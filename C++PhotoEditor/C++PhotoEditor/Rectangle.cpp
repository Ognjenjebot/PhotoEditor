#include "Rectangle.h"

Rectangle::Rectangle(int x, int y, int width, int height)
{
	this->x = x;   this->y = y;   this->width = width;   this->height = height;
}

int Rectangle::getX() const
{
	return this->x;
}

int Rectangle::getY() const
{
	return this->y;
}

int Rectangle::getWidth() const
{
	return this->width;
}

int Rectangle::getHeight() const
{
	return this->height;
}
