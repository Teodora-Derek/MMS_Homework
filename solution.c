#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <stdbool.h>
#include <time.h>
#include "queue.h"
#include <semaphore.h>
#include <pthread.h>

const uint8_t number_of_planes = 3;
const uint8_t number_of_frames = 10;
sem_t full_slots;
sem_t empty_slots;
pthread_mutex_t mutex_sync;

int32_t FRAME_HEIGHT;
int32_t FRAME_WIDTH;
int32_t FRAME_RATE;
int32_t SQUARE_SIDE;
int32_t total_pixel_count;
int32_t STEP;

typedef enum Direction
{
    NONE,
    RIGHT,
    DOWN_LEFT,
    LEFT,
    DOWN_RIGHT,
    UP_LEFT,
    UP_RIGHT,
} Direction;

typedef struct Plane
{
    uint32_t chanelCount;
    uint8_t *chanel_arr;
} Plane;

typedef struct Frame
{
    uint8_t planesCount;
    Plane **planes;
} Frame;

typedef struct Square
{
    int32_t x_col;
    int32_t y_row;
} Square;

typedef struct thread_args_t
{
    Frame **shared_frames_buff;
    int32_t empty_buff_index;
    int32_t full_buff_index;
    FILE *stream;
    Square *square;
    Direction *direction;
    bool *flag_goDown;
} thread_args_t;

Square *square_create(uint32_t xCol, uint32_t yRow);
void square_destroy(Square **square);
void square_set_color(Frame *frame, Square *square);
void square_move(Square *square, Direction *direction, bool *flag_goDown);

Plane *plane_create(uint32_t total_pixel_count, uint8_t plane_scale_down);
void plane_destroy(Plane **plane);

void frame_set_background_color(Frame *frame);
void frame_write_to_stream(FILE *stream, Frame *frame);
void frame_append_to_stream(FILE *stream, Frame *frame, Square *square, Direction *direction, bool *flag_goDown);

FILE *write_header();
void get_userInfo();
void frame_create(Frame **myFrame);
void frame_fill(FILE *stream, Frame *frame, Square *square);
void frame_destroy(Frame *frame);
Frame **frames_buff_create();
void frames_buff_destroy(Frame **buffer);

void *produce(void *args);
void *consume(void *args);

int main(void)
{
    get_userInfo();
    srand((unsigned int)time(NULL));

    Frame **shared_frames_buff = frames_buff_create();
    int32_t full_buff_index = 0;
    int32_t empty_buff_index = number_of_frames;
    FILE *stream = write_header();
    Square *square = square_create(0, 0);
    Direction direction = RIGHT;
    bool flag_goDown = false;

    thread_args_t args = {
        shared_frames_buff,
        empty_buff_index,
        full_buff_index,
        stream,
        square,
        &direction,
        &flag_goDown,
    };

    sem_init(&full_slots, 0, 0);
    sem_init(&empty_slots, 0, number_of_frames);
    pthread_mutex_init(&mutex_sync, NULL);

    pthread_t producer;
    pthread_t consumer;

    if (pthread_create(&producer, NULL, produce, &args) == -1)
    {
        perror("Could not create thread 1");
        exit(1);
    }
    if (pthread_create(&consumer, NULL, consume, &args) == -1)
    {
        perror("Could not create thread 2");
        exit(2);
    }

    if (pthread_join(producer, NULL) == -1)
    {
        perror("Could not join thread 1");
        exit(3);
    }
    if (pthread_join(consumer, NULL) == -1)
    {
        perror("Could not join thread 2");
        exit(4);
    }

    sem_destroy(&full_slots);
    sem_destroy(&empty_slots);
    pthread_mutex_destroy(&mutex_sync);

    frames_buff_destroy(shared_frames_buff);
    square_destroy(&square);
    fclose(stream);

    return 0;
}

void get_userInfo()
{
    FRAME_HEIGHT = 100;
    FRAME_WIDTH = 200;
    FRAME_RATE = 15;
    SQUARE_SIDE = 30;
    STEP = 17;
    total_pixel_count = FRAME_WIDTH * FRAME_HEIGHT;
    // printf("Enter FRAME_HEIGHT: \n");
    // scanf("%d", &FRAME_HEIGHT);
    // printf("Enter FRAME_WIDTH: \n");
    // scanf("%d", &FRAME_WIDTH);
    // printf("Enter FRAME_RATE: \n");
    // scanf("%d", &FRAME_RATE);
    // printf("Enter size of the side of the square: \n");
    // scanf("%d", &SQUARE_SIDE);
}

