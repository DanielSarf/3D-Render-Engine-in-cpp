#pragma once

#include "Vector3.h"
#include "Color.h"
#include "Ray.h"

class Object
{
private:
	Vector3 location;
	float radius;
	Color material;

public:
	Object(Vector3, float inputRadius, Color);

	float intersections(Ray&) const;

	Color getMaterial() const;
};