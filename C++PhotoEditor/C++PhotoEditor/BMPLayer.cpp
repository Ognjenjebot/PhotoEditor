
#include"BMPLayer.h"


BMPLayer::BMPLayer() {}
int BMPLayer::getHeight() const
{	
	return this->bmp_info_header.height;
}
int BMPLayer::getWidth() const
{
	return this->bmp_info_header.width;
}
BMPFileHeader BMPLayer::getFileHeader() const
{
	return this->file_header;
}
BMPInfoHeader BMPLayer::getInfoHeader() const
{
	return this->bmp_info_header;
}
BMPColorHeader BMPLayer::getColorHeader() const
{
	return this->bmp_color_header;
}
bool BMPLayer::getType()
{
	return true;
}
void BMPLayer::setHeight(int H)
{
	this->bmp_info_header.height = H;
}
void BMPLayer::setWidth(int W)
{
	this->bmp_info_header.width = W;
}

void BMPLayer::setHeaders(int a, int b, int c, int d)  //sirina, visina, velicina celog fajla, broj bajtova piksela
{
	this->bmp_info_header.height = a;
	this->bmp_info_header.width = b;
	this->bmp_info_header.size_image = c;
	this->file_header.file_size = d;
}
