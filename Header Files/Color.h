#pragma once

#include <ctime>
#include <fstream>
#include <string>

class Color
{
private:
	unsigned char r, g, b;

public:
	Color(std::string);

	Color(unsigned char = 0, unsigned char = 0, unsigned char = 0);
	
	Color operator+(Color other) const;

	Color operator*(float other) const;

	void setAll(unsigned char = 0, unsigned char = 0, unsigned char = 0);

	void setR(unsigned char);

	void setG(unsigned char);
	
	void setB(unsigned char);

	short getR() const;

	short getG() const;

	short getB() const;

	int hexCharToDecInt(char) const;
};