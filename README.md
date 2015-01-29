Bitmap Library
===============

Very simple bitmap library.
Can load and create RGB bitmaps.


Example usage
```
Bitmap newBitmap;
Bitmap oldBitmap;

newBitmap.CreateBMP(filename, width, height, bpp);
oldBitmap.LoadBMP(filename);

for (int x = 0; x < width; x++) {
    for (int y = 0; y < height; y++) {
        RGBColor p(255,0,255);
        newBitmap.SetPixel(x, y, p);
    }
}

newBitmap.Save();
oldBitmap.Save();
```