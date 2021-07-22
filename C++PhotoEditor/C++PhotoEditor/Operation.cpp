#pragma once
#include"Operation.h"
#include"Pixel.h"
#include"Image.h"
#include"Layer.h"
#include"Selection.h"



bool actives(std::pair<string, Selection*> p)
{
	return p.second->active;
}

void BasicOperation1::execute(Image &i)   //sabiranje
{
	std::cout << "Konstanta sa kojom se sabira ->" << std::endl;
	int c;
	cin >> c;
	std::map<std::string, Selection*>::iterator it;
	it = std::find_if(i.selections.begin(), i.selections.end(), actives);   //sadrzi aktivnu selekciju
	set<int> pixelIndexes = (*(it)).second->pixelSelection(i.layers[0]->getWidth(), i.layers[0]->getHeight());     //(*(it))->pixelSelection(i.layers[0]->getWidth(), i.layers[0]->getHeight());  
	//vracanje vektora indeksa piksela 

	for (Layer *l : i.layers) 
	{
		if (l->l_active)
		{
			for (int j : pixelIndexes)
			{
				l->pixels[j].A += c;   l->pixels[j].B += c;  l->pixels[j].G += c;  l->pixels[j].R += c;
			}
		}
	}
}

void BasicOperation2::execute(Image & i)  //oduzimanje
{	
	std::cout << "Konstanta sa kojom se oduzima ->" << std::endl;
	int c;
	cin >> c;
	std::map<std::string, Selection*>::iterator it;
	it = std::find_if(i.selections.begin(), i.selections.end(), actives);   //sadrzi aktivnu selekciju
	set<int> pixelIndexes = (*(it)).second->pixelSelection(i.layers[0]->getWidth(), i.layers[0]->getHeight());     //(*(it))->pixelSelection(i.layers[0]->getWidth(), i.layers[0]->getHeight());  
	//vracanje vektora indeksa piksela 

	for (Layer *l : i.layers)
	{
		if (l->l_active)
		{
			for (int j : pixelIndexes)
			{
				l->pixels[j].A -= c;   l->pixels[j].B -= c;  l->pixels[j].G -= c;  l->pixels[j].R -= c;
			}
		}
	}
}

void BasicOperation3::execute(Image & i)  //inverzno oduzimanje
{
	std::cout << "Konstanta ->" << std::endl;
	int c;
	cin >> c;

	std::map<std::string, Selection*>::iterator it;
	it = std::find_if(i.selections.begin(), i.selections.end(), actives);   //sadrzi aktivnu selekciju
	set<int> pixelIndexes = (*(it)).second->pixelSelection(i.layers[0]->getWidth(), i.layers[0]->getHeight());     //(*(it))->pixelSelection(i.layers[0]->getWidth(), i.layers[0]->getHeight());  
	//vracanje vektora indeksa piksela 

	for (Layer *l : i.layers)
	{
		if (l->l_active)
		{
			for (int j : pixelIndexes)
			{
				l->pixels[j].A = c - l->pixels[j].A;   l->pixels[j].B = c - l->pixels[j].B;  l->pixels[j].G = c - l->pixels[j].G;  l->pixels[j].R = c - l->pixels[j].R;
			}
		}
	}
}

void BasicOperation4::execute(Image & i)  //mnozenje
{
	std::cout << "Konstanta sa kojom se mnozi ->" << std::endl;
	int c;
	cin >> c;
	std::map<std::string, Selection*>::iterator it;
	it = std::find_if(i.selections.begin(), i.selections.end(), actives);   //sadrzi aktivnu selekciju
	set<int> pixelIndexes = (*(it)).second->pixelSelection(i.layers[0]->getWidth(), i.layers[0]->getHeight());     //(*(it))->pixelSelection(i.layers[0]->getWidth(), i.layers[0]->getHeight());  
	//vracanje vektora indeksa piksela 

	for (Layer *l : i.layers)
	{
		if (l->l_active)
		{
			for (int j : pixelIndexes)
			{
				l->pixels[j].A *= c;   l->pixels[j].B *= c;  l->pixels[j].G *= c;  l->pixels[j].R *= c;
			}
		}
	}
}

