#include"Layer.h"

struct BMPFileHeader;
struct BMPInfoHeader;
struct BMPColorHeader;

Layer::Layer(int H, int W)       //sa stvaranje praznog layera
{
	Height = H;
	Width = W;
	pixels.resize(Height * Width);
	pixels.clear();
	for (int i = 0; i < Height * Width; i++)
	{
		Pixel pom(0, 0, 0, 255);
		pixels.push_back(pom);
	}
}

Layer::Layer()
{
	transparency = 100;
	l_active = true;
}

int Layer::getHeight() const
{
	return Height;
}

int Layer::getWidth() const
{
	return Width;
}

void Layer::setHeight(int H)
{
	Height = H;
}

void Layer::setWidth(int W)
{
	Width = W;
}

void Layer::ajustSize(int H, int W)
{
	std::vector<Pixel> pom; 
	pom.clear();
	for (int i = 0; i < H; i++)
	{
		for (int j = 0; j < W; j++)
		{
			if ((i >= this->getHeight()) || (j >= this->getWidth()))
			{
				pom.push_back(Pixel(0, 0, 0, 0));
			}
			else
			{
				pom.push_back(this->pixels[i * this->getWidth() + j]);
			}
		}
	}
	this->pixels = pom;
	pom.clear();
	this->setHeight(H);
	this->setWidth(W);
}