void frame_create(Frame **myFrame)
{
    Plane *Y_plane = (Plane *)plane_create(total_pixel_count, 1);
    Plane *U_plane = (Plane *)plane_create(total_pixel_count, 4);
    Plane *V_plane = (Plane *)plane_create(total_pixel_count, 4);

    Frame *frame = (Frame *)malloc(sizeof(Frame));
    frame->planes = (Plane **)malloc(number_of_planes * sizeof(Plane *));
    frame->planesCount = number_of_planes;

    frame->planes[0] = Y_plane;
    frame->planes[1] = U_plane;
    frame->planes[2] = V_plane;

    *myFrame = frame;
}

void frame_fill(FILE *stream, Frame *frame, Square *square)
{
    fprintf(stream, "FRAME\n");
    frame_set_background_color(frame);
    square_set_color(frame, square);
}

void frame_destroy(Frame *frame)
{
    plane_destroy(frame->planes + 0);
    plane_destroy(frame->planes + 1);
    plane_destroy(frame->planes + 2);

    free(frame->planes);
    free(frame);
}

Frame **frames_buff_create()
{
    Frame **shared_frames_buff = malloc(number_of_frames * sizeof(Frame *));
    for (uint8_t i = 0; i < number_of_frames; i++)
    {
        Frame *curr_frame = NULL;
        frame_create(&curr_frame);
        shared_frames_buff[i] = curr_frame;
    }

    return shared_frames_buff;
}

void frames_buff_destroy(Frame **buffer)
{
    for (uint8_t i = 0; i < number_of_frames; i++)
        frame_destroy(buffer[i]);
    free(buffer);
}

void *produce(void *args)
{
    thread_args_t *a = (thread_args_t *)args;

    while (a->full_buff_index <= number_of_frames)
    {
        sem_wait(&empty_slots);

        pthread_mutex_lock(&mutex_sync);
        Frame *curr_frame = a->shared_frames_buff[a->full_buff_index % number_of_frames];
        a->full_buff_index++;
        pthread_mutex_unlock(&mutex_sync);

        frame_fill(a->stream, curr_frame, a->square);
        a->shared_frames_buff[a->empty_buff_index % number_of_frames] = curr_frame;
        a->empty_buff_index++;

        sem_post(&full_slots);
    }

    return NULL;
}

void *consume(void *args)
{
    thread_args_t *a = ((thread_args_t *)args);

    while (a->empty_buff_index >= 0)
    {
        sem_wait(&full_slots);

        pthread_mutex_lock(&mutex_sync);
        Frame *curr_frame = a->shared_frames_buff[a->empty_buff_index % number_of_frames];
        a->empty_buff_index++;
        pthread_mutex_unlock(&mutex_sync);

        frame_append_to_stream(a->stream, curr_frame, a->square, a->direction, a->flag_goDown);
        a->shared_frames_buff[a->full_buff_index % number_of_frames] = curr_frame;
        a->full_buff_index++;

        sem_post(&empty_slots);
    }
    return NULL;
}

void frame_append_to_stream(FILE *stream, Frame *frame, Square *square, Direction *direction, bool *flag_goDown)
{
    frame_write_to_stream(stream, frame);
    square_move(square, direction, flag_goDown);
}

Square *square_create(uint32_t xCol, uint32_t yRow)
{
    Square *square = (Square *)malloc(sizeof(Square));

    square->x_col = xCol;
    square->y_row = yRow;

    return square;
}

void square_destroy(Square **square)
{
    free(*square);
}

Plane *plane_create(uint32_t total_pixel_count, uint8_t plane_scale_down)
{
    Plane *plane = (Plane *)malloc(sizeof(Plane));

    plane->chanelCount = total_pixel_count / plane_scale_down;
    plane->chanel_arr = malloc(plane->chanelCount * sizeof(uint8_t));

    return plane;
}

void plane_destroy(Plane **plane)
{
    free((*plane)->chanel_arr);
    free(*plane);
}

void square_set_color(Frame *frame, Square *square)
{
    int random_color = rand() % 256;

    int y = rand() % 256;
    int u = rand() % 256;
    int v = rand() % 256;

    for (int32_t y = square->y_row; y < square->y_row + SQUARE_SIDE; y++)
    {
        for (int32_t x = square->x_col; x < square->x_col + SQUARE_SIDE; x++)
        {
            frame->planes[0]->chanel_arr[y * FRAME_WIDTH + x] = y;
            frame->planes[1]->chanel_arr[(y / 2) * (FRAME_WIDTH / 2) + (x / 2)] = u;
            frame->planes[2]->chanel_arr[(y / 2) * (FRAME_WIDTH / 2) + (x / 2)] = v;
        }
    }
}

