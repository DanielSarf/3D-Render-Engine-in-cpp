#pragma once

#include <limits>
#include <cstdlib>

const float infinity = std::numeric_limits<float>::infinity();

const float pi = 3.141592f;

float degrees_to_radians(float degrees);

float randomfloat();

float randomfloat(float min, float max);

float clamp(float x, float min, float max);