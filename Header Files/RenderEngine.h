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

public:
	RenderEngine(Scene&, int, bool = false);

	void render(Scene&, int, bool = false) const;

	Color rayTrace(Ray, Scene&, int) const;

	void findNearest(Sphere*&, float&, Ray&, Scene&) const;

	Color colorAt(Sphere*&, Vector3&, Vector3&, Scene&) const;

	//void displayProgress(float) const;

	void refreshSettings(Scene&);

	void outputImage(fileTypes, int);
};