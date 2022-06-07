#pragma once

#include "Color.h"

#include "fileTypes.h"

class Image
{
private:
	int height, width;
	Color** pixels;

public:
	Image(int, int);

	void setPixel(int, int, Color) const;

	void writeFile(fileTypes, int) const;

	std::string generateFileName(fileTypes) const;

	void outputPPM(std::string&, int) const;

	void outputBMP(std::string&) const;

	~Image();
};