void square_move(Square *square, Direction *direction, bool *flag_goDown)
{
    if (!(*flag_goDown))
    {
        switch (*direction)
        {
        case RIGHT:
            if (square->x_col + SQUARE_SIDE + STEP <= FRAME_WIDTH)
            {
                square->x_col += STEP;
            }
            else if (FRAME_WIDTH - (square->x_col + SQUARE_SIDE) < STEP)
            {
                square->x_col += FRAME_WIDTH - (square->x_col + SQUARE_SIDE);
                *direction = DOWN_LEFT;
            }
            if (square->x_col + SQUARE_SIDE == FRAME_WIDTH &&
                square->y_row + SQUARE_SIDE == FRAME_HEIGHT)
            {
                *flag_goDown = true;
            }
            break;

        case DOWN_LEFT:
            *direction = LEFT;
            if (square->y_row + SQUARE_SIDE + STEP <= FRAME_HEIGHT)
            {
                square->y_row += STEP;
            }
            else if (FRAME_HEIGHT - (square->y_row + SQUARE_SIDE) < STEP)
            {
                square->y_row += FRAME_HEIGHT - (square->y_row + SQUARE_SIDE);
            }
            if (square->x_col + SQUARE_SIDE == FRAME_WIDTH &&
                square->y_row + SQUARE_SIDE == FRAME_HEIGHT)
            {
                *flag_goDown = true;
            }
            break;

        case DOWN_RIGHT:
            *direction = RIGHT;
            if (square->y_row + SQUARE_SIDE + STEP <= FRAME_HEIGHT)
            {
                square->y_row += STEP;
            }
            else if (FRAME_HEIGHT - (square->y_row + SQUARE_SIDE) < STEP)
            {
                square->y_row += FRAME_HEIGHT - (square->y_row + SQUARE_SIDE);
            }
            break;

        case LEFT:
            if ((square->x_col - STEP) >= 0)
            {
                square->x_col -= STEP;
            }
            else
            {
                square->x_col = 0;
                *direction = DOWN_RIGHT;
            }
            break;
        }
    }
    else
    {
        switch (*direction)
        {
        case RIGHT:
            if (square->x_col + SQUARE_SIDE + STEP <= FRAME_WIDTH)
            {
                square->x_col += STEP;
            }
            else if (FRAME_WIDTH - (square->x_col + SQUARE_SIDE) < STEP)
            {
                square->x_col += FRAME_WIDTH - (square->x_col + SQUARE_SIDE);
                *direction = UP_LEFT;
            }
            break;

        case UP_LEFT:
            *direction = LEFT;
            if ((square->y_row - STEP) >= 0)
            {
                square->y_row -= STEP;
            }
            else
            {
                square->y_row = 0;
            }
            break;

        case UP_RIGHT:
            *direction = RIGHT;
            if ((square->y_row - STEP) >= 0)
            {
                square->y_row -= STEP;
            }
            else
            {
                square->y_row = 0;
            }
            if (square->x_col == 0 &&
                square->y_row == 0)
            {
                *flag_goDown = false;
            }
            break;

        case LEFT:
            if ((square->x_col - STEP) >= 0)
            {
                square->x_col -= STEP;
            }
            else
            {
                square->x_col = 0;
                *direction = UP_RIGHT;
            }
            if (square->x_col == 0 &&
                square->y_row == 0)
            {
                *flag_goDown = false;
            }
            break;
        }
    }
}

FILE *write_header()
{
    const char *yuv_header_filename = "square.y4m";
    const char *yuv_header_mode = "w";
    FILE *file_stream = fopen(yuv_header_filename, yuv_header_mode);
    if (!file_stream)
    {
        perror("Cannot open file stream.\n");
        exit(EXIT_FAILURE);
    }
    const char *yuv_format = "YUV4MPEG2 W%d H%d F%d:1 Ip A1:1 C420\n";
    uint32_t printed_chars_count = fprintf(file_stream, yuv_format, FRAME_WIDTH, FRAME_HEIGHT, FRAME_RATE);
    return file_stream;
}

void frame_set_background_color(Frame *frame)
{
    for (uint32_t y = 0; y < FRAME_HEIGHT; y++)
        for (uint32_t x = 0; x < FRAME_WIDTH; x++)
        {
            // Set background color:
            frame->planes[0]->chanel_arr[y * FRAME_WIDTH + x] = 127;
            frame->planes[1]->chanel_arr[(y / 2) * (FRAME_WIDTH / 2) + (x / 2)] = 127;
            frame->planes[2]->chanel_arr[(y / 2) * (FRAME_WIDTH / 2) + (x / 2)] = 127;
        }
}
void frame_write_to_stream(FILE *stream, Frame *frame)
{
    for (uint8_t i = 0; i < frame->planesCount; i++)
        fwrite(
            frame->planes[i]->chanel_arr,
            sizeof(uint8_t),
            frame->planes[i]->chanelCount,
            stream);
}