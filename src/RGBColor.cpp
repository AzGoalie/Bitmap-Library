#include "RGBColor.h"
#include <math.h>

RGBColor::RGBColor() : r(0.0f), g(0.0f), b(0.0f)
{}

RGBColor::RGBColor(float c) : r(c), g(c), b(c)
{}

RGBColor::RGBColor(float r, float g, float b) : r(r), g(g), b(b)
{}

RGBColor::RGBColor(const RGBColor& c) : r(c.r), g(c.g), b(c.b)
{}

RGBColor::~RGBColor()
{}

RGBColor& RGBColor::operator= (const RGBColor& rhs) {
	if (this == &rhs)
		return (*this);

	r = rhs.r; g = rhs.g; b = rhs.b;
	return (*this);
}

RGBColor RGBColor::powc(float p) const {
	return RGBColor(pow(r, p), pow(g, p), pow(b, p));
}