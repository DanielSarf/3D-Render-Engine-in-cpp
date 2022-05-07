#pragma warning(disable : 4996)

#include <iostream>
#include <ctime>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class Vector3
{
private:
	float x, y, z;

public:
	Vector3(float inputX = 0.0, float inputY = 0.0, float inputZ = 0.0) : x(inputX), y(inputY), z(inputZ) {}

	Vector3 operator+(Vector3 other) const
	{
		return Vector3(x + other.x, y + other.y, z + other.z);
	}

	Vector3 operator-(Vector3 other) const
	{
		return Vector3(x - other.x, y - other.y, z - other.z);
	}

	Vector3 operator*(float other) const
	{
		return Vector3(x * other, y * other, z * other);
	}

	Vector3 operator/(float other) const
	{
		return Vector3(x / other, y / other, z / other);
	}
	
	void setAll(float inputX, float inputY, float inputZ)
	{
		x = inputX;
		y = inputY;
		z = inputZ;
	}

	void setX(float inputX)
	{
		x = inputX;
	}

	void setY(float inputY)
	{
		y = inputY;
	}

	void setZ(float inputZ)
	{
		z = inputZ;
	}

	float getX() const
	{
		return x;
	}

	float getY() const
	{
		return y;
	}

	float getZ() const
	{
		return z;
	}

	float dotProduct() const
	{
		return (x * x + y * y + z * z);
	}

	float dotProduct(Vector3 other) const
	{
		return (x * other.x + y * other.y + z * other.z);
	}

	float magnitude() const
	{
		return sqrt(dotProduct());
	}

	Vector3 normalize() const
	{
		return (*this) / magnitude();
	}

	void printVector()
	{
		cout << "(" << x << ", " << y << ", " << z << ")" << endl;
	}
};

class Color
{
private:
	unsigned char r, g, b;

public:
	Color(string hexCode)
	{
		r = 16 * hexCharToDecInt(hexCode[1]) + hexCharToDecInt(hexCode[2]);
		g = 16 * hexCharToDecInt(hexCode[3]) + hexCharToDecInt(hexCode[4]);
		b = 16 * hexCharToDecInt(hexCode[5]) + hexCharToDecInt(hexCode[6]);
	}

	Color(unsigned char inputR = 0, unsigned char inputG = 0, unsigned char inputB = 0) : r(inputR), g(inputG), b(inputB) {}

	Color operator+(Color other) const
	{
		return Color(r + other.r, g + other.g, b + other.b);
	}

	Color operator*(float other) const
	{
		return Color(r * other, g * other, b * other);
	}

	void setAll(unsigned char inputR = 0, unsigned char inputG = 0, unsigned char inputB = 0)
	{
		r = inputR;
		g = inputG;
		b = inputB;
	}

	void setR(unsigned char inputR)
	{
		r = inputR;
	}

	void setG(unsigned char inputG)
	{
		g = inputG;
	}

	void setB(unsigned char inputB)
	{
		b = inputB;
	}

	short getR() const
	{
		return r;
	}

	short getG() const
	{
		return g;
	}

	short getB() const
	{
		return b;
	}

	int hexCharToDecInt(char inputChar)
	{
		string tempString = " ";

		tempString[0] = inputChar;

		return stoul(tempString, NULL, 16);
	}
};

class Image
{
private:
	int height, width;
	Color **pixels;

public:
	Image(int inputWidth, int inputHeight) : width(inputWidth), height(inputHeight)
	{
		pixels = new Color*[inputHeight];

		for (int h = 0; h < inputHeight; h++)
		{
			pixels[h] = new Color[inputWidth];

			for (int w = 0; w < inputWidth; w++)
			{
				pixels[h][w] = Color(0, 0, 0);
			}
		}
	}

	void setPixel(int w, int h, Color color)
	{
		pixels[h][w] = color;
	}

