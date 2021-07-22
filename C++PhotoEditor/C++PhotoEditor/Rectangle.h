#pragma once
#include"Pixel.h"
#include<vector>

class Rectangle
{
private:
	int x, y, width, height;

public:
	Rectangle(int x,int y,int width,int height);
	int getX() const;
	int getY() const;
	int getWidth() const;
	int getHeight() const;
};

