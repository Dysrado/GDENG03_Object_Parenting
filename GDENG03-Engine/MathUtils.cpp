#include "MathUtils.h"

#include <corecrt_math.h>
#include <stdlib.h>

float MathUtils::randomFloat(float a, float b)
{
    float random = ((float)rand()) / (float)RAND_MAX;
    float diff = b - a;
    float r = random * diff;
    return a + r;
}

int MathUtils::randomInt(int a, int b)
{
    int range = a - b + 1;
    int num = rand() % range + a;

    return num;
}

float MathUtils::extractScaleTransform(float x, float y, float z)
{
    return sqrtf((powf(x, 2.0f) + powf(y, 2.0f) + powf(z, 2.0f)));
}
