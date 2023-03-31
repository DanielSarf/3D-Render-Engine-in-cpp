#include "Vector3.h"

Vector3::Vector3(float inputX, float inputY, float inputZ)
{
	v3[0] = inputX;
	v3[1] = inputY;
	v3[2] = inputZ;
}

Vector3::Vector3(float inputV4[3])
{
	v3[0] = inputV4[0];
	v3[1] = inputV4[1];
	v3[2] = inputV4[2];
}

Vector3 Vector3::operator+(Vector3 inputOther) const
{
	__m128 current = _mm_set_ps(0, v3[2], v3[1], v3[0]);

	__m128 other = _mm_set_ps(0, inputOther.v3[2], inputOther.v3[1], inputOther.v3[0]);

	__m128 result = _mm_add_ps(current, other);

	float r3[3];

	_mm_storeu_ps(r3, result);

	return Vector3(r3);
}

Vector3 Vector3::operator-(Vector3 inputOther) const
{
	__m128 current = _mm_set_ps(0, v3[2], v3[1], v3[0]);

	__m128 other = _mm_set_ps(0, inputOther.v3[2], inputOther.v3[1], inputOther.v3[0]);

	__m128 result = _mm_sub_ps(current, other);

	float r3[3];

	_mm_storeu_ps(r3, result);

	return Vector3(r3);
}

Vector3 Vector3::operator-() const
{
	__m128 result = _mm_mul_ps(_mm_set_ps(0, v3[2], v3[1], v3[0]), _mm_set1_ps(-1.0));

	float r3[3];

	_mm_storeu_ps(r3, result);

	return Vector3(r3);
}

Vector3 Vector3::operator*(float inputOther) const
{
	__m128 current = _mm_set_ps(0, v3[2], v3[1], v3[0]);

	__m128 other = _mm_set1_ps(inputOther);

	__m128 result = _mm_mul_ps(current, other);

	float r3[3];

	_mm_storeu_ps(r3, result);

	return Vector3(r3);
}

Vector3 Vector3::operator/(float inputOther) const
{
	__m128 current = _mm_set_ps(0, v3[2], v3[1], v3[0]);

	__m128 other = _mm_set1_ps(inputOther);

	__m128 result = _mm_div_ps(current, other);
	
	float r3[3];

	_mm_storeu_ps(r3, result);

	return Vector3(r3);
}

void Vector3::setAll(float inputX, float inputY, float inputZ)
{
	v3[0] = inputX;
	v3[1] = inputY;
	v3[2] = inputZ;
}

void Vector3::setX(float inputX)
{
	v3[0] = inputX;
}

void Vector3::setY(float inputY)
{
	v3[1] = inputY;
}

void Vector3::setZ(float inputZ)
{
	v3[2] = inputZ;
}

float Vector3::getX() const
{
	return v3[0];
}

float Vector3::getY() const
{
	return v3[1];
}

float Vector3::getZ() const
{
	return v3[2];
}

float Vector3::dotProduct() const
{
	__m128 current = _mm_set_ps(0, v3[2], v3[1], v3[0]);

	__m128 result = _mm_mul_ps(current, current);

	float r3[3]; 

	_mm_storeu_ps(r3, result);

	return (r3[0] + r3[1] + r3[2]);
}

float Vector3::dotProduct(const Vector3& inputOther) const
{
	__m128 current = _mm_set_ps(0, v3[2], v3[1], v3[0]);

	__m128 other = _mm_set_ps(0, inputOther.v3[2], inputOther.v3[1], inputOther.v3[0]);

	__m128 result = _mm_mul_ps(current, other);

	float r3[3];

	_mm_storeu_ps(r3, result);

	return (r3[0] + r3[1] + r3[2]);
}

float Vector3::magnitude() const
{
	return sqrt(dotProduct());
}

Vector3 Vector3::normalize() const
{
	return (*this) / magnitude();
}

Vector3 Vector3::crossProduct(const Vector3& other) const
{
	return Vector3(v3[1] * other.v3[2] - v3[2] * other.v3[1],
		v3[2] * other.v3[0] - v3[0] * other.v3[2],
		v3[0] * other.v3[1] - v3[1] * other.v3[0]);
}

Vector3 Vector3::reflect(const Vector3& v, const Vector3& n) const
{
	return v - n * (v.dotProduct(n) * 2);
}

Vector3 Vector3::random() const
{
	return Vector3(randomfloat(), randomfloat(), randomfloat());
}

Vector3 Vector3::random(float min, float max) const
{
	return Vector3(randomfloat(min, max), randomfloat(min, max), randomfloat(min, max));
}

Vector3 Vector3::randomPointOnUnitSphereSurface() const
{
	//Random point in cube from (-1, -1, -1) to (1, 1, 1) then normalizes so they are one unit away from origin i.e surface of unit sphere
	return random(-1, 1).normalize();
}

bool Vector3::nearZero() const
{
	const float s = 1e-8f;
	
	return (fabs(v3[0]) < s) && (fabs(v3[1]) < s) && (fabs(v3[2]) < s);
}

void Vector3::printVector() const
{
	std::cout << "(" << v3[0] << ", " << v3[1] << ", " << v3[2] << ", " << 0 << ")" << std::endl;
}