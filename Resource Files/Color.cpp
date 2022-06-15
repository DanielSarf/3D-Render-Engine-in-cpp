#include "../Header Files/Color.h"

Color::Color(std::string hexCode)
{
	//After the first character '#', every next two characters are a hexadecimal value that gets converted to decimal
	v3[0] = float(16 * hexCharToDecInt(hexCode[1]) + hexCharToDecInt(hexCode[2])) / 255;
	v3[1] = float(16 * hexCharToDecInt(hexCode[3]) + hexCharToDecInt(hexCode[4])) / 255;
	v3[2] = float(16 * hexCharToDecInt(hexCode[5]) + hexCharToDecInt(hexCode[6])) / 255;
}

Color::Color(float inputR, float inputG, float inputB) : Vector3(inputR, inputG, inputB) {}

Color::Color(float inputV4[3])
{
	v3[0] = inputV4[0];
	v3[1] = inputV4[1];
	v3[2] = inputV4[2];
}

Color Color::operator+(Color inputOther) const
{
	__m128 current = _mm_set_ps(0, v3[2], v3[1], v3[0]);

	__m128 other = _mm_set_ps(0, inputOther.v3[2], inputOther.v3[1], inputOther.v3[0]);

	__m128 result = _mm_add_ps(current, other);

	float r3[3];

	_mm_storeu_ps(r3, result);

	return Color(r3);
}

Color Color::operator*(Color inputOther) const
{
	__m128 current = _mm_set_ps(0, v3[2], v3[1], v3[0]);

	__m128 other = _mm_set_ps(0, inputOther.v3[2], inputOther.v3[1], inputOther.v3[0]);

	__m128 result = _mm_mul_ps(current, other);

	float r3[3];

	_mm_storeu_ps(r3, result);

	return Color(r3);
}

Color Color::operator*(float inputOther) const
{
	__m128 current = _mm_set_ps(0, v3[2], v3[1], v3[0]);

	__m128 other = _mm_set1_ps(inputOther);

	__m128 result = _mm_mul_ps(current, other);

	float r3[3];

	_mm_storeu_ps(r3, result);

	return Color(r3);
}

Color Color::operator/(float inputOther) const
{
	__m128 current = _mm_set_ps(0, v3[2], v3[1], v3[0]);

	__m128 other = _mm_set1_ps(inputOther);

	__m128 result = _mm_div_ps(current, other);

	float r3[3];

	_mm_storeu_ps(r3, result);

	return Color(r3);
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