#pragma once

#include <ctime>
#include <fstream>
#include <string>

#include "Vector3.h"

class Color : public Vector3
{
public:
	//Constructor sets x(r), y(g), z(b) components using hex code
	Color(std::string);

	//Constructor sets x(r), y(g), z(b) components
	Color(float = 0, float = 0, float = 0);

	Color(float inputV3[3]);
	
	//Adds two colors together
	Color operator+(Color inputOther) const;

	//Multiplies two colors
	Color operator*(Color inputOther) const;

	//Multiplies all components by float value
	Color operator*(float inputOther) const;

	//Divides all components by float value
	Color operator/(float inputOther) const;

	//Returns integer from a hex character like hexCharToDecInt('F') -> 15
	int hexCharToDecInt(char) const;
};