	void writeFile()
	{
		time_t curr_time;
		tm* curr_tm;
		char date[50];

		time(&curr_time);
		curr_tm = localtime(&curr_time);

		strftime(date, 50, "%d%m%Y%H%M%S", curr_tm);

		string nameOfFile = date;

		nameOfFile.append(".ppm");

		ofstream imageFile;

		imageFile.open(nameOfFile);

		imageFile << "P3 " << width << " " << height << endl << "255" << endl;

		for (int h = 0; h < height; h++)
		{
			for (int w = 0; w < width; w++)
			{
				imageFile << pixels[h][w].getR() << " " << pixels[h][w].getG() << " " << pixels[h][w].getB() << " ";
			}

			imageFile << endl;
		}

		imageFile.close();
	}

	~Image()
	{
		for (int h = 0; h < height; h++)
		{
			delete[] pixels[h];
		}

		delete[] pixels;
	}
};

class Ray
{
private:
	Vector3 origin, direction;

public:
	Ray(Vector3 inputOrigin, Vector3 inputDirection) : origin(inputOrigin), direction(inputDirection.normalize()) {}

	void setOrigin(Vector3 inputOrigin)
	{
		origin = inputOrigin;
	}

	void setDirection(Vector3 inputDirection)
	{
		direction = inputDirection.normalize();
	}

	Vector3 getOrigin()
	{
		return origin;
	}

	Vector3 getDirection()
	{
		return direction;
	}
};

class Object
{
private:
	Vector3 location;
	float radius;
	Color material;

public:
	Object(Vector3 inputLocation, float inputRadius, Color inputMaterial) : location(inputLocation), radius(inputRadius), material(inputMaterial) {}

	float intersections(Ray ray)
	{
		Vector3 sphereToRay = ray.getOrigin() - location;

		float b = 2 * ray.getDirection().dotProduct(sphereToRay);

		float c = sphereToRay.dotProduct() - radius * radius;

		float discriminant = b * b - 4 * c;

		if (discriminant >= 0)
		{
			float distance = (-b - sqrt(discriminant)) / 2;

			if (distance > 0)
			{
				return distance;
			}
		}

		return NULL;
	}

	Color getMaterial()
	{
		return material;
	}
};

class Scene
{
private:
	Vector3 camera;
	vector<Object> *objects;
	int height, width;

public:
	Scene(Vector3 inputCamera, vector<Object> *inputObjects, int inputWidth, int inputHeight) : camera(inputCamera), objects(inputObjects), width(inputWidth), height(inputHeight) {}


	void setCamera(Vector3 inputCamera)
	{
		camera = inputCamera;
	}

	void setHeight(int inputHeight)
	{
		height = inputHeight;
	}

	void setWidth(int inputWidth)
	{
		width = inputWidth;
	}

	Vector3 getCamera()
	{
		return camera;
	}

	vector<Object>* getObjects()
	{
		return objects;
	}

	int getHeight()
	{
		return height;
	}

	int getWidth()
	{
		return width;
	}
};

class RenderEngine
{
private:
	int height, width;
	float aspectRatio, x0, x1, xStep, y0, y1, yStep;
	Vector3 camera;
	Image pixels;

public:
	RenderEngine(Scene &inputScene) : pixels(inputScene.getWidth(), inputScene.getHeight())
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

		for (int i = 0; i < height; i++)
		{
			y = y0 + i * yStep;

			for (int j = 0; j < width; j++)
			{
				x = x0 + j * xStep;

				Ray ray(camera, (Vector3(x, y, 0) - camera));

				pixels.setPixel(j, i, rayTrace(ray, inputScene));
			}
		}

		pixels.writeFile();
	}

	Color rayTrace(Ray inputRay, Scene &inputScene)
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

		color = color + colorAt(objectHit, hitPosition, inputScene);
	}

	void findNearest(Object* &objectHit, float &hitDistance, Ray &inputRay, Scene& inputScene)
	{
		float minimumDistance = NULL;

		for (int i = 0; i < (*inputScene.getObjects()).size(); i++)
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

	Color colorAt(Object* objecHit, Vector3 hitPosition, Scene &inputScene)
	{
		return (*objecHit).getMaterial();
	}
};

void main()
{
	Vector3 camera(0, 0, -1);

	vector<Object> objects;

	objects.push_back(Object(Vector3(0, 0, 0), 0.5, Color("#FF0000")));

	Scene scene(camera, &objects, 320, 200);

	RenderEngine engine(scene);
}