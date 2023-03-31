#include "Scene.h"

Scene::Scene(Camera* inputCamera, std::vector<Light>* inputLights, std::vector<Sphere>* inputObjects) : camera(inputCamera), lights(inputLights), objects(inputObjects) {}

void Scene::setCamera(Camera* inputCamera)
{
	camera = inputCamera;
}

Camera* Scene::getCamera() const
{
	return camera;
}

std::vector<Light>* Scene::getLights() const
{
	return lights;
}

std::vector<Sphere>* Scene::getObjects() const
{
	return objects;
}