#include "../Header Files/Ray.h"

Ray::Ray(Vector3 inputOrigin, Vector3 inputDirection) : origin(inputOrigin), direction(inputDirection.normalize()) {}

void Ray::setOrigin(Vector3 inputOrigin)
{
	origin = inputOrigin;
}

void Ray::setDirection(Vector3 inputDirection)
{
	direction = inputDirection.normalize();
}

Vector3 Ray::getOrigin() const
{
	return origin;
}

Vector3 Ray::getDirection() const
{
	return direction;
}