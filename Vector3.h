#pragma once

#include <iostream>
#include <xmmintrin.h>
#include <math.h>

#include "Utilities.h"

class Vector3
{
protected:
	float v3[3];

public:
	//Constructor sets x, y, z components
	Vector3(float = 0, float = 0, float = 0);

	Vector3(float inputV4[3]);
	
	//Adds two vectors together
	Vector3 operator+(Vector3) const;

	//Subtracts two vectors together
	Vector3 operator-(Vector3) const;
	
	//Returns negative vector
	Vector3 operator-() const;

	//Multiplies all components by float value
	Vector3 operator*(float) const;

	//Divides all components by float value
	Vector3 operator/(float) const;

	//Sets all vector components
	void setAll(float, float, float);

	//Getter and setter functions:
	void setX(float);

	void setY(float);

	void setZ(float);

	float getX() const;

	float getY() const;

	float getZ() const;

	//Returns dot product of vector
	float dotProduct() const;

	//Returns dot product of two vectors
	float dotProduct(const Vector3&) const;

	//Returns magnitude of vector
	float magnitude() const;

	//Returns normalized vector
	Vector3 normalize() const;

	//Returns cross product between two vectors
	Vector3 crossProduct(const Vector3&) const;

	Vector3 reflect(const Vector3&, const Vector3&) const;

	//Returns a vector with random components
	Vector3 random() const;

	//Returns a vector with random components between a range
	Vector3 random(float, float) const;

	//Returns semi-random points on the surface of a unit sphere
	Vector3 randomPointOnUnitSphereSurface() const;

	bool nearZero() const;

	//Prints vector component values
	void printVector() const;
};