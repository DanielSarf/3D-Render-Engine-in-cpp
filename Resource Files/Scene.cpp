#include "../Header Files/Scene.h"

Scene::Scene(Vector3* inputCamera, std::vector<Light>* inputLights, std::vector<Object>* inputObjects, int inputWidth, int inputHeight) : camera(inputCamera), lights(inputLights), objects(inputObjects), width(inputWidth), height(inputHeight) {}

void Scene::setCamera(Vector3* inputCamera)
{
	camera = inputCamera;
}

void Scene::setHeight(int inputHeight)
{
	height = inputHeight;
}

void Scene::setWidth(int inputWidth)
{
	width = inputWidth;
}

Vector3* Scene::getCamera() const
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

int Scene::getHeight() const
{
	return height;
}

int Scene::getWidth() const
{
	return width;
}