#include "../Header Files/Color.h"

Color::Color(std::string hexCode)
{
	r = float(16 * hexCharToDecInt(hexCode[1]) + hexCharToDecInt(hexCode[2])) / 255;
	g = float(16 * hexCharToDecInt(hexCode[3]) + hexCharToDecInt(hexCode[4])) / 255;
	b = float(16 * hexCharToDecInt(hexCode[5]) + hexCharToDecInt(hexCode[6])) / 255;
}

Color::Color(float inputR, float inputG, float inputB) : r(inputR), g(inputG), b(inputB) {}

Color Color::operator+(Color other) const
{
	return Color(r + other.r, g + other.g, b + other.b);
}

Color Color::operator*(float other) const
{
	return Color(r * other, g * other, b * other);
}

void Color::setAll(float inputR, float inputG, float inputB)
{
	r = inputR;
	g = inputG;
	b = inputB;
}

void Color::setR(float inputR)
{
	r = inputR;
}

void Color::setG(float inputG)
{
	g = inputG;
}

void Color::setB(float inputB)
{
	b = inputB;
}

float Color::getR() const
{
	return r;
}

float Color::getG() const
{
	return g;
}

float Color::getB() const
{
	return b;
}

int Color::hexCharToDecInt(char inputChar) const
{
	std::string tempString = "";

	tempString[0] = inputChar;

	return stoul(tempString, NULL, 16);
}