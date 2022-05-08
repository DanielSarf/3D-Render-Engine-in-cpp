#include "Header Files/Vector3.h"
#include "Header Files/Color.h"
#include "Header Files/Material.h"
#include "Header Files/Light.h"
#include "Header Files/Object.h"
#include "Header Files/Ray.h"
#include "Header Files/Image.h"
#include "Header Files/Scene.h"
#include "Header Files/RenderEngine.h"

using namespace std;

void main()
{
	Vector3 camera(0, 0, -1);

	vector<Light> lights;

	lights.push_back(Light(Vector3(1.5, -0.5, -10), Color("#FFFFFF"), 100));

	vector<Object> objects;

	objects.push_back(Object(Vector3(0, 0, 0), 0.5, Color("#FF0000")));

	Scene scene(&camera, &lights, &objects, 320, 200);

	RenderEngine engine(scene);
}