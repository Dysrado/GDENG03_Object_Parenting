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

Vector3D MathUtils::convertRadToEuler(float x, float y, float z)
{
    Vector3D val = Vector3D::zeros();

    val.m_x = (x / 3.141592f) * 180.0f;
    val.m_y = (y / 3.141592f) * 180.0f;
    val.m_z = (z / 3.141592f) * 180.0f;

    return val;
}

Vector3D MathUtils::convertEulerToRad(float x, float y, float z)
{
    int X = 0, Y = 0, Z = 0;
    bool isPositive;

    Vector3D val = Vector3D::zeros();
    float valX = abs(x);
    float valY = abs(y);
    float valZ = abs(z);

    if(x > 0.0f){
        val.m_x = MathUtils::converter(valX, 180.0f / 3.141592f);
    }

    else{
        val.m_x = -MathUtils::converter(valX, 180.0f / 3.141592f);
    }

    if (y > 0.0f) {
        val.m_y = MathUtils::converter(valY, 180.0f / 3.141592f);
    }

    else {
        val.m_y = -MathUtils::converter(valY, 180.0f / 3.141592f);
    }

    if (z > 0.0f) {
        val.m_z = MathUtils::converter(valZ, 180.0f / 3.141592f);
    }

    else {
        val.m_z = -MathUtils::converter(valZ, 180.0f / 3.141592f);
    }


    return val;
}

float MathUtils::converter(float val, float steps)
{
    int i = 0;
    float sum = 0;

    float value = val;
    float stepsCount = steps;
    while (value > stepsCount)
    {
        value -= stepsCount;
        i++;
    }

    sum = (float)i + (value / stepsCount);
    return sum;

}

