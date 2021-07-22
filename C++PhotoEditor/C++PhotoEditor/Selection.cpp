#pragma once
#include"Selection.h"

int Number(int i, int j, int layer_Width, int layer_Height, int x, int y)
{
	int new_y, new_x;
	new_y = y - i;
	new_x = x + j;
	return ((new_y - 1)*layer_Width - 1 + new_x);
}

Selection::Selection(std::vector<Rectangle*> Rectangles)
{
	rectangles = Rectangles;
	active = 1;
}

std::set<int> Selection::pixelSelection(int layer_Width, int layer_Height)
{
	std::set<int> temp;
	int m, n, x, y;
	for (Rectangle *r : this->rectangles)
	{
		m = r->getHeight();   n = r->getWidth();   x = r->getX();  y = r->getY();
		for (int i = 0; i < m; i++)
		{
			for (int j = 0; j < n; j++)
			{
				temp.insert(Number(i, j, layer_Width, layer_Height, x, y));
			}
		}
	}
	return temp;
}

