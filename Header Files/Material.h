#pragma once

#include "Vector3.h"
#include "Color.h"

class Material
{
private:
	Color color;
	Color ambient;
	float diffuse;
	float specular;

public:
	Material(Color, Color = Color("#3F3F3F"), float = 1, float = 1);

	void setColor(Color);

	void setAmbient(float);

	void setDiffuse(float);

	void setSpecular(float);

	Color getColor();

	Color getAmbient();

	float getDiffuse();

	float getSpecular();

	Color colorAtMaterial();
};