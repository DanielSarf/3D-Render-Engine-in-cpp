#pragma once

#include <iostream>
#include <chrono>
#include <thread>

#include "Color.h"
#include "Ray.h"
#include "Image.h"
#include "Scene.h"

#include "fileTypes.h"


class RenderEngine
{
private:
	int height, width, startFrame, endFrame;
	float viewportHeight, viewportWidth, aspectRatio;
	Camera* camera;
	Image pixels;
	Scene scene;

public:
	//Constructor sets all the data members by using getter functions
	RenderEngine(Scene&);

	void renderCPU(int, bool = false) const;

	Color rayTrace(Ray, int) const;

	void findNearest(Sphere*&, float&, Ray&) const;

	void refreshSettings(Scene&);

	void outputImage(fileTypes, int);
};