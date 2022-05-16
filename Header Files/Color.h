#pragma once

#include <ctime>
#include <fstream>
#include <string>

#include "Vector3.h"

class Color : public Vector3
{
public:
	Color(std::string);

	Color(float = 0, float = 0, float = 0);
	
	Color operator+(Color other) const;

	Color operator*(float other) const;

	int hexCharToDecInt(char) const;
};