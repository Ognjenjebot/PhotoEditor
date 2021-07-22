#include<iostream>
#include<string>
#include<sstream>
#include<algorithm>
#include<iterator>
#include "Image.h"
#include "Formatter.h"
#include"Rectangle.h"
#include"Layer.h"

Image::Image(Formatter *f) { myFormatter = f; }

Image::~Image() { delete myFormatter; }

void Image::read(std::string fname) {
	myFormatter->read(fname, *this);
}

void Image::write(std::string fname) {
	myFormatter->write(fname, *this);
}

void Image::setFormatter(Formatter *newF) {
	if (newF != nullptr) { delete myFormatter;  myFormatter = newF; }
}

void Image::addOperation(Operation *newOp) {
	if (newOp != nullptr) {
		operations.push_back(newOp);
	}
}

void Image::setSelections()
{
	std::cout << "Setovanje selekcija:\n"
		<< "Za stvaranje selekcije,napisite njeno ime, koliko delova selekcije cete navesti,i za svaku koordinate,sirinu i visinu (za kraj navodjenja selekcija navedite prazno ime)" << std::endl;

	while (1)
	{
		int n;
		std::string name;
		std::getline(cin, name);
		if (name != "")
		{
			cin >> n;
			vector<Rectangle*> pom;
			std::cout << "koordinate(x, y), sirina, visina" << std::endl;
			for (int i = 0; i < n; i++)
			{
				int x, y, h, w;
				cin >> x >> y >> h >> w;
				if (x < 0 || x > this->layers[0]->Width || y < 0 || y > this->layers[0]->Height)
				{
					std::cout << "Koordinate van opsega, unesite ponovo podatke" << std::endl;
				}
				else if ((this->layers[0]->Width - x - w) < 0 || (y - h) < 0)
				{
					std::cout << "Rectangle izlazi van slike, unesite ponovo podatke" << std::endl;			
				}
				else
				{
					Rectangle *temp = new Rectangle(x, y, h, w);
					pom.push_back(temp);
				}
			}
			Selection *selec = new Selection(pom);
			this->selections[name] = selec;
		}
		else
			break;
	}
}

void Image::setActiveLayers()
{
	std::cout << "Izaberite koji slojevi ce biti aktivni (po default-u nisu aktivni)" << std::endl;
	std::string aktivni;
	getline(cin, aktivni);
	stringstream st(aktivni);
	std::vector<int> values;
	int n;
	while (st >> n) {
		values.push_back(n);
	}
	std::vector<Layer*> &pom = this->layers;                    // *** PROVERI DA LI OVO RADI***
	for_each(values.begin(), values.end(), [pom](int i) {
		pom[i]->l_active = true;                              // this->layers[i].l_active = true;
	});
}

void Image::setVisibleLayer()
{
	std::cout << "Izaberite koji slojevi nece biti vidljivi (po default-u se vide)" << std::endl;
	std::string aktivni;
	getline(cin, aktivni);
	stringstream st(aktivni);
	std::vector<int> values;
	int n;
	while (st >> n) {
		values.push_back(n);
	}
	std::vector<Layer*> &pom = this->layers;                    // *** PROVERI DA LI OVO RADI***
	for_each(values.begin(), values.end(), [pom](int i) {
		pom[i]->visible = false;                            // this->layers[i].l_active = true;
	});
}

void Image::layerCheck()      //dopune praznim piskelima ako se dodaje veci layer on prethodnih ili manji, ogranicenje je da obe velicine moraju biti vece ili manje
{
	if (!this->layers.empty())
	{
		//layer[0] bi uvek trebao da bude updejtovan
		if (this->layers.back()->getHeight() < this->layers[0]->getHeight() && this->layers.back()->getWidth() < this->layers[0]->getWidth())
		{
			this->layers.back()->ajustSize(this->layers[0]->getHeight(), this->layers[0]->getWidth());
			int m;
			m = 138 + this->layers[0]->Height * this->layers[0]->Width * 4;
			this->layers.back()->setHeaders(this->layers[0]->Height, this->layers[0]->Width, this->layers[0]->getHeight() * this->layers[0]->getWidth() * 4, m);
		}
		else if (this->layers.back()->getHeight() > this->layers[0]->getHeight() && this->layers.back()->getWidth() > this->layers[0]->getWidth())
		{
			vector<Layer*>::iterator ptr;
			for (ptr = this->layers.begin(); ptr < this->layers.end() - 1; ptr++)
			{
				(*ptr)->ajustSize(this->layers.back()->getHeight(), this->layers.back()->getWidth());
				int m;
				m = 138 + this->layers.back()->Height * this->layers.back()->Width * 4;
				this->layers.back()->setHeaders(this->layers.back()->Height, this->layers.back()->Width, this->layers.back()->getHeight() * this->layers.back()->getWidth() * 4, m);
			}
		}
	}
}

