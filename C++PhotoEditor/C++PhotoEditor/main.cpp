#include "Image.h"
#include "Formatter.h"
#include "Operation.h"
#include"BMPFormatter.h"
#include"BMPLayer.h"
#include<iostream>
#include<string>
#include<regex>
/*
int main() {


	Image *bmp = nullptr;
	std::string fileName;
	int t;
	while (1)
	{
		std::cout << "******Opcije*******" << std::endl;
		std::cout << "1. Ubacite sliku" << std::endl;
		std::cout << "2. Napravite selekciju" << std::endl;
		std::cout << "3. Izaberite aktivnu selekciju" << std::endl;
		std::cout << "4. Izvrsite operacije" << std::endl;
		std::cout << "5. Obojite selekciju" << std::endl;
		std::cout << "6. Izaberite vidljive slojeve" << std::endl;
		std::cout << "7. Exportujte sliku" << std::endl;
		std::cout << "0. za kraj rada " << std::endl;
		std::cin >> t;
		std::cin.ignore(1024, '\n');
		if (t == 1)
		{
			std::cout << "Ucitavanje slike " << std::endl;
			std::cout << "Ime datoteke:" << std::endl;
			std::getline(cin, fileName);
			if (bmp == nullptr)
			{
				if (fileName.find("bmp") != std::string::npos)
				{
					bmp = new Image(new BMPFormatter());
					bmp->read(fileName);
					bmp->layerCheck();
				}
				else if (fileName.find("pam") != std::string::npos)
				{
					//		bmp = new Image(new PAMFormatter());
					bmp->read(fileName);
				}
				else
					std::cout << "Wrong file format" << std::endl;
			}
			else
			{
				if (fileName.find("bmp") != std::string::npos)
				{
					bmp->setFormatter(new BMPFormatter());
					bmp->read(fileName);
					bmp->layerCheck();
				}
				else if (fileName.find("pam") != std::string::npos)
				{
					//	bmp->setFormatter(new PAMFormatter());
					bmp->read(fileName);
				}
				else
					std::cout << "Wrong file format" << std::endl;
			}
		}
		else if (t == 2)
		{
			bmp->setSelections();
		}
		else if (t == 3)
		{
			bmp->setActiveLayers();
		}
		else if (t == 4)
		{

			std::cout << "****OPERACIJE***" << std::endl;
			std::cout << "1. sabiranje" << std::endl;
			std::cout << "2. oduzimanje" << std::endl;
			std::cout << "3. inverzno oduzimanje" << std::endl;
			std::cout << "4. mnozenje" << std::endl;
			std::cout << "5. deljenje" << std::endl;
			std::cout << "6. inverzno deljenje" << std::endl;
			std::cout << "7. stepen" << std::endl;
			std::cout << "8. log" << std::endl;
			std::cout << "9. abs" << std::endl;
			std::cout << "10. min" << std::endl;
			std::cout << "11. max" << std::endl;
			std::cout << "12. greyShades" << std::endl;
			std::cout << "13. medijana" << std::endl;
			std::cout << "14. inverzija" << std::endl;
			std::cout << "15. crno-bela slika" << std::endl;
			std::cout << "16. kompozitna operacija" << std::endl;
			std::cout << "0. za kraj" << std::endl;
			int p;
			std::cin >> p;

			if (p == 1) {
				bmp->addOperation(new BasicOperation1);
				bmp->operations.back()->execute(*bmp);
			}
			else if (p == 2) {
				bmp->addOperation(new BasicOperation2);
				bmp->operations.back()->execute(*bmp);
			}
			else if (p == 3) {
				bmp->addOperation(new BasicOperation3);
				bmp->operations.back()->execute(*bmp);
			}
			else if (p == 4) {
				bmp->addOperation(new BasicOperation4);
				bmp->operations.back()->execute(*bmp);
			}
			else if (p == 5) {
				bmp->addOperation(new BasicOperation5);
				bmp->operations.back()->execute(*bmp);
			}
			else if (p == 6) {
				bmp->addOperation(new BasicOperation6);
				bmp->operations.back()->execute(*bmp);
			}
			else if (p == 7) {
				bmp->addOperation(new BasicOperation7);
				bmp->operations.back()->execute(*bmp);
			}
			else if (p == 8) {
				bmp->addOperation(new BasicOperation8);
				bmp->operations.back()->execute(*bmp);
			}
			else if (p == 9) {
				bmp->addOperation(new BasicOperation9);
				bmp->operations.back()->execute(*bmp);
			}
			else if (p == 10) {
				bmp->addOperation(new BasicOperation10);
				bmp->operations.back()->execute(*bmp);
			}
			else if (p == 11) {
				bmp->addOperation(new BasicOperation11);
				bmp->operations.back()->execute(*bmp);
			}
			else if (p == 12) {
				bmp->addOperation(new GreyShadesOperation);
				bmp->operations.back()->execute(*bmp);
			}
			else if (p == 13) {
				bmp->addOperation(new MedianaOperation);
				bmp->operations.back()->execute(*bmp);
			}
			else if (p == 14) {
				bmp->addOperation(new InverseOperation);
				bmp->operations.back()->execute(*bmp);
			}
			else if (p == 15) {
				bmp->addOperation(new BlackWhiteOperation);
				bmp->operations.back()->execute(*bmp);
			}
			else if (p == 16) {
				CompositeOperation *pom = new CompositeOperation;
				int t1;
				while (1)
				{
					std::cin >> t1;
					if (t1 == 1) {
						pom->addOperation(new BasicOperation1);
					}
					else if (t1 == 2) {
						pom->addOperation(new BasicOperation2);
					}
					else if (t1 == 3) {
						pom->addOperation(new BasicOperation3);
					}
					else if (t1 == 4) {
						pom->addOperation(new BasicOperation4);
					}
					else if (t1 == 5) {
						pom->addOperation(new BasicOperation5);
					}
					else if (t1 == 6) {
						pom->addOperation(new BasicOperation6);
					}
					else if (t1 == 7) {
						pom->addOperation(new BasicOperation7);
					}
					else if (t1 == 8) {
						pom->addOperation(new BasicOperation8);
					}
					else if (t1 == 9) {
						pom->addOperation(new BasicOperation9);
					}
					else if (t1 == 10) {
						pom->addOperation(new BasicOperation10);
					}
					else if (t1 == 11) {
						pom->addOperation(new BasicOperation11);
					}
					else if (t1 == 0)
						break;
				}
				bmp->addOperation(pom);
				bmp->operations.back()->execute(*bmp);
			}
		}
		else if (t == 5)
		{
			bmp->fillSelection();
		}
		else if (t == 6)
		{
			bmp->setVisibleLayer();
		}
		else if (t == 7)
		{
			std::cout << "Ime datoteke:" << std::endl;
			std::getline(cin, fileName);
			if (fileName.find("bmp") != std::string::npos)
			{
				bmp->setFormatter(new BMPFormatter());
				bmp->write(fileName);
			}
			else if (fileName.find("pam") != std::string::npos)
			{
				//	bmp->setFormatter(new PAMFormatter());
				bmp->write(fileName);
			}
		}
		else if(t == 0)
		exit(1);
	}

//********STARO************
	/*
	while (1)
	{
		std::cout << "Ucitavanje slike " << std::endl;
		std::cout << "Ime datoteke:" << std::endl;
		std::getline(cin, fileName);
		if (bmp == nullptr)
		{
			if (fileName.find("bmp") != std::string::npos)
			{
				bmp = new Image(new BMPFormatter());
				bmp->read(fileName);
				bmp->read("Ashura.bmp");
				bmp->layerCheck();
			//	unsigned char a = bmp->layers[0]->getHeight();   		  //provera
			//	unsigned char b = bmp->layers[0]->pixels[0].A;			  //provera
			//	std::cout << (int)a << (int)b << std::endl;				  //provera
			//	bmp->setSelections();
				//bmp->fillSelection();
			//	bmp->addOperation(new GreyShadesOperation);
			//	bmp->operations[0]->execute(*bmp);
				bmp->write("smp2.bmp");    //Sample2_proba.bmp,tester1.bmp
				std::cout << 1;
			}
			else if (fileName.find("pam") != std::string::npos)
			{
		//		bmp = new Image(new PAMFormatter());
				bmp->read(fileName);
			}
			else
				std::cout << "Wrong file format" << std::endl;
		}
		else
		{
			if (fileName.find("bmp") != std::string::npos)
			{
				bmp->setFormatter(new BMPFormatter());
				bmp->read(fileName);
			}
			else if (fileName.find("pam") != std::string::npos)
			{
			//	bmp->setFormatter(new PAMFormatter());
				bmp->read(fileName);
			}
			else
				std::cout << "Wrong file format" << std::endl;
		}

	}

	std::cout << "Birajte selekcije" << std::endl;
	//poziv funkcije biranja selekcija, parametar je objekat Image


	bmp->addOperation(new BasicOperation1());


	//.....
	//bmp->setFormatter(new PAMFormatter());
	//bmp->write("primer_exp.pam");

	return 0;
	*/
//}