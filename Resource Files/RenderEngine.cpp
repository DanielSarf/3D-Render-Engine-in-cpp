#include "../Header Files/RenderEngine.h"

RenderEngine::RenderEngine(Scene& inputScene) : pixels(inputScene.getWidth(), inputScene.getHeight())
{
	height = inputScene.getHeight();
	width = inputScene.getWidth();

	aspectRatio = float(width) / height;

	x0 = -1;
	x1 = 1;
	xStep = (x1 - x0) / (width - 1);

	y0 = -1 / aspectRatio;
	y1 = 1 / aspectRatio;
	yStep = (y1 - y0) / (height - 1);

	camera = inputScene.getCamera();

	float x, y;

	for (int i = 0; i < height; i++)
	{
		y = y0 + i * yStep;

		for (int j = 0; j < width; j++)
		{
			x = x0 + j * xStep;

			Ray ray(*camera, (Vector3(x, y, 0) - *camera));

			pixels.setPixel(j, i, rayTrace(ray, inputScene));
		}
	}

	pixels.writeFile();
}

Color RenderEngine::rayTrace(Ray & inputRay, Scene & inputScene) const
{
	Color color;

	float hitDistance = NULL;
	Object* objectHit = NULL;

	findNearest(objectHit, hitDistance, inputRay, inputScene);

	if (objectHit == NULL)
	{
		return color;
	}

	Vector3 hitPosition = inputRay.getOrigin() + inputRay.getDirection() * hitDistance;

	color = color + colorAt(objectHit, hitPosition, inputScene);

	return color;
}

void RenderEngine::findNearest(Object * &objectHit, float& hitDistance, Ray & inputRay, Scene & inputScene) const
{
	float minimumDistance = NULL;

	for (int i = 0; i < (*inputScene.getObjects()).size(); i++)
	{
		float distance = NULL;

		distance = (*inputScene.getObjects())[i].intersections(inputRay);

		if (distance != NULL && (objectHit == NULL || distance < minimumDistance))
		{
			minimumDistance = distance;

			objectHit = &(*inputScene.getObjects())[i];
		}
	}

	hitDistance = minimumDistance;
}

Color RenderEngine::colorAt(Object * &objecHit, Vector3 & hitPosition, Scene & inputScene) const
{
	return (*objecHit).getMaterial();
}