#pragma once

#ifndef IMAGE
#define IMAGE

#include "Operation.h"
#include <stdint.h>
#include <vector>
#include"Layer.h"
#include<map>
#include"Rectangle.h"
#include"Selection.h"
using namespace std;

class Formatter;
class Operation;

class Image
{
private:
	Formatter *myFormatter;

public:
	vector<Layer*> layers;
	map<string, Selection*> selections;
	vector<Operation*> operations;
	Layer *exportLayer;

	Image(Formatter *f);
	~Image();

	virtual void read(std::string);

	virtual void write(std::string);

	void setFormatter(Formatter *newF);

	void addOperation(Operation *newOp);

	vector<Layer*> getLayers() const { return layers; }

	void setSelections();     //postavljanje selekcija, tj stvaranje

	void setActiveLayers();   //biranje toga koji ce layer iti aktivan

	void setVisibleLayer();   //biraju se vidljivi slojevi za exportovanje

	void layerCheck();        //dopune pikselima ako se doda veci layer od prethodnih ili obrnuto

	void deleteLayer();

	void deleteSelection();

	void settingFirstLayer();

	void fillSelection();       //ubacuje boju u selekciju

	std::vector<Pixel> flattenLayers();
};

#endif