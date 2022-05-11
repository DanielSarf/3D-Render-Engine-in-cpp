#pragma once

#include "Vector3.h"
#include "Color.h"
#include "Ray.h"
#include "Material.h"

class Object
{
private:
	Vector3 location;
	float radius;
	Material material;

public:
	Object(Vector3, float inputRadius, Material);

	float intersections(Ray&) const;

	Vector3 normal(Vector3);

	Material getMaterial() const;
};