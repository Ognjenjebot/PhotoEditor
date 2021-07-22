#pragma once

#ifndef FORMATTER
#define FORMATTER

#include "Image.h"
#include <exception>
using namespace std;

class Image;
class BMPImage;
class PAMImage;
struct BMPColorHeader;

class Formatter {
public:
	virtual void read(std::string fname, Image &image) = 0;

	virtual void write(std::string fname, Image &image) = 0;
};

#endif
