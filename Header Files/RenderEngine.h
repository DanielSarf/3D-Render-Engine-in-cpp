#pragma once

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
	RenderEngine(Scene&);

	Color rayTrace(Ray&, Scene&) const;

	void findNearest(Object*&, float&, Ray&, Scene&) const;

	Color colorAt(Object*&, Vector3&, Scene&) const;
};