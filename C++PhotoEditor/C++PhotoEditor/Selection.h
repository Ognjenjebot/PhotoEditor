#pragma once
#include"Rectangle.h"
#include<iostream>
#include<vector>
#include"Rectangle.h"
#include<set>

class Selection
{
private:
		
	std::vector<Rectangle*> rectangles;

public:
	bool active;
	Selection(std::vector<Rectangle*>);
	std::set<int> pixelSelection(int width, int height);
};