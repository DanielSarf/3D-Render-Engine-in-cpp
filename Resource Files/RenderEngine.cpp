#include "../Header Files/RenderEngine.h"

RenderEngine::RenderEngine(Scene &inputScene, int depth, bool timerMode) : pixels(inputScene.getCamera()->getWidth(), inputScene.getCamera()->getHeight())
{
	camera = inputScene.getCamera();

	height = camera->getHeight();
	width = camera->getWidth();

	aspectRatio = float(width) / height;

	viewportHeight = 2;
	viewportWidth = viewportHeight * aspectRatio;

	startFrame = camera->getStartFrame();
	endFrame = camera->getEndFrame();

	for (int currentFrame = startFrame; currentFrame <= endFrame; currentFrame++)
	{
		//keyframe(currentFrame);

		render(inputScene, depth, timerMode);
	}
}

void RenderEngine::render(Scene& inputScene, int depth, bool timerMode) const
{
	auto start = std::chrono::high_resolution_clock::now();

	const int numberOfThreads = 32;

	std::thread threads[numberOfThreads];

	for (int currentThread = 0; currentThread < numberOfThreads; currentThread++)
	{
		threads[currentThread] = std::thread([this](int currentThreadNumber, int numberOfThreads, Scene& inputScene, int depth)
			{
				Vector3 cameraLocation = camera->getLocation();

				float focalLength = -(camera->getFocalLength());

				int startHeightRange = height - (height / numberOfThreads) * currentThreadNumber - 1;

				int endHeightRange = startHeightRange - (height / numberOfThreads);

				int startWidthRange = (width / numberOfThreads) * currentThreadNumber;

				int endWidthRange = startWidthRange + (width / numberOfThreads);
				
				if (currentThreadNumber == numberOfThreads - 1)
				{
					endHeightRange = height - 1;

					endWidthRange = 0;
				}

				for (int j = startHeightRange; j >= endHeightRange; j--)
				{
					for (int i = startWidthRange; i < startWidthRange; i++)
					{
						Color rayTracedColor(0, 0, 0);

						for (int currentSample = 0; currentSample < camera->getNumberOfSamples(); currentSample++)
						{
							float u = ((i + randomFloat()) / (width - 1) * 2 - 1) * aspectRatio;

							float v = (j + randomFloat()) / (height - 1) * 2 - 1;

							Ray ray(cameraLocation, (Vector3(u, -v, focalLength) - cameraLocation));
				
							rayTracedColor = rayTracedColor + rayTrace(ray, inputScene, depth);
						}

						pixels.setPixel(i, j, rayTracedColor / float(camera->getNumberOfSamples()));
					}
				}
			}, currentThread, numberOfThreads, inputScene, depth);
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

Color RenderEngine::rayTrace(Ray inputRay, Scene &inputScene, int depth) const
{
	if (depth <= 0)
	{
		return Color(0, 0, 0);
	}

	Color color;

	float hitDistance = NULL;

	// TODO: Make it possible for different Object types
	Sphere* objectHit = NULL;

	findNearest(objectHit, hitDistance, inputRay, inputScene);

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

	return rayTrace(Ray(hitPosition, target), inputScene, depth - 1) / 2;
}

void RenderEngine::findNearest(Sphere * &objectHit, float &hitDistance, Ray &inputRay, Scene &inputScene) const
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

Color RenderEngine::colorAt(Sphere*& objectHit, Vector3& hitPosition, Vector3& hitNormal, Scene& inputScene) const
{
	return Color();
}

void RenderEngine::refreshSettings(Scene &inputScene)
{
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