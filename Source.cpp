#include "Vector3.h"
#include "Color.h"
#include "Camera.h"
#include "Material.h"
#include "Light.h"
#include "Object.h"
#include "Ray.h"
#include "Image.h"
#include "Scene.h"
#include "RenderEngine.h"

#include "fileTypes.h"

using namespace std;

int main()
{
	//Configuration
	int WIDTH = 1920;
	int HEIGHT = 1080;
	int STARTFRAME = 1;
	int ENDFRAME = 1;
	int NUMBEROFSAMPLES = 100;
	int DEPTH = 50;
	float FOCALLENGTH = 0.1f;

	//Set Camera
	Camera camera(Vector3(0.0f, 0.35f, 1.0f), WIDTH, HEIGHT, STARTFRAME, ENDFRAME, NUMBEROFSAMPLES, FOCALLENGTH);

	vector<Light> lights;

	/*lights.push_back(Light(Vector3(1.5, 0.5, 10)));

	lights.push_back(Light(Vector3(-0.5, 10.5, 0), Color("#E6E6E6")));*/
	
	DiffuseMaterial blueDiffuse(Color("#0000FF"));

	MetalMaterial redMetal(Color("#FF0000"), 0.0f);

	//GlassMaterial glass(Color("#803980"));

	//List of objects (currently only supports spheres)
	vector<Sphere> objects;

	//Adding Spheres
	objects.push_back(Sphere(Vector3(0.0f, -10000.5f, -1.0f), 10000.0f));

	objects.push_back(Sphere(Vector3(0.75f, 0.1f, -1.0f), 0.6f, &redMetal));

	objects.push_back(Sphere(Vector3(-0.75f, 0.1f, -2.25f), 0.6f, &blueDiffuse));

	objects.push_back(Sphere(Vector3(-2.0f, 0.1f, -2.25f), 0.6f));

	//Scene initialization
	Scene scene(&camera, &lights, &objects);

	//Renderengine initialization
	RenderEngine debugEngine(scene);

	//Start render on CPU
	debugEngine.renderCPU(DEPTH, true);

	//Output rendered image as a .bmp file
	debugEngine.outputImage(fileTypes::BMP, 8);

	system("pause>0");

	return 0;
}