void Image::deleteLayer()            //brisanje layera
{
	std::cout << "Izaberite koje slojeve zelite da obrisete (0 za kraj)" << std::endl;
	std::vector<Layer*>::iterator it;
	while (1)
	{
		int i;
		cin >> i;
		if (i != 0)
		{
			int j = 0;
			for (it = this->layers.begin(); j < i - 1; j++, it++);          
			delete this->layers[i - 1];
			this->layers.erase(it);
		}
		else
			break;
	}
}

void Image::deleteSelection()      //brisanje selekcije
{
	std::cout << "Izaberite koje selekcije zelite da obrisete po imenu(prazan str za kraj)" << std::endl;
	std::map<std::string, Selection*>::iterator it;
	while (1)
	{
		std::string name;
		getline(cin, name);
		if (name != "")
		{
			delete this->selections.at(name);
			this->selections.erase(name);
		}
		else
			break;
	}
}

void Image::settingFirstLayer()             //popravi na kraju ako mora
{
	std::cout << "Velicina slike?(H, pa W)" << std::endl;
	int H, W;
	cin >> H >> W;
	//Layer *temp = new Layer(H, W);
    //this->layers.push_back(temp);
}

void Image::fillSelection()         //popunice selekciju bojom koja se izabere
{
	while (1)
	{
		std::cout << "Izaberite koju selekciju  zelite da popunite (po imenu, prazan string za kraj)" << std::endl;
		std::string name;
		getline(cin, name);
		if (name != "")
		{
			set<int> indexes = this->selections.at(name)->pixelSelection(this->layers[0]->getWidth(), this->layers[0]->getHeight());
			std::cout << "Izaberite boju (R za crvenu, G za zelenu, B za plavu)" << std::endl;
			std::string boja;
			getline(cin, boja);
			if (boja == "R")
			{
				for (Layer* l : this->layers)
				{
					for (int j : indexes)
					{
						l->pixels[j].R = 255;   l->pixels[j].G = 0;   l->pixels[j].B = 0;
					}
				}
			}
			else if (boja == "B")
			{
				for (Layer* l : this->layers)
				{
					for (int j : indexes)
					{
						l->pixels[j].B = 255;   l->pixels[j].G = 0;   l->pixels[j].R = 0;
					}
				}
			}
			else if (boja == "G")
			{
				for (Layer* l : this->layers)
				{
					for (int j : indexes)
					{
						l->pixels[j].R = 0;   l->pixels[j].G = 255;   l->pixels[j].B = 0;
					}
				}
			}
			else
				std::cout << "pogresno ste uneli boju" << std::endl;
		}
		else
			break;
	}


}

std::vector<Pixel> Image::flattenLayers()       //sve layere pretvara u jedan, tj samo piksele, ostali podaci ce biti isti kao kod layer[0]
{
	float tmpA, tmp;
	float sumA, sumB, sumG, sumR;

	std::vector<Pixel> exportPixels;
	for (int i = 0; i < this->layers[0]->getHeight() * this->layers[0]->getWidth(); i++)
	{
		std::vector<Layer*>::iterator it;
		tmpA = (1 - this->layers[0]->pixels[i].A / 255.0) * (this->layers[1]->pixels[i].A / 255.0);
		sumA = (this->layers[0]->pixels[i].A / 255.0) + tmpA;
		if (sumA != 0)
		{
			for (it = this->layers.begin() + 2; it < this->layers.end(); it++)
			{
				tmpA = tmpA * ((*it)->pixels[i].A / 255.0);
				sumA += tmpA;
			}
			tmp = (1 - (this->layers[0]->pixels[i].A / 255.0)) * (this->layers[1]->pixels[i].A / 255.0) / sumA;
			sumR = this->layers[0]->pixels[i].R * (this->layers[0]->pixels[i].A / 255.0) / sumA + this->layers[1]->pixels[i].R * tmp;
			sumG = this->layers[0]->pixels[i].G * (this->layers[0]->pixels[i].A / 255.0) / sumA + this->layers[1]->pixels[i].G * tmp;
			sumB = this->layers[0]->pixels[i].B * (this->layers[0]->pixels[i].A / 255.0) / sumA + this->layers[1]->pixels[i].B * tmp;
			for (it = this->layers.begin() + 2; it < this->layers.end(); it++)
			{
				tmp *= ((*it)->pixels[i].A / 255.0);
				sumR = sumR + tmp * (*it)->pixels[i].R;
				sumG = sumG + tmp * (*it)->pixels[i].G;
				sumB = sumB + tmp * (*it)->pixels[i].B;
			}
			//napravi pixel sa vrednostima sumA, sumB, sumG, sumR
			exportPixels.push_back(Pixel((int)sumB, (int)sumG, (int)sumR, (int)(sumA * 255.0)));
		}
		else
			exportPixels.push_back(Pixel(255, 255, 255, 0));
	}
	return exportPixels;
}



