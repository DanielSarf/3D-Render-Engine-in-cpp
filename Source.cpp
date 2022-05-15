#include "Header Files/Vector3.h"
#include "Header Files/Color.h"
#include "Header Files/Material.h"
#include "Header Files/Light.h"
#include "Header Files/Object.h"
#include "Header Files/Ray.h"
#include "Header Files/Image.h"
#include "Header Files/Scene.h"
#include "Header Files/RenderEngine.h"

#include "Header Files/fileTypes.h"

using namespace std;

int main()
{
	int WIDTH = 1920;
	int HEIGHT = 1080;

	Vector3 camera(0, 0, 1);

	vector<Light> lights;

	lights.push_back(Light(Vector3(1.5, 0.5, 10)));

	Material redDiffuseShiny(Color("#FF0000"));

	vector<Object> objects;

	objects.push_back(Object(Vector3(0, 0, 0), 0.5, redDiffuseShiny));

	Scene scene(&camera, &lights, &objects, WIDTH, HEIGHT);

	RenderEngine debugEngine(scene, 1);

	RenderEngine engine(scene);

	engine.outputImage(fileTypes::PPM, 8);

	return 0;
}