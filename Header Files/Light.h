#pragma once

#include "Vector3.h"
#include "Color.h"

class Light
{
private:
	Vector3 location;
	Color color;
	float power;
	//float radius;
	//int maxBounces;

public:
	Light(Vector3, Color, float);

	void setLocation(Vector3);

	void setLocation(Color inputColor);

	void setPower(float inputPower);

	Vector3 getLocation();

	Color getColor();

	float getPower();
};