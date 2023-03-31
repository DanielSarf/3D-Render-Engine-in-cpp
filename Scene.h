#pragma once

#include <vector>

#include "Camera.h"
#include "Light.h"
#include "Object.h"

class Scene
{
private:
	Camera* camera;
	std::vector<Light>* lights;
	std::vector<Sphere>* objects;

public:
	//Constructor sets data members
	Scene(Camera*, std::vector<Light>*, std::vector<Sphere>*);

	//Getter and setter functions:
	void setCamera(Camera*);

	Camera* getCamera() const;

	std::vector<Light>* getLights() const;

	std::vector<Sphere>* getObjects() const;
};