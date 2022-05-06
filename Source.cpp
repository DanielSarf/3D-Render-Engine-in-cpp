#pragma warning(disable : 4996)

#include <iostream>
#include <ctime>
#include <fstream>
#include <string>

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
	Color **pixels; //pointer of pointers

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

class Sphere
{
private:
	Vector3 location;
	float radius;
	Material material;

public:
	Sphere(Vector3 inputLocation, float inputRadius, Material inputMaterial) : location(inputLocation), radis(inputRadius), material(inputMaterial) {}


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
};

class Scene
{
private:
	Vector3 camera;
	objects;
	int height, width;

public:
	Scene(Vector3 inputCamera, objects, int width, int height) : {}

};

void main()
{
	int width = 320;

	int height = 200;

	Vector3 camera(0, 0, -1);

	objects = [Sphere(Vector3(0, 0, 0), 0.5, Color("#FF0000"))];

	Scene scene(camera, objects, width, height);

	engine.RenderEngine();

	image = engine.render(scene);

	image.writeFile();
}