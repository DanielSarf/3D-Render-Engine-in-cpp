#pragma once

#include "Color.h"

class Material
{
private:
	Color color;
	float ambient;
	float diffuse;
	float specular;

public:
	Material(Color, float = 0.05, float = 1, float = 1);
};