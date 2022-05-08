#include "../Header Files/Material.h"

Material::Material(Color inputColor, float inputAmbient, float inputDiffuse, float inputSpecular)
{
	color = inputColor;
	ambient = inputAmbient;
	diffuse = inputDiffuse;
	specular = inputSpecular;
}