void BasicOperation5::execute(Image & i)  //deljenje
{
	std::cout << "Konstanta sa kojom se deli ->" << std::endl;
	int c;
	cin >> c;
	std::map<std::string, Selection*>::iterator it;
	it = std::find_if(i.selections.begin(), i.selections.end(), actives);   //sadrzi aktivnu selekciju
	set<int> pixelIndexes = (*(it)).second->pixelSelection(i.layers[0]->getWidth(), i.layers[0]->getHeight());     //(*(it))->pixelSelection(i.layers[0]->getWidth(), i.layers[0]->getHeight());  
	//vracanje vektora indeksa piksela 

	for (Layer *l : i.layers)
	{
		if (l->l_active)
		{
			for (int j : pixelIndexes)
			{
				l->pixels[j].A /= c;   l->pixels[j].B /= c;  l->pixels[j].G /= c;  l->pixels[j].R /= c;
			}
		}
	}
}

void BasicOperation6::execute(Image & i)  //inverzno deljenje
{
	std::cout << "Konstanta sa kojom se deli ->" << std::endl;
	int c;
	cin >> c;
	std::map<std::string, Selection*>::iterator it;
	it = std::find_if(i.selections.begin(), i.selections.end(), actives);   //sadrzi aktivnu selekciju
	set<int> pixelIndexes = (*(it)).second->pixelSelection(i.layers[0]->getWidth(), i.layers[0]->getHeight());     //(*(it))->pixelSelection(i.layers[0]->getWidth(), i.layers[0]->getHeight());  
	//vracanje vektora indeksa piksela 

	for (Layer *l : i.layers)
	{
		if (l->l_active)
		{
			for (int j : pixelIndexes)
			{
				l->pixels[j].A = c / l->pixels[j].A;   l->pixels[j].B = c / l->pixels[j].B;  l->pixels[j].G = c / l->pixels[j].G;  l->pixels[j].R = c / l->pixels[j].R;
			}
		}
	}
}

void BasicOperation7::execute(Image & i)  //stepen
{
	std::cout << "Konstanta stepena ->" << std::endl;
	int c;
	cin >> c;
	std::map<std::string, Selection*>::iterator it;
	it = std::find_if(i.selections.begin(), i.selections.end(), actives);   //sadrzi aktivnu selekciju
	set<int> pixelIndexes = (*(it)).second->pixelSelection(i.layers[0]->getWidth(), i.layers[0]->getHeight());     //(*(it))->pixelSelection(i.layers[0]->getWidth(), i.layers[0]->getHeight());  
	//vracanje vektora indeksa piksela 

	for (Layer *l : i.layers)
	{
		if (l->l_active)
		{
			for (int j : pixelIndexes)
			{
				l->pixels[j].A = pow(l->pixels[j].A, c);   l->pixels[j].B = pow(l->pixels[j].B, c);  l->pixels[j].G = pow(l->pixels[j].G, c);  l->pixels[j].R = pow(l->pixels[j].R, c);
			}
		}
	}
}

void BasicOperation8::execute(Image & i)  //log
{
	std::cout << "Prirodni logaritam ->" << std::endl;

	std::map<std::string, Selection*>::iterator it;
	it = std::find_if(i.selections.begin(), i.selections.end(), actives);   //sadrzi aktivnu selekciju
	set<int> pixelIndexes = (*(it)).second->pixelSelection(i.layers[0]->getWidth(), i.layers[0]->getHeight());     //(*(it))->pixelSelection(i.layers[0]->getWidth(), i.layers[0]->getHeight());  
	//vracanje vektora indeksa piksela 

	for (Layer *l : i.layers)
	{
		if (l->l_active)
		{
			for (int j : pixelIndexes)
			{
				l->pixels[j].A = log(l->pixels[j].A);   l->pixels[j].B = log(l->pixels[j].B);  l->pixels[j].G = log(l->pixels[j].G);  l->pixels[j].R = log(l->pixels[j].R);
			}
		}
	}
}

