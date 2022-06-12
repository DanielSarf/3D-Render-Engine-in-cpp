#include "../Header Files/Color.h"

Color::Color(std::string hexCode)
{
	//After the first character '#', every next two characters are a hexadecimal value that gets converted to decimal
	x = float(16 * hexCharToDecInt(hexCode[1]) + hexCharToDecInt(hexCode[2])) / 255;
	y = float(16 * hexCharToDecInt(hexCode[3]) + hexCharToDecInt(hexCode[4])) / 255;
	z = float(16 * hexCharToDecInt(hexCode[5]) + hexCharToDecInt(hexCode[6])) / 255;
}

Color::Color(float inputR, float inputG, float inputB) : Vector3(inputR, inputG, inputB) {}

Color Color::operator+(Color other) const
{
	return Color(x + other.x, y + other.y, z + other.z);
}

Color Color::operator*(float other) const
{
	return Color(x * other, y * other, z * other);
}

Color Color::operator/(float other) const
{
	return Color(x / other, y / other, z / other);
}


int Color::hexCharToDecInt(char inputChar) const
{
	//Makes a empty temporary string
	std::string tempString = "";

	//Sets first character of string to the input character
	tempString[0] = inputChar;

	//stoul converts character of string to specified base
	return stoul(tempString, NULL, 16);
}