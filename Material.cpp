#include "Material.h"

Material::Material(Color inputColor, float inputRoughness)
{
	baseColor = inputColor;
    roughness = inputRoughness;
}

void Material::setBaseColor(Color inputColor)
{
	baseColor = inputColor;
}

void Material::setRoughness(float inputRoughness)
{
    roughness = inputRoughness;
}

Color Material::getBaseColor() const
{
	return baseColor;
}

float Material::getRoughness() const
{
    return roughness;
}

DiffuseMaterial::DiffuseMaterial(Color inputColor, float inputRoughness)
{
    baseColor = inputColor;
    roughness = inputRoughness;
}

bool DiffuseMaterial::scatter(const Ray &inputRay, Color &attenuation, const Vector3 &hitPosition, const Vector3 &hitNormal, Ray &scatteredRay) const
{
    //scatterDirection is the next direction the ray should bounce off to
    Vector3 scatterDirection = hitNormal + Vector3().randomPointOnUnitSphereSurface();

    if (scatterDirection.nearZero())
    {
        scatterDirection = hitNormal;
    }

    scatteredRay = Ray(hitPosition, scatterDirection);
    
    attenuation = baseColor;
    
    return true;
}

MetalMaterial::MetalMaterial(Color inputColor, float inputRoughness)
{
    baseColor = inputColor;
    roughness = inputRoughness;
}

bool MetalMaterial::scatter(const Ray& inputRay, Color& attenuation, const Vector3& hitPosition, const Vector3& hitNormal, Ray& scatteredRay) const
{
    //reflectedDirection is the next direction the ray should bounce off to
    Vector3 reflectedDirection = Vector3().reflect(inputRay.getDirection().normalize(), hitNormal);

    scatteredRay = Ray(hitPosition, reflectedDirection + Vector3().randomPointOnUnitSphereSurface() * roughness);

    attenuation = baseColor;

    return (scatteredRay.getDirection().dotProduct(hitNormal) > 0);
}