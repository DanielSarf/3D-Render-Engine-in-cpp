#pragma once

#include <iostream>

class Vector3
{
protected:
	float x, y, z;

public:
	Vector3(float = 0, float = 0, float = 0);

	Vector3 operator+(Vector3) const;

	Vector3 operator-(Vector3) const;

	Vector3 operator*(float) const;

	Vector3 operator/(float) const;

	void setAll(float, float , float);

	void setX(float inputX);

	void setY(float inputY);

	void setZ(float inputZ);

	float getX() const;

	float getY() const;

	float getZ() const;

	float dotProduct() const;

	float dotProduct(Vector3) const;

	float magnitude() const;

	Vector3 normalize() const;

	void printVector() const;
};