#include "../Header Files/RenderEngine.h"

RenderEngine::RenderEngine(Scene &inputScene, int timerMode) : pixels(inputScene.getWidth(), inputScene.getHeight())
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

	auto start = std::chrono::high_resolution_clock::now();

	for (int i = 0; i < height; i++)
	{
		y = y0 + i * yStep;

		for (int j = 0; j < width; j++)
		{
			x = x0 + j * xStep;

			Ray ray(*camera, (Vector3(x, -y) - *camera));

			if (timerMode)
			{
				rayTrace(ray, inputScene);
			}
			else
			{
				pixels.setPixel(j, i, rayTrace(ray, inputScene));
			}
		}

		if (!timerMode)
		{
			displayProgress((y * aspectRatio + 1) / 2);
		}
	}

	auto stop = std::chrono::high_resolution_clock::now();

	if (timerMode)
	{
		std::cout << "Time taken to render is: " << float(std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count()) / 1000000 << " seconds\n\n";
	}
}

Color RenderEngine::rayTrace(Ray &inputRay, Scene &inputScene) const
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

	Vector3 hitNormal = (*objectHit).normal(hitPosition);

	color = color + colorAt(objectHit, hitPosition, hitNormal, inputScene);

	return color;
}

void RenderEngine::findNearest(Object * &objectHit, float &hitDistance, Ray &inputRay, Scene &inputScene) const
{
	float minimumDistance = NULL;

	size_t numberOfObjects = (*inputScene.getObjects()).size();

	for (size_t i = 0; i < numberOfObjects; i++)
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

Color RenderEngine::colorAt(Object *&objectHit, Vector3 &hitPosition, Vector3 &hitNormal, Scene &inputScene) const
{
	Material objectMaterial = (*objectHit).getMaterial();

	Color objectColor = objectMaterial.colorAtMaterial();

	Vector3 toCam = *(inputScene.getCamera()) - hitPosition;

	float specularK = 50;

	Color color = Color() + objectMaterial.getAmbient();

	size_t numberOfLights = (*inputScene.getLights()).size();
	
	for (size_t i = 0; i < numberOfLights; i++)
	{
		Ray toLight(hitPosition, (*inputScene.getLights())[i].getLocation() - hitPosition);

		float hitNormalDotToLightDirection = hitNormal.dotProduct(toLight.getDirection());

		color = color + objectColor * objectMaterial.getDiffuse() * (hitNormalDotToLightDirection > 0 ? hitNormalDotToLightDirection : 0);

		Vector3 halfVector = (toLight.getDirection() + toCam).normalize();

		float hitNormalDotHalfVector = hitNormal.dotProduct(halfVector);

		color = color + (*inputScene.getLights())[i].getColor() * objectMaterial.getSpecular() * pow((hitNormalDotHalfVector > 0 ? hitNormalDotHalfVector : 0), specularK);
	}

	return color;
}

void RenderEngine::displayProgress(float normalizedProgress) const
{
	int barWidth = 70;

	std::cout << "[";

	int pos = int(barWidth * normalizedProgress);

	for (int i = 0; i < barWidth; ++i) {
		if (i < pos) std::cout << "=";
		else if (i == pos) std::cout << ">";
		else std::cout << " ";
	}

	std::cout << "] " << int(normalizedProgress * 100) << " %\r";

	std::cout.flush();
}

void RenderEngine::outputImage(fileTypes inputFileType, int inputBitDepth)
{
	pixels.writeFile(inputFileType, inputBitDepth);
}