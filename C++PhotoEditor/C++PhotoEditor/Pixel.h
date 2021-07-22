#pragma once

class Pixel
{
public:
	unsigned char B;
	unsigned char G;
	unsigned char R;
	unsigned char A;

public:
	Pixel(unsigned char Blue, unsigned char Green, unsigned char Red, unsigned char Alpha);
	Pixel() {}
};