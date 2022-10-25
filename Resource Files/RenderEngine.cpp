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
	const int numberOfThreads = (std::thread::hardware_concurrency() * 2 > 32) ? std::thread::hardware_concurrency() * 2 : 32;

	//Makes an array of thread objects
	std::thread *threads = new std::thread[numberOfThreads];

	//Starts threads with lambda function
	for (int currentThread = 0; currentThread < numberOfThreads; currentThread++)
	{
		//Lambda function that runs on a thread
		threads[currentThread] = std::thread([this](int currentThreadNumber, int numberOfThreads, int depth)
			{
				Vector3 cameraLocation = camera->getLocation();

				float focalLength = -(camera->getFocalLength()) * width * aspectRatio;

				//Finds width range of pixels to render
				int startWidthRange = (width / numberOfThreads) * currentThreadNumber;

				int endWidthRange = startWidthRange + (width / numberOfThreads);
				
				//At the last iteration it sets endWidthRange = width, to make sure there is not any width left
				if (currentThreadNumber == numberOfThreads - 1)
				{
					endWidthRange = width;
				}

				//Runs for each pixel
				for (int j = height - height / 2 - 1; j >= 0 - height / 2; j--)
				{
					for (int i = startWidthRange - width / 2; i < endWidthRange - width / 2; i++)
					{
						Color rayTracedColor(0, 0, 0);

						//Runs for each sample
						for (int currentSample = 0; currentSample < camera->getNumberOfSamples(); currentSample++)
						{
							//Finds u and v coordinates to shoot ray from camera with a random offset from -0.5 to 0.5 (for anti-aliasing)
							float u = i + randomfloat() - 0.5f;

							float v = j + randomfloat() - 0.5f;

							//Sends ray from camera to u and v coordinate with focal length component setting focal length 
							Ray ray(cameraLocation, (Vector3(u, -v, focalLength) - cameraLocation));
				
							rayTracedColor = rayTracedColor + rayTrace(ray, depth);

							//rayTracedColor accumulates color values, so it has to be divided by (current sample + 1)
						}

						pixels.setPixel(i + width / 2, j + height / 2, rayTracedColor / float(camera->getNumberOfSamples()));
					}
				}
			}, currentThread, numberOfThreads, depth);
	}

	for (int i = 0; i < numberOfThreads; i++)
	{
		threads[i].join();
	}

	delete[] threads;

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
		return (Color(0, 0, 0));
	}

	Color color;

	float hitDistance = NULL;

	Sphere* objectHit = nullptr;

	findNearest(objectHit, hitDistance, inputRay);

	//If object is not hit, returns color of HDRI
	if (objectHit == nullptr)
	{
		//HDRI

		return (Color(0.5f, 0.7f, 1.0f));
	}

	Vector3 hitPosition = inputRay.hitPosition(hitDistance);

	Vector3 hitNormal = (*objectHit).normal(hitPosition);

	Ray scatteredRay;

	Color attenuation;

	if (objectHit->getMaterial()->scatter(inputRay, attenuation, hitPosition, hitNormal, scatteredRay))
	{
		return rayTrace(scatteredRay, depth - 1) * attenuation;
	}

	return (Color(0, 0, 0));
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