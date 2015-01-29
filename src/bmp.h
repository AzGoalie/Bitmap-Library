#ifndef BMP_H
#define BMP_H

#include "RGBColor.h"
#include <string>

struct BitmapHeader
{
	unsigned char		magic[2];	// magic number, usually BM
	unsigned int		fileSize;	// size of the file
	unsigned short int	res1;		// unused
	unsigned short int	res2;		// unused
	unsigned int		offset;		// starting position of data
};

struct BitmapInfo
{
	unsigned int		infoSize;			// size of this header
	unsigned int		width;				// width of the image
	unsigned int		height;				// height of the image
	unsigned short int	planes;				// number of color planes (1)
	unsigned short int	bpp;				// bits per pixel (1,4,8,16,24,32)
	unsigned int		comp;				// compression method
	unsigned int		bmpSize;			// size of the raw image in bytes
	unsigned int		xPixelsPerMeter;	// horizontal resolution in pixels/meter
	unsigned int		yPixelsPerMeter;	// vertical resolution in pixels/meter
	unsigned int		nColors;			// number of colors in the pallete (0)
	unsigned int		importantColors;	// number of important colors (0)
};

class Bitmap
{
private:
	BitmapHeader header;
	BitmapInfo info;
    std::string filename;

	RGBColor** pixels;

public:
	Bitmap();
	~Bitmap();

	bool LoadBMP(const char* filename);
	bool CreateBMP(const char* filename, unsigned int width, unsigned int height, unsigned short int bpp);

    std::string GetFilename() { return filename; }
    void SetFilename(const char* filename) { this->filename = filename; }
    
	unsigned int GetWidth();
	unsigned int GetHeight();
	unsigned int GetBPP();

	RGBColor* GetPixel(unsigned int x, unsigned int y);
	bool SetPixel(unsigned int x, unsigned int y, const RGBColor& p);

	bool Save();
};

#endif