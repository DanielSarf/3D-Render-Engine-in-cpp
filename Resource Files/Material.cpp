#include "../Header Files/Material.h"

Material::Material(Color inputColor, Color inputAmbient, float inputDiffuse, float inputSpecular)
{
	color = inputColor;
	ambient = inputAmbient;
	diffuse = inputDiffuse;
	specular = inputSpecular;
}

void Material::setColor(Color inputColor)
{
	color = inputColor;
}

void Material::setAmbient(float inputAmbient)
{
	ambient = inputAmbient;
}

void Material::setDiffuse(float inputDiffuse)
{
	diffuse = inputDiffuse;
}

void Material::setSpecular(float inputSpecular)
{
	specular = inputSpecular;
}

Color Material::getColor()
{
	return color;
}

Color Material::getAmbient()
{
	return ambient;
}

float Material::getDiffuse()
{
	return diffuse;
}

float Material::getSpecular()
{
	return specular;
}

Color Material::colorAtMaterial()
{
	return color;
}