#include"Layer.h"
#include"Formatter.h"
#include"Image.h"
#include"BMPFormatter.h"
#include"BMPLayer.h"
#include<fstream>
#include<iostream>



void BMPFormatter::read(std::string name, Image &image) {
	
	BMPLayer *test = new BMPLayer();
	std::cout << "Izaberite prozirnost sloja (0 - skroz proziran, 100 - neproziran)" << std::endl;
	int t;
	cin >> t;
	std::cin.ignore(1024, '\n');              //jer kasnije pravi problem kod getline,http://www.cplusplus.com/forum/general/69685/#msg372532
	test->transparency = t / 100.0;
	image.layers.push_back(test);

	std::ifstream inp("C:\\Users\\ognje\\Desktop\\" + name, std::ios_base::binary);
	if (inp) {
		inp.read((char*)&test->file_header, 14);
		if (test->file_header.file_type != 0x4D42) {
			throw std::runtime_error("Error! Unrecognized file format.");
		}
		inp.read((char*)&test->bmp_info_header, sizeof(BMPInfoHeader));

		// The BMPColorHeader is used only for transparent images
		if (test->bmp_info_header.bit_count == 32) {
			// Check if the file has bit mask color information
			//Ako je velicina ovog prvog dela info hedera veca od samog hedera(BMPInfoHeader), onda to znaci da ima i bitova maske koji trebaju da se ucitaju
			test->bmp_color_header.unused.resize(((int)test->file_header.offset_data - 74) / 4);                    //  !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
			//da bi ubacio sve ove bajtove od unused kako treba
			if (test->bmp_info_header.size >= (sizeof(BMPInfoHeader) + sizeof(BMPColorHeader))) {
				inp.read((char*)&test->bmp_color_header.red_mask, sizeof(test->bmp_color_header.red_mask));
				inp.read((char*)&test->bmp_color_header.green_mask, sizeof(test->bmp_color_header.green_mask));
				inp.read((char*)&test->bmp_color_header.blue_mask, sizeof(test->bmp_color_header.blue_mask));
				inp.read((char*)&test->bmp_color_header.alpha_mask, sizeof(test->bmp_color_header.alpha_mask));
				inp.read((char*)&test->bmp_color_header.color_space_type, sizeof(test->bmp_color_header.color_space_type));
				for (int i = 0; i < test->bmp_color_header.unused.size(); i++)
					inp.read((char*)&test->bmp_color_header.unused[i], sizeof(test->bmp_color_header.unused[i]));
				// Check if the pixel data is stored as BGRA and if the color space type is sRGB
				check_color_header(test->bmp_color_header);
			}
			else {
			//	std::cerr << "Warning! The file \"" << name << "\" does not seem to contain bit mask information\n";
				throw std::runtime_error("Error! Unrecognized file format.");
			}
		}
		// Jump to the pixel data location
		inp.seekg(test->file_header.offset_data, inp.beg);      // skipuje do pixel informacija,tj pointer na bin datoteku gledavsi od pocetka

		//Namestanje velicina hedera, velicina drugog hedera(DIB), i pocetak piksela
		// Adjust the header fields for output.
		// Some editors will put extra info in the image file, we only save the headers and the data.

		if (test->bmp_info_header.bit_count == 32) {
		//	test->bmp_info_header.size = sizeof(BMPInfoHeader) + sizeof(BMPColorHeader);
		//	test->file_header.offset_data = sizeof(BMPFileHeader) + sizeof(BMPInfoHeader) + sizeof(BMPColorHeader);  //odavde ce poceti pikseli
		}
		else {
			test->bmp_info_header.size = sizeof(BMPInfoHeader);
			test->file_header.offset_data = sizeof(BMPFileHeader) + sizeof(BMPInfoHeader);
		}
		//test->file_header.file_size = test->file_header.offset_data;  //   kasnije se na file_size dodaje i memorija piksela

		if (test->bmp_info_header.height < 0) {
			throw std::runtime_error("The program can treat only BMP images with the origin in the bottom left corner!");
		}

		test->Height = test->bmp_info_header.height;
		test->Width = test->bmp_info_header.width;

		//FORMAT JE BGRA
		
	//	test->data.resize(test->bmp_info_header.width * test->bmp_info_header.height * test->bmp_info_header.bit_count / 8);    //resize vektora(pomnoze se visina sirina i broj bitova po pikselu, pase podeli sa 8 da bi se dobio broj bajtova tj ovo uint8)
		test->pixels.resize(test->bmp_info_header.height * test->bmp_info_header.width);

		// Here we check if we need to take into account row padding
		if (test->bmp_info_header.width % 4 == 0) {
			//puni piksele u memoriju, test.data.size() ce sad imati velicinu svih piksela 
		//	inp.read((char*)test->data.data(), test->data.size());   //.data() -> Returns a direct pointer to the memory array used internally by the vector to store its owned elements
			// ne mora da se pise & jer .data() vraca pointer
		//	test->file_header.file_size += test->data.size();
		//	std::cout << (int)test->data[0] << std::endl;
			test->pixels.clear();
			Pixel pom;
			while (inp.read(reinterpret_cast<char*>(&pom), sizeof(Pixel)))
			{
				pom.A *= test->transparency;
				test->pixels.push_back(pom);
			}
			//test->file_header.file_size += test->pixels.size() * 4;
			inp.close();
		}
		else {
			row_stride = test->bmp_info_header.width * test->bmp_info_header.bit_count / 8;  //broj bajtova po redu da piksele(mora biti umnozak cetvorke)
			uint32_t new_stride = make_stride_aligned(4);
			std::vector<uint8_t> padding_row(new_stride - row_stride); //koliko se padding piksela dodaje

			//inp.read(odakle krece da se puni, koliko se puni)

			for (int y = 0; y < test->bmp_info_header.height; ++y) {
				inp.read((char*)(test->data.data() + row_stride * y), row_stride);   //   prvo ucitava ono sto nam treba
				inp.read((char*)padding_row.data(), padding_row.size());     //pa posle nepotrebne padding bajtove
			}
			test->file_header.file_size += test->data.size() + test->bmp_info_header.height * padding_row.size();
		}
	}
	else {
		throw std::runtime_error("Unable to open the input image file.");
	}
}

