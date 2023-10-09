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
sem_t *producer;
sem_t *consumer;
pthread_mutex_t *mutex_sync;

int32_t FRAME_HEIGHT;
int32_t FRAME_WIDTH;
int32_t FRAME_RATE;
int32_t SQUARE_SIDE;
int32_t total_pixel_count;
int32_t STEP;

typedef enum Direction
{
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
void frame_destroy(Frame *frame);
Queue *queue_fill_with_frames();

int main(void)
{
    get_userInfo();
    srand((unsigned int)time(NULL));
    FILE *stream = write_header();
    Square *square = square_create(0, 0);
    Frame *frame = NULL;
    Direction direction = RIGHT;
    bool flag_goDown = false;

    Queue *frames_queue = queue_fill_with_frames();

    sem_init(producer, false, 0);
    sem_init(consumer, false, number_of_frames);
    pthread_mutex_init(mutex_sync, NULL);

    Queue *shared_queue = init_queue(number_of_frames);
    do
    {
        sem_wait(consumer);

        pthread_mutex_lock(mutex_sync);
        enqueue(shared_queue, (void *)frames_queue);
        pthread_mutex_unlock(mutex_sync);

        sem_post(producer);
    } while (true);

    do
    {
        sem_post(producer);

        pthread_mutex_lock(mutex_sync);
        Frame *frame = (Frame *)dequeue(shared_queue);
        pthread_mutex_unlock(mutex_sync);

        sem_wait(consumer);
    } while (true);

    for (uint32_t i = 0; i < 150; i++)
        frame_append_to_stream(stream, frame, square, &direction, &flag_goDown);

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

void frame_destroy(Frame *frame)
{
    plane_destroy(frame->planes + 0);
    plane_destroy(frame->planes + 1);
    plane_destroy(frame->planes + 2);

    free(frame->planes);
    free(frame);
}

Queue *queue_fill_with_frames()
{
    Queue *queue = init_queue(number_of_frames);
    for (uint8_t i = 0; i < number_of_frames; i++)
    {
        Frame *curr_frame = NULL;
        frame_create(&curr_frame);
        enqueue(queue, (void *)curr_frame);
    }

    return queue;
}

void frame_append_to_stream(FILE *stream, Frame *frame, Square *square, Direction *direction, bool *flag_goDown)
{
    fprintf(stream, "FRAME\n");

    frame_set_background_color(frame);
    square_set_color(frame, square);

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