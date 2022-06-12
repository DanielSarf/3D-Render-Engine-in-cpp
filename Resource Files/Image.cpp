#include "../Header Files/Image.h"

Image::Image(int inputWidth, int inputHeight) : width(inputWidth), height(inputHeight)
{
	//Allocates width * height Color objects for 2D array
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

void Image::writeFile(fileTypes inputFileType, int inputBitDepth) const
{
	std::string nameOfFile = generateFileName(inputFileType);

	//Calls function based on file type
	if (inputFileType == fileTypes::PPM)
	{
		outputPPM(nameOfFile, inputBitDepth);
	}

	if (inputFileType == fileTypes::BMP)
	{
		outputBMP(nameOfFile);
	}
}

std::string Image::generateFileName(fileTypes inputFileType) const
{
	//Sets char array to current date and time in dmYHMS format
	time_t curr_time;
	tm curr_tm;
	char date[50];

	time(&curr_time);
	localtime_s(&curr_tm, &curr_time);

	strftime(date, 50, "%d%m%Y%H%M%S", &curr_tm);

	//Char array used to make string
	std::string nameOfFile = date;

	//String has .[filetype] appended to it
	if (inputFileType == fileTypes::PPM)
	{
		nameOfFile.append(".ppm");
	}

	if (inputFileType == fileTypes::BMP)
	{
		nameOfFile.append(".bmp");
	}

	return nameOfFile;
}

void Image::outputPPM(std::string &nameOfFile, int inputBitDepth) const
{
	//Starts output file stream
	std::ofstream imageFile;

	//Creates a file with the file name
	imageFile.open(nameOfFile);

	//Calculates maximum value of the number of bits can hold
	unsigned int maxColorValue = unsigned int(pow(2, inputBitDepth) - 1);

	//Format of a .ppm file:
	imageFile << "P3 " << width << " " << height << std::endl << maxColorValue << std::endl;

	for (int h = 0; h < height; h++)
	{
		for (int w = 0; w < width; w++)
		{
			 imageFile << sqrt(clamp(pixels[h][w].getX(), 0, 1)) * maxColorValue
				<< " " << sqrt(clamp(pixels[h][w].getY(), 0, 1)) * maxColorValue
				<< " " << sqrt(clamp(pixels[h][w].getZ(), 0, 1)) * maxColorValue << " ";
		}

		imageFile << std::endl;
	}

	imageFile.close();
}

void Image::outputBMP(std::string& nameOfFile) const
{
	std::ofstream imageFile;

	imageFile.open(nameOfFile, std::ios::binary);

	//Format of a .bmp file: 
	int filesize = 54 + 3 * width * height;

	unsigned char bmpfileheader[14] = { 'B','M', 0,0,0,0, 0,0, 0,0, 54,0,0,0 };
	unsigned char bmpinfoheader[40] = { 40,0,0,0, 0 ,0,0,0, 0,0,0,0, 1,0, 24,0 };
	unsigned char bmppad[3] = { 0,0,0 };

	bmpfileheader[2] = (unsigned char)(filesize);
	bmpfileheader[3] = (unsigned char)(filesize >> 8);
	bmpfileheader[4] = (unsigned char)(filesize >> 16);
	bmpfileheader[5] = (unsigned char)(filesize >> 24);

	bmpinfoheader[4] = (unsigned char)(width);
	bmpinfoheader[5] = (unsigned char)(width >> 8);
	bmpinfoheader[6] = (unsigned char)(width >> 16);
	bmpinfoheader[7] = (unsigned char)(width >> 24);
	bmpinfoheader[8] = (unsigned char)(height);
	bmpinfoheader[9] = (unsigned char)(height >> 8);
	bmpinfoheader[10] = (unsigned char)(height >> 16);
	bmpinfoheader[11] = (unsigned char)(height >> 24);

	imageFile.write(reinterpret_cast<char *>(bmpfileheader), 14);
	imageFile.write(reinterpret_cast<char*>(bmpinfoheader), 40);

	for (int h = height - 1; h >= 0; h--)
	{
		for (int w = 0; w < width; w++)
		{
			unsigned char b = sqrt(clamp(pixels[h][w].getZ(), 0, 1)) * 255;
			unsigned char g = sqrt(clamp(pixels[h][w].getY(), 0, 1)) * 255;
			unsigned char r = sqrt(clamp(pixels[h][w].getX(), 0, 1)) * 255;

			unsigned char color[3] = { b, g, r };
			
			imageFile.write(reinterpret_cast<char*>(color), 3);
		}

		imageFile.write(reinterpret_cast<char*>(bmppad), (4 - (width * 3) % 4) % 4);
	}

	imageFile.close();
}

Image::~Image()
{
	//Iterates over allocated memory of 2D array and deletes it
	for (int h = 0; h < height; h++)
	{
		delete[] pixels[h];
	}

	delete[] pixels;
}
