#include "Light.h"

Light::Light(Vector3 inputLocation, Color inputColor, float inputPower) : location(inputLocation), color(inputColor), power(inputPower) {}

void Light::setLocation(Vector3 inputLocation)
{
	location = inputLocation;
}

void Light::setLocation(Color inputColor)
{
	color = inputColor;
}

void Light::setPower(float inputPower)
{
	power = inputPower;
}

Vector3 Light::getLocation()
{
	return location;
}

Color Light::getColor()
{
	return color;
}

float Light::getPower()
{
	return power;
}