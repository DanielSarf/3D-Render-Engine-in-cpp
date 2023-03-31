#pragma once

#include "Vector3.h"

class Ray
{
private:
	Vector3 origin, direction;

public:
	//Constructor sets origin and direction
	Ray(Vector3 = Vector3(), Vector3 = Vector3());

	//Getter and setter functions:
	void setOrigin(Vector3);

	void setDirection(Vector3);

	Vector3 getOrigin() const;

	Vector3 getDirection() const;

	//Uses distance to find a specific point along ray
	Vector3 hitPosition(float) const;
};