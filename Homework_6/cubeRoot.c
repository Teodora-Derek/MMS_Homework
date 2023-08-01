#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#define EPSILON 0.001

// Направете функция, която изчислява корен трети,
// без да използвате math.h или друга външна библиотека.
double cubeRoot(double num);
double cubeRoot2(double num);
double derivative(double num);
double customF(double guess, double num);

int main(void)
{
    printf("Cube root: %f\n", cubeRoot2(48));
    printf("Cube root: %f\n", cubeRoot(48));
}

double cubeRoot2(double num)
{
    // f(x) = x^3 - num;
    // f(x)` = 3 * (x)^2;
    int lowerIdx = 0;
    int upperIdx = 0;

    int i = 0;
    double possibleRoot = 0;
    while ((possibleRoot = customF(i, num)) < 0)
        upperIdx = i++;

    if (possibleRoot == 0)
        return i;
    // The lower is between X(n)->customF(i, num) and X(n-1)->customF(--i, num)
    lowerIdx = i;

    printf("lowerIdx: %d \n", lowerIdx);
    printf("upperIdx: %d \n", upperIdx);

    double currGuess = 0;
    currGuess = (double)(lowerIdx + upperIdx) / 2;
    printf("currGuess: %lf \n", currGuess);
    double f_of_currGuess = 0;
    double derivative_of_currGuess = 0;
    for (size_t i = 0; i < 10; i++)
    {
        f_of_currGuess = customF(currGuess, num);
        printf("f_of_currGuess: %f \n", f_of_currGuess);

        derivative_of_currGuess = derivative(currGuess);
        printf("derivative_of_currGuess: %f \n", derivative_of_currGuess);

        currGuess = (currGuess - (f_of_currGuess / derivative_of_currGuess));
        printf("currGuess: %f \n", currGuess);
        printf("-----------\n");
    }

    return currGuess;
}

double derivative(double x)
{
    // f(x)` = 3 * x^2;
    return 3 * x * x;
}

double customF(double guess, double num)
{
    return (guess * guess * guess) - num;
}

double cubeRoot(double num)
{
    if (num == 0 || num == 1)
        return num;

    // Create initial guess:
    double currGuess = num / 3.0;
    double nextGuess;
    while (true)
    {
        // X(n+1) = { 2*X(n) + num / [X(n)]^2 } / 3.0;
        nextGuess = (2 * currGuess + num / (currGuess * currGuess)) / 3.0;
        if (nextGuess - currGuess < EPSILON && currGuess - nextGuess < EPSILON)
        {
            // If the difference between the current guess and the next guess is within the desired precision, break the loop
            break;
        }
        currGuess = nextGuess;
    }

    return currGuess;
}
