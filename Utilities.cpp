#include "Utilities.h"

#ifdef __unix__
    #include <pthread.h>
    thread_local unsigned int seed = time(nullptr);
#endif

float degrees_to_radians(float degrees)
{
    return float(degrees) * pi / 180.0f;
}

float randomfloat() {
    // Running rand() on POSIX using multi-threading is very slow.

    #ifdef __unix__
        return static_cast<float>(rand_r(&seed)) / (RAND_MAX + 1.0f);
    #elif defined(_WIN32) || defined(_WIN64)
        return static_cast<float>(rand()) / (RAND_MAX + 1.0f);
    #else
        std::cerr << "Unsupported operating system." << std::endl;
        return 0.5f;
    #endif
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