#include "../Header Files/Utilities.h"

float degrees_to_radians(float degrees)
{
    return float(degrees * pi / 180.0);
}

float randomFloatSmall()
{
    return float(rand() / (RAND_MAX + 1.0)) * 0.001;
}

float randomFloat()
{
    return float(rand() / (RAND_MAX + 1.0));
}

float randomFloat(float min, float max)
{
    return min + (max - min) * randomFloat();
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