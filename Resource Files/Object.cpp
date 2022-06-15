#include "../Header Files/Object.h"

Object::Object(Vector3 inputLocation) : location(inputLocation) {}

DiffuseMaterial Object::defaultMaterial = { DiffuseMaterial(Color(0.5, 0.5, 0.5)) };

Sphere::Sphere(Vector3 inputLocation, float inputRadius, Material* inputMaterial) : Object(inputLocation), radius(inputRadius), material(inputMaterial) {}

float Sphere::intersections(Ray& ray) const
{
	//Uses discriminant formula to find if there was a ray hit
	Vector3 sphereToRay = ray.getOrigin() - location;

	float b = 2 * ray.getDirection().dotProduct(sphereToRay);

	float c = sphereToRay.dotProduct() - radius * radius;

	float discriminant = b * b - 4 * c;

	//If there was a ray hit, uses quadratic formula to find shortest distance to ray hit(s) from ray origin
	if (discriminant >= 0)
	{
		float distance = (-b - sqrt(discriminant)) / 2;

		if (distance > 0.001)
		{
			return distance;
		}
	}

	return NULL;
}

Vector3 Sphere::normal(Vector3 surfacePoint)
{
	return (surfacePoint - location).normalize();
}

Material* Sphere::getMaterial() const
{
	return material;
}