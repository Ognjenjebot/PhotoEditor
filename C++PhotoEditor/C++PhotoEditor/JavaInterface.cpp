#include"gui_Image.h"
#include"Layer.h"
#include"Formatter.h"
#include"Image.h"
#include"BMPFormatter.h"
#include"BMPLayer.h"
#include<fstream>
#include<iostream>


JNIEXPORT jbyteArray JNICALL Java_gui_Image_loadBMPImage(JNIEnv* env, jobject, jstring path) {
	const char* _nativeString = env->GetStringUTFChars(path, 0);
	char *nativeString = _strdup(_nativeString);
	env->ReleaseStringUTFChars(path, _nativeString);
	std::ifstream inp(nativeString, std::ios_base::binary);

	BMPLayer* test = new BMPLayer();

	if (inp) {
		inp.read((char*)&test->file_header, 14);
		if (test->file_header.file_type != 0x4D42) {
			throw std::runtime_error("Error! Unrecognized file format.");
		}
		inp.read((char*)&test->bmp_info_header, sizeof(BMPInfoHeader));



		//--------------------------------------------------------------------------------------------------------------------

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
				//check_color_header(test->bmp_color_header);
			}
			else {
				//	std::cerr << "Warning! The file \"" << name << "\" does not seem to contain bit mask information\n";
				throw std::runtime_error("Error! Unrecognized file format.");
			}
		}

		//--------------------------------------------------------------------------------------------------------------------


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

		if (test->bmp_info_header.width % 4 == 0) {
			test->pixels.clear();
			Pixel pom;
			while (inp.read(reinterpret_cast<char*>(&pom), sizeof(Pixel)))
			{
				//pom.A *= test->transparency;
				test->pixels.push_back(pom);
			}
		}


		unsigned char* data = new unsigned char[test->getFileHeader().file_size];

		char *fileH = reinterpret_cast<char*>(&test->file_header);
		int k = 0;
		for (int i = 0; i < 14; i++) data[k++] = fileH[i];

		char *infoH = reinterpret_cast<char*>(&test->bmp_info_header);
		for (int i = 0; i < 40; i++) data[k++] = infoH[i];

		//ovo je dodato novo

		char *fileC1 = reinterpret_cast<char*>(&test->bmp_color_header.red_mask);
		for (int i = 0; i < 4; i++) data[k++] = fileC1[i];
		char *fileC2 = reinterpret_cast<char*>(&test->bmp_color_header.green_mask);
		for (int i = 0; i < 4; i++) data[k++] = fileC2[i];
		char *fileC3 = reinterpret_cast<char*>(&test->bmp_color_header.blue_mask);
		for (int i = 0; i < 4; i++) data[k++] = fileC3[i];
		char *fileC4 = reinterpret_cast<char*>(&test->bmp_color_header.alpha_mask);
		for (int i = 0; i < 4; i++) data[k++] = fileC4[i];
		char *fileC5 = reinterpret_cast<char*>(&test->bmp_color_header.color_space_type);
		for (int i = 0; i < 4; i++) data[k++] = fileC5[i];

		for (int i = 0; i < test->bmp_color_header.unused.size(); i++) {
			uint32_t un = test->bmp_color_header.unused.at(i);
			char *fileC6 = reinterpret_cast<char*>(&un);
			for (int j = 0; j < 4; j++)
				data[k++] = fileC6[j];
		}
		//------------------------------------------------

		for (int i = 0; i < test->pixels.size(); i++) {
			Pixel* pixel = &test->pixels.at(i);
			data[k++] = pixel->B;
			data[k++] = pixel->G;
			data[k++] = pixel->R;
			data[k++] = pixel->A;
		}



		jbyteArray jarray = env->NewByteArray(test->getFileHeader().file_size);
		env->SetByteArrayRegion(jarray, 0, test->getFileHeader().file_size, (const signed char*)data);
		return jarray;
	}
	else {
		return 0;
	}
}


JNIEXPORT jboolean JNICALL Java_gui_Image_exportBMPImage
(JNIEnv *env, jobject, jbyteArray arr, jstring path) {
	const char* _nativeString = env->GetStringUTFChars(path, 0);
	char *nativeString = _strdup(_nativeString);
	env->ReleaseStringUTFChars(path, _nativeString);
	std::ofstream fout("C:\\Users\\ognje\\Desktop\\test2.bmp", ios::out | ios::binary);

	int len = env->GetArrayLength(arr);
	unsigned char* buf = new unsigned char[len];
	env->GetByteArrayRegion(arr, 0, len, reinterpret_cast<jbyte*>(buf));
	for (int i = 0; i < len; i++)
		fout.write((char*)&buf[i], sizeof(unsigned char));


	return true;
}

/*char niz[1];
jbyteArray jarray = env->NewByteArray(1);
env->SetByteArrayRegion(jarray, 0,1, (const signed char*)niz);
return jarray;*/


/*
void main() {
	std::ifstream inp("C:\\Users\\Tail\\Documents\\zizak.bmp", std::ios_base::binary);

	BMPLayer* test = new BMPLayer();

	if (inp) {
		inp.read((char*)&test->file_header, 14);
		if (test->file_header.file_type != 0x4D42) {
			throw std::runtime_error("Error! Unrecognized file format.");
		}
		inp.read((char*)&test->bmp_info_header, sizeof(BMPInfoHeader));


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
	//	test->pixels.resize(test->bmp_info_header.height * test->bmp_info_header.width);


		char* data = new char[test->getFileHeader().file_size];
		char* fileH = reinterpret_cast<char*>(&test->file_header);
		int k = 0;
		for (int i = 0; i < 14; i++) data[k++] = fileH[i];

		char* infoH = reinterpret_cast<char*>(&test->bmp_info_header);
		for (int i = 0; i < 40; i++) data[k++] = infoH[i];

		for (int i = 0; i < test->pixels.size(); i++) {
			char* pixelB = reinterpret_cast<char*>(&test->pixels.at(i));
			for (int j = 0; j < 4; j++)
				data[k++] = pixelB[4];
		}
	}
}*/
