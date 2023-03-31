#pragma once

#include "Color.h"

#include "fileTypes.h"

class Image
{
private:
	int height, width;
	Color** pixels;

public:
	//Constructor sets pixels as a 2D array of Color objects
	Image(int, int);

	//Sets an element in the 2D array to a Color object
	void setPixel(int, int, Color) const;

	//Writes image file to a specific file type and bit depth
	void writeFile(fileTypes, int) const;

	//Returns a string containing the current date and time and ends with file type
	std::string generateFileName(fileTypes) const;

	//Outputs .ppm file
	void outputPPM(std::string&, int) const;

	//Outputs .bmp file
	void outputBMP(std::string&) const;

	//Deletes all the elements of the 2D array
	~Image();
};