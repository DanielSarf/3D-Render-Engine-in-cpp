#pragma once

#include "Vector3.h"
#include "Color.h"
#include "Ray.h"

class Material
{
protected:
	Color baseColor;

public:
	//Constructor sets data members
	Material(Color = Color(1, 1, 1));

	//Getter and setter functions:
	void setBaseColor(Color);

	Color getBaseColor() const;

	virtual bool scatter(const Ray& inputRay, Color& attenuation, const Vector3&, const Vector3&, Ray&) const = 0;
};

class DiffuseMaterial : public Material
{
public:
	DiffuseMaterial(Color = Color(1, 1, 1));

	virtual bool scatter(const Ray& inputRay, Color& attenuation, const Vector3&, const Vector3&, Ray&) const override;
};

class MetalMaterial : public Material
{
public:
	MetalMaterial(Color = Color(1, 1, 1));

	virtual bool scatter(const Ray& inputRay, Color& attenuation, const Vector3&, const Vector3&, Ray&) const override;
};

class GlassMaterial : public Material
{
public:
	GlassMaterial(Color = Color(1, 1, 1));

	virtual bool scatter(const Ray& inputRay, Color& attenuation, const Vector3&, const Vector3&, Ray&) const override;
};