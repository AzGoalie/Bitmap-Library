#include "bmp.h"
#include <fstream>

#define HEADER_SIZE 14
#define INFO_SIZE 40

Bitmap::Bitmap()
{
	pixels = NULL;
}

Bitmap::~Bitmap()
{
	if (!pixels)
	{
		for (int x = 0; x < info.width; x++)
			delete[] pixels[x];
		delete[] pixels;
		pixels = NULL;
	}
}

bool Bitmap::LoadBMP(const char* filename)
{
    std::ifstream file(filename, std::ios::in | std::ios::binary);
    if (!file.is_open())
        return false;
    
    this->filename = filename;
    
    // Read the header
    file.read((char*)&header.magic, sizeof(header.magic));
    file.read((char*)&header.fileSize, sizeof(header.fileSize));
    file.read((char*)&header.res1, sizeof(header.res1));
    file.read((char*)&header.res2, sizeof(header.res2));
    file.read((char*)&header.offset, sizeof(header.offset));
    
    // Read the info header
    file.read((char*)&info.infoSize, sizeof(info.infoSize));
    file.read((char*)&info.width, sizeof(info.width));
    file.read((char*)&info.height, sizeof(info.height));
    file.read((char*)&info.planes, sizeof(info.planes));
    file.read((char*)&info.bpp, sizeof(info.bpp));
    file.read((char*)&info.comp, sizeof(info.comp));
    file.read((char*)&info.bmpSize, sizeof(info.bmpSize));
    file.read((char*)&info.xPixelsPerMeter, sizeof(info.xPixelsPerMeter));
    file.read((char*)&info.yPixelsPerMeter, sizeof(info.yPixelsPerMeter));
    file.read((char*)&info.nColors, sizeof(info.nColors));
    file.read((char*)&info.importantColors, sizeof(info.importantColors));
    
    // Create the pixel array
    pixels = new RGBColor*[info.width];
    for (int i = 0; i < info.width; i++)
        pixels[i] = new RGBColor[info.height];
    
    int pad = (-info.width*3) & 3;
    for (int y = 0; y < info.height; y++)
    {
        for (int x = 0; x < info.width; x++)
        {
            char p[3];
            file.read(p, sizeof(p));
            pixels[x][y].r = p[2];
            pixels[x][y].g = p[1];
            pixels[x][y].b = p[0];
        }
        
        char zero;
        for (int i = 0; i < pad; i++)
            file.read(&zero, sizeof(zero));
    }
    
    file.close();
    
    return true;
}

bool Bitmap::CreateBMP(const char* filename, unsigned int width, unsigned int height, unsigned short int bpp)
{
	if (bpp != 1 && bpp != 4 && bpp != 8 && bpp != 16 && bpp != 24 && bpp != 32)
		return false;

    int pad = (-width*3) & 3;
	header.magic[0] = 'B';
	header.magic[1] = 'M';
	header.fileSize = HEADER_SIZE + INFO_SIZE + (width*3+pad) * height;
	header.res1 = 0;
	header.res2 = 0;
	header.offset = HEADER_SIZE + INFO_SIZE;

	info.infoSize = INFO_SIZE;
	info.width = width;
	info.height = height;
	info.planes = 1;
	info.comp = 0;
	info.bpp = bpp;
	info.bmpSize = (width*3+pad) * height;
	info.xPixelsPerMeter = 3780;
	info.yPixelsPerMeter = 3780;
	info.nColors = 0;
	info.importantColors = 0;

	pixels = new RGBColor*[width];
	for (int i = 0; i < width; i++)
		pixels[i] = new RGBColor[height];

    this->filename = filename;

	return true;
}

unsigned int Bitmap::GetWidth()
{
	return info.width;
}

unsigned int Bitmap::GetHeight()
{
	return info.height;
}

unsigned int Bitmap::GetBPP()
{
	return info.bpp;
}

RGBColor* Bitmap::GetPixel(unsigned int x, unsigned int y)
{
	if (x <= info.width && y <= info.height)
		return &pixels[x][y];

	return NULL;
}

bool Bitmap::SetPixel(unsigned int x, unsigned int y, const RGBColor& pixel)
{
	if (x <= info.width && y <= info.height)
	{
		pixels[x][y] = pixel;
		return true;
	}

	return false;
}

bool Bitmap::Save()
{
	std::ofstream file(filename.c_str(), std::ios::out | std::ios::binary);

	if (!file.is_open())
		return false;

	// Write the header
	file.write((char*)&header.magic, sizeof(header.magic));
	file.write((char*)&header.fileSize, sizeof(header.fileSize));
	file.write((char*)&header.res1, sizeof(header.res1));
	file.write((char*)&header.res2, sizeof(header.res2));
	file.write((char*)&header.offset, sizeof(header.offset));

	// Write the info header
	file.write((char*)&info.infoSize, sizeof(info.infoSize));
	file.write((char*)&info.width, sizeof(info.width));
	file.write((char*)&info.height, sizeof(info.height));
	file.write((char*)&info.planes, sizeof(info.planes));
	file.write((char*)&info.bpp, sizeof(info.bpp));
	file.write((char*)&info.comp, sizeof(info.comp));
	file.write((char*)&info.bmpSize, sizeof(info.bmpSize));
	file.write((char*)&info.xPixelsPerMeter, sizeof(info.xPixelsPerMeter));
	file.write((char*)&info.yPixelsPerMeter, sizeof(info.yPixelsPerMeter));
	file.write((char*)&info.nColors, sizeof(info.nColors));
	file.write((char*)&info.importantColors, sizeof(info.importantColors));

    int pad = (-info.width*3) & 3;
	for (int y = 0; y < info.height; y++)
	{
		for (int x = 0; x < info.width; x++)
		{
            char p[3];
            p[0] = pixels[x][y].b;
            p[1] = pixels[x][y].g;
            p[2] = pixels[x][y].r;
            
			file.write(p, sizeof(p));
		}
        
        char zero = 0;
        for (int i = 0; i < pad; i++)
            file.write(&zero, sizeof(zero));
    }

	file.close();
	return true;
}