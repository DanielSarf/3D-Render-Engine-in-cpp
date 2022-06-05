#pragma once

#include "Vector3.h"

class Ray
{
private:
	Vector3 origin, direction;

public:
	Ray(Vector3, Vector3);

	void setOrigin(Vector3);

	void setDirection(Vector3);

	Vector3 getOrigin() const;

	Vector3 getDirection() const;

	Vector3 hitPosition(float) const;
};