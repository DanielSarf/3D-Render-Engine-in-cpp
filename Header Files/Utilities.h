#pragma once

#include <limits>
#include <cstdlib>

const float infinity = std::numeric_limits<float>::infinity();

const float pi = 3.1415926535897932385;

float degrees_to_radians(float);

float randomFloatSmall();

float randomFloat();

float randomFloat(float, float);

float clamp(float, float, float);