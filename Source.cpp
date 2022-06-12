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
	//Configuration
	int WIDTH = 1920;
	int HEIGHT = 1080;
	int STARTFRAME = 1;
	int ENDFRAME = 1;
	int NUMBEROFSAMPLES = 100;
	int DIFFUSEDEPTH = 50;
	float FOCALLENGTH = 0.1;

	//Set Camera
	Camera camera(Vector3(0, 0.35, 1), WIDTH, HEIGHT, STARTFRAME, ENDFRAME, NUMBEROFSAMPLES, FOCALLENGTH);

	//Will add lights functionality later
	vector<Light> lights;

	/*lights.push_back(Light(Vector3(1.5, 0.5, 10)));

	lights.push_back(Light(Vector3(-0.5, 10.5, 0), Color("#E6E6E6")));*/

	//Will add material functionality later
	Material diffuse(Color("#FF0000"));

	Material metal(Color("#0000FF"));

	Material glass(Color("#803980"));

	//List of objects (currently only supports spheres)
	vector<Sphere> objects;

	//Adding Spheres
	objects.push_back(Sphere(Vector3(0, -10000.5, -1), 10000, diffuse));

	objects.push_back(Sphere(Vector3(0.75, 0.1, -1), 0.6, diffuse));

	objects.push_back(Sphere(Vector3(-0.75, 0.1, -2.25), 0.6, metal));

	objects.push_back(Sphere(Vector3(-2, 0.1, -2.25), 0.6, glass));

	//Scene initialization
	Scene scene(&camera, &lights, &objects);

	//Renderengine initialization
	RenderEngine debugEngine(scene);

	//Start render on CPU
	debugEngine.renderCPU(DIFFUSEDEPTH, true);

	//Output rendered image as a .bmp file
	debugEngine.outputImage(fileTypes::BMP, 8);

	return 0;
}