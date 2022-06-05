#pragma once

#include "Vector3.h"

class Camera
{
private:
	Vector3 location;
	int width, height, startFrame, endFrame, numberOfSamples;
	float focalLength;

public:
	Camera(Vector3 = Vector3(0, 0, 0), int = 1920, int = 1080, int = 1, int = 1, int = 100, float = 0);

	void setLocation(Vector3 inputLocation);

	void setWidth(int);

	void setHeight(int);

	void setStartFrame(int);

	void setEndFrame(int);

	void setNumberOfSamples(int);

	void setFocalLength(float);
	
	Vector3 getLocation() const;

	int getWidth() const;

	int getHeight() const;

	int getStartFrame() const;

	int getEndFrame() const;

	int getNumberOfSamples() const;

	float getFocalLength() const;
};