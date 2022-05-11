#pragma once

#include <ctime>
#include <fstream>
#include <string>

class Color
{
private:
	float r, g, b;

public:
	Color(std::string);

	Color(float = 0, float = 0, float = 0);
	
	Color operator+(Color other) const;

	Color operator*(float other) const;

	void setAll(float = 0, float = 0, float = 0);

	void setR(float);

	void setG(float);
	
	void setB(float);

	float getR() const;

	float getG() const;

	float getB() const;

	int hexCharToDecInt(char) const;
};