void BasicOperation9::execute(Image & i)  //abs
{
	std::cout << "Apsolutna vrednost" << std::endl;
	std::map<std::string, Selection*>::iterator it;
	it = std::find_if(i.selections.begin(), i.selections.end(), actives);   //sadrzi aktivnu selekciju
	set<int> pixelIndexes = (*(it)).second->pixelSelection(i.layers[0]->getWidth(), i.layers[0]->getHeight());     //(*(it))->pixelSelection(i.layers[0]->getWidth(), i.layers[0]->getHeight());  
	//vracanje vektora indeksa piksela 

	for (Layer *l : i.layers)
	{
		if (l->l_active)
		{
			for (int j : pixelIndexes)
			{
				l->pixels[j].A = abs(l->pixels[j].A);   l->pixels[j].B = abs(l->pixels[j].B);  l->pixels[j].G = abs(l->pixels[j].G);  l->pixels[j].R = abs(l->pixels[j].R);
			}
		}
	}
}

void BasicOperation10::execute(Image & i)  //min
{
	std::cout << "Konstanta ->" << std::endl;
	int c;
	cin >> c;
	std::map<std::string, Selection*>::iterator it;
	it = std::find_if(i.selections.begin(), i.selections.end(), actives);   //sadrzi aktivnu selekciju
	set<int> pixelIndexes = (*(it)).second->pixelSelection(i.layers[0]->getWidth(), i.layers[0]->getHeight());     //(*(it))->pixelSelection(i.layers[0]->getWidth(), i.layers[0]->getHeight());  
	//vracanje vektora indeksa piksela 

	for (Layer *l : i.layers)
	{
		if (l->l_active)
		{
			for (int j : pixelIndexes)
			{
				if (l->pixels[j].A > c)
					l->pixels[j].A = c;
				if (l->pixels[j].B > c)
					l->pixels[j].B = c;
				if (l->pixels[j].G > c)
					l->pixels[j].G = c;
				if (l->pixels[j].R > c)
					l->pixels[j].R = c;
			}
		}
	}
}

void BasicOperation11::execute(Image & i)  //max
{
	std::cout << "Konstanta ->" << std::endl;
	int c;
	cin >> c;
	std::map<std::string, Selection*>::iterator it;
	it = std::find_if(i.selections.begin(), i.selections.end(), actives);   //sadrzi aktivnu selekciju
	set<int> pixelIndexes = (*(it)).second->pixelSelection(i.layers[0]->getWidth(), i.layers[0]->getHeight());     //(*(it))->pixelSelection(i.layers[0]->getWidth(), i.layers[0]->getHeight());  
	//vracanje vektora indeksa piksela 

	for (Layer *l : i.layers)
	{
		if (l->l_active)
		{
			for (int j : pixelIndexes)
			{
				if (l->pixels[j].A < c)
					l->pixels[j].A = c;
				if (l->pixels[j].B < c)
					l->pixels[j].B = c;
				if (l->pixels[j].G < c)
					l->pixels[j].G = c;
				if (l->pixels[j].R < c)
					l->pixels[j].R = c;
			}
		}
	}
}

void GreyShadesOperation::execute(Image & i)  //abs
{
	std::map<std::string, Selection*>::iterator it;
	it = std::find_if(i.selections.begin(), i.selections.end(), actives);   //sadrzi aktivnu selekciju
	set<int> pixelIndexes = (*(it)).second->pixelSelection(i.layers[0]->getWidth(), i.layers[0]->getHeight());     //(*(it))->pixelSelection(i.layers[0]->getWidth(), i.layers[0]->getHeight());  
	//vracanje vektora indeksa piksela 

	for (Layer *l : i.layers)
	{
		if (l->l_active)
		{
			for (int j : pixelIndexes)
			{
				int a = ((l->pixels[j].B + l->pixels[j].G + l->pixels[j].R) / 3);
				l->pixels[j].B = a;
				l->pixels[j].G = a;
				l->pixels[j].R = a;
			}
		}
	}
}

