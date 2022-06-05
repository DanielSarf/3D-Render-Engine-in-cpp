#include "../Header Files/Camera.h"

Camera::Camera(Vector3 inputLocation, int inputWidth, int inputHeight, int inputStartFrame, int inputEndFrame, int inputNumberOfSamples, float inputFocalLength)
{
	location = inputLocation;
	width = inputWidth;
	height = inputHeight;
	startFrame = inputStartFrame;
	endFrame = inputEndFrame;
	numberOfSamples = inputNumberOfSamples;
	focalLength = inputFocalLength;
}

void Camera::setLocation(Vector3 inputLocation)
{
	location = inputLocation;
}

void Camera::setWidth(int inputWidth)
{
	width = inputWidth;
}

void Camera::setHeight(int inputHeight)
{
	height = inputHeight;
}

void Camera::setStartFrame(int inputStartFrame)
{
	startFrame = inputStartFrame;
}

void Camera::setEndFrame(int inputEndFrame)
{
	endFrame = inputEndFrame;
}

void Camera::setNumberOfSamples(int inputNumberOfSamples)
{
	numberOfSamples = inputNumberOfSamples;
}

void Camera::setFocalLength(float inputFocalLength)
{
	focalLength = inputFocalLength;
}

Vector3 Camera::getLocation() const
{
	return location;
}

int Camera::getWidth() const
{
	return width;
}

int Camera::getHeight() const
{
	return height;
}

int Camera::getStartFrame() const
{
	return startFrame;
}

int Camera::getEndFrame() const
{
	return endFrame;
}

int Camera::getNumberOfSamples() const
{
	return numberOfSamples;
}

float Camera::getFocalLength() const
{
	return focalLength;
}