#include "../Header Files/Color.h"

Color::Color(std::string hexCode)
{
	r = 16 * hexCharToDecInt(hexCode[1]) + hexCharToDecInt(hexCode[2]);
	g = 16 * hexCharToDecInt(hexCode[3]) + hexCharToDecInt(hexCode[4]);
	b = 16 * hexCharToDecInt(hexCode[5]) + hexCharToDecInt(hexCode[6]);
}

Color::Color(unsigned char inputR, unsigned char inputG, unsigned char inputB) : r(inputR), g(inputG), b(inputB) {}

Color Color::operator+(Color other) const
{
	return Color(r + other.r, g + other.g, b + other.b);
}

Color Color::operator*(float other) const
{
	return Color(r * other, g * other, b * other);
}

void Color::setAll(unsigned char inputR, unsigned char inputG, unsigned char inputB)
{
	r = inputR;
	g = inputG;
	b = inputB;
}

void Color::setR(unsigned char inputR)
{
	r = inputR;
}

void Color::setG(unsigned char inputG)
{
	g = inputG;
}

void Color::setB(unsigned char inputB)
{
	b = inputB;
}

short Color::getR() const
{
	return r;
}

short Color::getG() const
{
	return g;
}

short Color::getB() const
{
	return b;
}

int Color::hexCharToDecInt(char inputChar) const
{
	std::string tempString = "";

	tempString[0] = inputChar;

	return stoul(tempString, NULL, 16);
}