void MedianaOperation::execute(Image & i)  
{
	std::map<std::string, Selection*>::iterator it;
	it = std::find_if(i.selections.begin(), i.selections.end(), actives);   //sadrzi aktivnu selekciju
	set<int> pixelIndexes = (*(it)).second->pixelSelection(i.layers[0]->getWidth(), i.layers[0]->getHeight());     //(*(it))->pixelSelection(i.layers[0]->getWidth(), i.layers[0]->getHeight());  
	//vracanje vektora indeksa piksela 


	for (Layer *l : i.layers)
	{
		if (l->l_active)
		{
			std::vector<Pixel> temp;
			temp = l->pixels;
			for (int j : pixelIndexes)
			{
				int R, G, B;
				R = (l->pixels[j + 1].R + l->pixels[j - 1].R + l->pixels[j - l->getWidth()].R + l->pixels[j + l->getWidth()].R) / 4;
				G = (l->pixels[j + 1].G + l->pixels[j - 1].G + l->pixels[j - l->getWidth()].G + l->pixels[j + l->getWidth()].G) / 4;
				B = (l->pixels[j + 1].B + l->pixels[j - 1].B + l->pixels[j - l->getWidth()].B + l->pixels[j + l->getWidth()].B) / 4;
				temp[j].B = B;    temp[j].G = G;    temp[j].R = R;
			}
			l->pixels = temp;
			temp.clear();
		}
	}
}

void InverseOperation::execute(Image & i)  //abs
{
	std::map<std::string, Selection*>::iterator it;
	it = std::find_if(i.selections.begin(), i.selections.end(), actives);   //sadrzi aktivnu selekciju
	set<int> pixelIndexes = (*(it)).second->pixelSelection(i.layers[0]->getWidth(), i.layers[0]->getHeight());     //(*(it))->pixelSelection(i.layers[0]->getWidth(), i.layers[0]->getHeight());  
	//vracanje vektora indeksa piksela 

	for (Layer *l : i.layers)
	{
		if (l->l_active)
		{
			for (int j : pixelIndexes)
			{
				l->pixels[j].A = 255 - l->pixels[j].A;   l->pixels[j].B = 255 - l->pixels[j].B;  l->pixels[j].G = 255 - l->pixels[j].G;  l->pixels[j].R = 255 - l->pixels[j].R;
			}
		}
	}
}

void BlackWhiteOperation::execute(Image & i)  //abs
{
	std::map<std::string, Selection*>::iterator it;
	it = std::find_if(i.selections.begin(), i.selections.end(), actives);   //sadrzi aktivnu selekciju
	set<int> pixelIndexes = (*(it)).second->pixelSelection(i.layers[0]->getWidth(), i.layers[0]->getHeight());     //(*(it))->pixelSelection(i.layers[0]->getWidth(), i.layers[0]->getHeight());  
	//vracanje vektora indeksa piksela 

	for (Layer *l : i.layers)
	{
		if (l->l_active)
		{
			for (int j : pixelIndexes)
			{
				if (((l->pixels[j].B + l->pixels[j].G + l->pixels[j].R) / 3) < 127)
				{
					l->pixels[j].B = 0;
					l->pixels[j].G = 0;
					l->pixels[j].R = 0;
				}
				else
				{
					l->pixels[j].B = 255;
					l->pixels[j].G = 255;
					l->pixels[j].R = 255;
				}
			}
		}
	}
}

void CompositeOperation::addOperation(Operation * op)
{
	if (op != nullptr) {
		operations.push_back(op);
	}	
}

void CompositeOperation::execute(Image & i)
{	
	for (std::vector<Operation *>::iterator it = operations.begin(); it != operations.end(); ++it) {
		//*it vraca Operation *
		(*it)->execute(i);
	}	
}
