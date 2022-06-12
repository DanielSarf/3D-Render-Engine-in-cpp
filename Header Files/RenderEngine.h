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

	//Renders on CPU using multi-threading. If bool is true, prints time taken to render 
	void renderCPU(int, bool = false) const;

	//Bounces ray recursively a specific number of times (the int parameter) and collects color then returns it as a Color object
	Color rayTrace(Ray, int) const;

	//Sets Sphere to nearest sphere hit, sets float to distance to nearest sphere hit
	void findNearest(Sphere*&, float&, Ray&) const;

	//Sets data members again
	void refreshSettings(Scene&);

	//Writes image file to a specific file type and bit depth
	void outputImage(fileTypes, int);
};