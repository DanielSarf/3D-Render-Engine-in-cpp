#pragma once

#include "Vector3.h"
#include "Color.h"
#include "Ray.h"
#include "Material.h"

//Wrapper class
class Object
{
public:
	Object(Vector3 = Vector3(), float = 1, Material = Material());
};

class Sphere : public Object
{
private:
	Vector3 location;
	float radius;
	Material material;

public:
	//Constructor sets data members
	Sphere(Vector3 = Vector3(), float = 1, Material = Material());

	//Finds the shortest distance between ray origin and where ray intersected sphere
	float intersections(Ray&) const;

	//Returns the normal of the hit position
	Vector3 normal(Vector3);

	//Returns the material of the sphere
	Material getMaterial() const;
};