#pragma once

#include <iostream>
#include <chrono>

#include "Color.h"
#include "Ray.h"
#include "Image.h"
#include "Scene.h"

class RenderEngine
{
private:
	int height, width;
	float aspectRatio, x0, x1, xStep, y0, y1, yStep;
	Vector3* camera;
	Image pixels;

public:
	RenderEngine(Scene&, int = 0);

	Color rayTrace(Ray&, Scene&) const;

	void findNearest(Object*&, float&, Ray&, Scene&) const;

	Color colorAt(Object*&, Vector3&, Vector3&, Scene&) const;

	void displayProgress(float) const;
};