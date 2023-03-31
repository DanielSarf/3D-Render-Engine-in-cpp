#include "Utilities.h"

float degrees_to_radians(float degrees)
{
    return float(degrees) * pi / 180.0f;
}

float randomfloat()
{
    return float(rand() / (RAND_MAX + 1.0));
}

float randomfloat(float min, float max)
{
    return min + (max - min) * randomfloat();
}

float clamp(float x, float min, float max)
{
    if (x < min)
    {
        return min;
    }

    if (x > max)
    {
        return max;
    }

    return x;
}