// Check if the pixel data is stored as BGRA and if the color space type is sRGB
void BMPFormatter::check_color_header(BMPColorHeader &bmp_color_header) {
	BMPColorHeader expected_color_header;
	if (expected_color_header.red_mask != bmp_color_header.red_mask ||
		expected_color_header.blue_mask != bmp_color_header.blue_mask ||
		expected_color_header.green_mask != bmp_color_header.green_mask ||
		expected_color_header.alpha_mask != bmp_color_header.alpha_mask) {
		throw std::runtime_error("Unexpected color mask format! The program expects the pixel data to be in the BGRA format");
	}
	//	if (expected_color_header.color_space_type != bmp_color_header.color_space_type) {
	//		throw std::runtime_error("Unexpected color space type! The program expects sRGB values");
	//	}
}

uint32_t BMPFormatter::make_stride_aligned(uint32_t align_stride) {
	uint32_t new_stride = row_stride;
	while (new_stride % align_stride != 0) {
		new_stride++;
	}
	return new_stride;
}


void BMPFormatter::write(std::string name, Image &image) {
	//uzme sliku image i upise je u BMP format
	BMPColorHeader pom = image.layers[0]->getColorHeader();;
	//stavio sam pom, jer nije radilo &image.layers[0].getColorHeader().piksel
	if (image.layers.size() != 1)
	{
		std::vector<Pixel> exportPixels = image.flattenLayers();
		ofstream fout("C:\\Users\\ognje\\Desktop\\" + name, ios::out | ios::binary);
		fout.write((char*)&image.layers[0]->getFileHeader(), sizeof(image.layers[0]->getFileHeader()));
		fout.write((char*)&image.layers[0]->getInfoHeader(), sizeof(image.layers[0]->getInfoHeader()));		
		fout.write((char*)&pom.red_mask, sizeof(pom.red_mask));
		fout.write((char*)&pom.green_mask, sizeof(pom.green_mask));
		fout.write((char*)&pom.blue_mask, sizeof(pom.blue_mask));
		fout.write((char*)&pom.alpha_mask, sizeof(pom.alpha_mask));
		fout.write((char*)&pom.color_space_type, sizeof(pom.color_space_type));
		for (int i = 0; i < pom.unused.size(); i++)
			fout.write((char*)&pom.unused[i], sizeof(pom.unused[i]));
		for (int i = 0; i < exportPixels.size(); i++)
		{
			if (image.layers[0]->pixels[i].B > 255) image.layers[0]->pixels[i].B = 255;
			if (image.layers[0]->pixels[i].B < 0) image.layers[0]->pixels[i].B = 0;
			if (image.layers[0]->pixels[i].G > 255) image.layers[0]->pixels[i].G = 255;
			if (image.layers[0]->pixels[i].G < 0) image.layers[0]->pixels[i].G = 0;
			if (image.layers[0]->pixels[i].R > 255) image.layers[0]->pixels[i].R = 255;
			if (image.layers[0]->pixels[i].R < 0) image.layers[0]->pixels[i].R = 0;
			fout.write((char*)&exportPixels[i], sizeof(exportPixels[i]));
		}
	}
	else
	{
		ofstream fout("C:\\Users\\ognje\\Desktop\\" + name, ios::out | ios::binary);
		fout.write((char*)&image.layers[0]->getFileHeader(), sizeof(image.layers[0]->getFileHeader()));
		fout.write((char*)&image.layers[0]->getInfoHeader(), sizeof(image.layers[0]->getInfoHeader()));
		fout.write((char*)&pom.red_mask, sizeof(pom.red_mask));
		fout.write((char*)&pom.green_mask, sizeof(pom.green_mask));
		fout.write((char*)&pom.blue_mask, sizeof(pom.blue_mask));
		fout.write((char*)&pom.alpha_mask, sizeof(pom.alpha_mask));
		fout.write((char*)&pom.color_space_type, sizeof(pom.color_space_type));
		for (int i = 0; i < pom.unused.size(); i++)
			fout.write((char*)&pom.unused[i], sizeof(pom.unused[i]));
		for (int i = 0; i < image.layers[0]->pixels.size(); i++)
		{
			if (image.layers[0]->pixels[i].B > 255) image.layers[0]->pixels[i].B = 255;
			if (image.layers[0]->pixels[i].B < 0) image.layers[0]->pixels[i].B = 0;
			if (image.layers[0]->pixels[i].G > 255) image.layers[0]->pixels[i].G = 255;
			if (image.layers[0]->pixels[i].G < 0) image.layers[0]->pixels[i].G = 0;
			if (image.layers[0]->pixels[i].R > 255) image.layers[0]->pixels[i].R = 255;
			if (image.layers[0]->pixels[i].R < 0) image.layers[0]->pixels[i].R = 0;
			fout.write((char*)&image.layers[0]->pixels[i], sizeof(image.layers[0]->pixels[i]));
		}
	}
}
