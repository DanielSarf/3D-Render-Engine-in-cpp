#pragma once

#include "Color.h"

class Image
{
private:
	int height, width;
	Color** pixels;

public:
	Image(int, int);

	void setPixel(int, int, Color) const;

	void writeFile() const;

	~Image();
};