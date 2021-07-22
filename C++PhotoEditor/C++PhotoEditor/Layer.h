#pragma once
#include "Pixel.h"
#include<vector>

struct BMPFileHeader;
struct BMPInfoHeader;
struct BMPColorHeader;

class Layer
{
public:
	std::vector<Pixel> pixels;
	float transparency;
	bool l_active = false;
	bool visible = true;
	int Height, Width;

public:
	Layer(int H, int W);
	Layer();
	virtual int getHeight() const;
	virtual int getWidth() const;
	virtual BMPFileHeader getFileHeader() const = 0;
	virtual BMPInfoHeader getInfoHeader() const = 0;
	virtual BMPColorHeader getColorHeader() const = 0;
	virtual void setHeaders(int a, int b, int c, int d) = 0;
	virtual bool getType() = 0;
	virtual void setHeight(int H);
	virtual void setWidth(int W);
	void ajustSize(int H, int W);
};