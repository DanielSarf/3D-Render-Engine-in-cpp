#pragma once

#include "Color.h"

class Image
{
private:
	int height, width, bitDepth;
	Color** pixels;

public:
	Image(int, int, int);

	void setPixel(int, int, Color) const;

	void writeFile() const;

	~Image();
};