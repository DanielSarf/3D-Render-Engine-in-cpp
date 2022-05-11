#pragma once

#include <ctime>
#include <fstream>
#include <string>

class Color
{
private:
	int r, g, b;

public:
	Color(std::string);

	Color(int = 0, int = 0, int = 0);
	
	Color operator+(Color other) const;

	Color operator*(float other) const;

	void setAll(int = 0, int = 0, int = 0);

	void setR(int);

	void setG(int);
	
	void setB(int);

	int getR() const;

	int getG() const;

	int getB() const;

	int hexCharToDecInt(char) const;
};