#pragma warning(disable: 4996)

#include "../Header Files/Image.h"

Image::Image(int inputWidth, int inputHeight, int inputBitDepth) : width(inputWidth), height(inputHeight), bitDepth(inputBitDepth)
{
	pixels = new Color * [inputHeight];

	for (int h = 0; h < inputHeight; h++)
	{
		pixels[h] = new Color[inputWidth];

		for (int w = 0; w < inputWidth; w++)
		{
			pixels[h][w] = Color(0, 0, 0);
		}
	}
}

void Image::setPixel(int w, int h, Color color) const
{
	pixels[h][w] = color;
}

void Image::writeFile() const
{
	time_t curr_time;
	tm* curr_tm;
	char date[50];

	time(&curr_time);
	curr_tm = localtime(&curr_time);

	strftime(date, 50, "%d%m%Y%H%M%S", curr_tm);

	std::string nameOfFile = date;

	nameOfFile.append(".ppm");

	std::ofstream imageFile;

	imageFile.open(nameOfFile);

	int maxColorValue = (pow(2, bitDepth) - 1);

	imageFile << "P3 " << width << " " << height << std::endl << maxColorValue << std::endl;

	for (int h = 0; h < height; h++)
	{
		for (int w = 0; w < width; w++)
		{
			imageFile << (int(pixels[h][w].getR() * maxColorValue) > maxColorValue ? maxColorValue : int(pixels[h][w].getR() * maxColorValue)) 
			   << " " << (int(pixels[h][w].getG() * maxColorValue) > maxColorValue ? maxColorValue : int(pixels[h][w].getG() * maxColorValue))
			   << " " << (int(pixels[h][w].getB() * maxColorValue) > maxColorValue ? maxColorValue : int(pixels[h][w].getB() * maxColorValue)) << " ";
		}

		imageFile << std::endl;
	}

	imageFile.close();
}

Image::~Image()
{
	for (int h = 0; h < height; h++)
	{
		delete[] pixels[h];
	}

	delete[] pixels;
}
