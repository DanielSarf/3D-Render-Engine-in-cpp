#pragma once

#include <iostream>
#include <chrono>

#include "Color.h"
#include "Ray.h"
#include "Image.h"
#include "Scene.h"

#include "fileTypes.h"


class RenderEngine
{
private:
	int height, width, startFrame, endFrame;
	float aspectRatio, x0, x1, xStep, y0, y1, yStep;
	Camera* camera;
	Image pixels;

public:
	RenderEngine(Scene&, bool = false);

	void render(Scene&, bool) const;

	Color rayTrace(Ray&, Scene&) const;

	void findNearest(Object*&, float&, Ray&, Scene&) const;

	Color colorAt(Object*&, Vector3&, Vector3&, Scene&) const;

	void displayProgress(float) const;

	void refreshSettings(Scene&);

	void outputImage(fileTypes, int);
};