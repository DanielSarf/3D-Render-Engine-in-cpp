#include "../Header Files/Scene.h"

Scene::Scene(Camera* inputCamera, std::vector<Light>* inputLights, std::vector<Object>* inputObjects) : camera(inputCamera), lights(inputLights), objects(inputObjects) {}

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

std::vector<Object>* Scene::getObjects() const
{
	return objects;
}