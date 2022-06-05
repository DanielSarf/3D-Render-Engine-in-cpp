#include "Header Files/Vector3.h"
#include "Header Files/Color.h"
#include "Header Files/Camera.h"
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
	int WIDTH = 320;
	int HEIGHT = 200;
	int STARTFRAME = 1;
	int ENDFRAME = 1;
	int NUMBEROFSAMPLES = 100;
	int DIFFUSEDEPTH = 3;
	float FOCALLENGTH = 0.1;

	Camera camera(Vector3(0, 0.35, 1), WIDTH, HEIGHT, STARTFRAME, ENDFRAME, NUMBEROFSAMPLES, FOCALLENGTH);

	vector<Light> lights;

	lights.push_back(Light(Vector3(1.5, 0.5, 10)));

	lights.push_back(Light(Vector3(-0.5, 10.5, 0), Color("#E6E6E6")));

	Material chequeredMaterial(Color("#FF0000"));

	Material blueDiffuseShiny(Color("#0000FF"));

	Material pinkDiffuseShiny(Color("#803980"));

	vector<Object> objects;

	objects.push_back(Object(Vector3(0, -10000.5, -1), 10000, chequeredMaterial));

	objects.push_back(Object(Vector3(0.75, 0.1, -1), 0.6, blueDiffuseShiny));

	objects.push_back(Object(Vector3(-0.75, 0.1, -2.25), 0.6, pinkDiffuseShiny));

	Scene scene(&camera, &lights, &objects);

	RenderEngine debugEngine(scene, DIFFUSEDEPTH, 1);

	debugEngine.outputImage(fileTypes::PPM, 8);

	return 0;
}