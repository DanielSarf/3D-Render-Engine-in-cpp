#include "../Header Files/RenderEngine.h"

RenderEngine::RenderEngine(Scene &inputScene) : scene(inputScene), pixels(inputScene.getCamera()->getWidth(), inputScene.getCamera()->getHeight())
{
	camera = inputScene.getCamera();

	height = camera->getHeight();
	width = camera->getWidth();

	aspectRatio = float(width) / height;

	viewportHeight = 2;
	viewportWidth = viewportHeight * aspectRatio;

	startFrame = camera->getStartFrame();
	endFrame = camera->getEndFrame();

	//for (int currentFrame = startFrame; currentFrame <= endFrame; currentFrame++)
	//{
	//	//keyframe(currentFrame);

	//	render(depth, timerMode);
	//}
}

void RenderEngine::render(int depth, bool timerMode) const
{
	auto start = std::chrono::high_resolution_clock::now();

	const int numberOfThreads = 32;

	std::thread threads[numberOfThreads];

	for (int currentThread = 0; currentThread < numberOfThreads; currentThread++)
	{
		threads[currentThread] = std::thread([this](int currentThreadNumber, int numberOfThreads, int depth)
			{
				Vector3 cameraLocation = camera->getLocation();

				float focalLength = -(camera->getFocalLength());

				int startWidthRange = (width / numberOfThreads) * currentThreadNumber;

				int endWidthRange = startWidthRange + (width / numberOfThreads);
				
				if (currentThreadNumber == numberOfThreads - 1)
				{
					endWidthRange = width;
				}

				for (int j = height - 1; j >= 0; j--)
				{
					for (int i = startWidthRange; i < endWidthRange; i++)
					{
						Color rayTracedColor(0, 0, 0);

						for (int currentSample = 0; currentSample < camera->getNumberOfSamples(); currentSample++)
						{
							float u = ((i + randomFloat()) / (width - 1) * 2 - 1) * aspectRatio;

							float v = (j + randomFloat()) / (height - 1) * 2 - 1;

							Ray ray(cameraLocation, (Vector3(u, -v, focalLength) - cameraLocation));
				
							rayTracedColor = rayTracedColor + rayTrace(ray, depth);

							pixels.setPixel(i, j, rayTracedColor / float(currentSample + 1));
						}
					}
				}
			}, currentThread, numberOfThreads, depth);
	}

	for (int i = 0; i < numberOfThreads; i++)
	{
		threads[i].join();
	}

	auto stop = std::chrono::high_resolution_clock::now();

	if (timerMode)
	{
		std::cout << "Time taken to render is: " << float(std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count()) / 1000000 << " seconds\n\n";
	}
}

Color RenderEngine::rayTrace(Ray inputRay, int depth) const
{
	if (depth <= 0)
	{
		return Color(0, 0, 0);
	}

	Color color;

	float hitDistance = NULL;

	// TODO: Make it possible for different Object types
	Sphere* objectHit = NULL;

	findNearest(objectHit, hitDistance, inputRay);

	if (objectHit == NULL)
	{
		//HDRI

		Vector3 unitDirection = inputRay.getDirection();

		float t = 0.5 * (unitDirection.getY() + 1.0);

		return (Color(1.0, 1.0, 1.0) * (1.0 - t) + Color(0.5, 0.7, 1.0) * t);
	}

	Vector3 hitPosition = inputRay.hitPosition(hitDistance);

	Vector3 hitNormal = (*objectHit).normal(hitPosition);

	Vector3 target = hitNormal + Vector3().randomPointOnUnitSphereSurface();

	return rayTrace(Ray(hitPosition, target), depth - 1) / 2;
}

void RenderEngine::findNearest(Sphere * &objectHit, float &hitDistance, Ray &inputRay) const
{
	float minimumDistance = NULL;

	size_t numberOfObjects = (*scene.getObjects()).size();

	for (size_t i = 0; i < numberOfObjects; i++)
	{
		float distance = NULL;

		distance = (*scene.getObjects())[i].intersections(inputRay);

		if (distance != NULL && (objectHit == NULL || distance < minimumDistance))
		{
			minimumDistance = distance;

			objectHit = &(*scene.getObjects())[i];
		}
	}

	hitDistance = minimumDistance;
}

Color RenderEngine::colorAt(Sphere*& objectHit, Vector3& hitPosition, Vector3& hitNormal) const
{
	return Color();
}

void RenderEngine::refreshSettings(Scene &inputScene)
{
	scene = inputScene;

	pixels.~Image();
	pixels = Image(inputScene.getCamera()->getWidth(), inputScene.getCamera()->getHeight());

	height = camera->getHeight();
	width = camera->getWidth();

	aspectRatio = float(width) / height;

	viewportHeight = 2;
	viewportWidth = viewportHeight * aspectRatio;

	startFrame = camera->getStartFrame();
	endFrame = camera->getEndFrame();
}

//void RenderEngine::displayProgress(float normalizedProgress) const
//{
//	int barWidth = 70;
//
//	std::cout << "[";
//
//	int pos = int(barWidth * normalizedProgress);
//
//	for (int i = 0; i < barWidth; ++i) {
//		if (i < pos) std::cout << "=";
//		else if (i == pos) std::cout << ">";
//		else std::cout << " ";
//	}
//
//	std::cout << "] " << int(normalizedProgress * 100) << " %\r";
//
//	std::cout.flush();
//}

void RenderEngine::outputImage(fileTypes inputFileType, int inputBitDepth)
{
	pixels.writeFile(inputFileType, inputBitDepth);
}