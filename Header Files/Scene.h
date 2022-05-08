#pragma once

#include <vector>

#include "Vector3.h"
#include "Light.h"
#include "Object.h"

class Scene
{
private:
	Vector3* camera;
	std::vector<Light>* lights;
	std::vector<Object>* objects;
	int height, width;

public:
	Scene(Vector3*, std::vector<Light>*, std::vector<Object>*, int, int);

	void setCamera(Vector3*);

	void setHeight(int);

	void setWidth(int);

	Vector3* getCamera() const;

	std::vector<Light>* getLights() const;

	std::vector<Object>* getObjects() const;

	int getHeight() const;

	int getWidth() const;
};