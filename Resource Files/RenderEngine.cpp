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
}

void RenderEngine::renderCPU(int depth, bool timerMode) const
{
	auto start = std::chrono::high_resolution_clock::now();

	//Number of threads to render on
	const int numberOfThreads = 32;

	//Makes an array of thread objects
	std::thread threads[numberOfThreads];

	//Starts threads with anonymous function
	for (int currentThread = 0; currentThread < numberOfThreads; currentThread++)
	{
		//Anonymous function that runs on a thread
		threads[currentThread] = std::thread([this](int currentThreadNumber, int numberOfThreads, int depth)
			{
				Vector3 cameraLocation = camera->getLocation();

				float focalLength = -(camera->getFocalLength());

				//Finds width range of pixels to render
				int startWidthRange = (width / numberOfThreads) * currentThreadNumber;

				int endWidthRange = startWidthRange + (width / numberOfThreads);
				
				//At the last iteration it sets endWidthRange = width, to make sure there is not any width left
				if (currentThreadNumber == numberOfThreads - 1)
				{
					endWidthRange = width;
				}

				//Runs for each pixel
				for (int j = height - 1; j >= 0; j--)
				{
					for (int i = startWidthRange; i < endWidthRange; i++)
					{
						Color rayTracedColor(0, 0, 0);

						//Runs for each sample
						for (int currentSample = 0; currentSample < camera->getNumberOfSamples(); currentSample++)
						{
							//Finds u and v coordinates to shoot ray from camera with a random offset (for anti-aliasing)
							float u = ((i + randomFloat()) / (width - 1) * 2 - 1) * aspectRatio;

							float v = (j + randomFloat()) / (height - 1) * 2 - 1;

							//Sends ray from camera to u and v coordinate with focal length component setting focal length 
							Ray ray(cameraLocation, (Vector3(u, -v, focalLength) - cameraLocation));
				
							rayTracedColor = rayTracedColor + rayTrace(ray, depth);

							//rayTracedColor accumulates color values, so it has to be divided by (current sample + 1)
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
	//If depth is 0, function is stopped recursive function returns black color
	if (depth <= 0)
	{
		return Color(0, 0, 0);
	}

	Color color;

	float hitDistance = NULL;

	// TODO: Make it possible for different Object types
	Sphere* objectHit = NULL;

	findNearest(objectHit, hitDistance, inputRay);

	//If object is not hit, returns color of HDRI
	if (objectHit == NULL)
	{
		//HDRI

		Vector3 unitDirection = inputRay.getDirection();

		float t = 0.5 * (unitDirection.getY() + 1.0);

		return (Color(1.0, 1.0, 1.0) * (1.0 - t) + Color(0.5, 0.7, 1.0) * t);
	}

	Vector3 hitPosition = inputRay.hitPosition(hitDistance);

	Vector3 hitNormal = (*objectHit).normal(hitPosition);

	//Target is the next direction the ray should bounce off to
	Vector3 target = hitNormal + Vector3().randomPointOnUnitSphereSurface();

	return rayTrace(Ray(hitPosition, target), depth - 1) / 2;
}

void RenderEngine::findNearest(Sphere * &objectHit, float &hitDistance, Ray &inputRay) const
{
	float minimumDistance = NULL;

	size_t numberOfObjects = (*scene.getObjects()).size();

	//Iterates over objects in Sphere vector
	for (size_t i = 0; i < numberOfObjects; i++)
	{
		float distance = NULL;

		distance = (*scene.getObjects())[i].intersections(inputRay);

		//Finds minimum distance out of all distances
		if (distance != NULL && (objectHit == NULL || distance < minimumDistance))
		{
			minimumDistance = distance;

			objectHit = &(*scene.getObjects())[i];
		}
	}

	hitDistance = minimumDistance;
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

void RenderEngine::outputImage(fileTypes inputFileType, int inputBitDepth)
{
	pixels.writeFile(inputFileType, inputBitDepth);
}