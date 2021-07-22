#pragma once

#include"Formatter.h"



class BMPFormatter : public Formatter {
	void check_color_header(BMPColorHeader &bmp_color_header);
	uint32_t make_stride_aligned(uint32_t align_stride);

	uint32_t row_stride = 0;
public:
	virtual void read(std::string fname, Image &image) override;

	virtual void write(std::string fname,  Image &image) override;
};