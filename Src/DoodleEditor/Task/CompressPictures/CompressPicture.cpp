#include "CompressPicture.h"

#include <wxGUI/wxGUI.h>
#include <SOIL/SOIL.h>
#include <pngquant/pngquant.cpp>

using namespace deditor::compress_pictures;


CompressPicture::CompressPicture(const CompressParams& params,
								 const wxString& src, const wxString& dst)
	: m_params(params), m_src(src), m_dst(dst) 
{
}

void CompressPicture::compress() const
{
	std::string ext = wxgui::FilenameTools::getExtension(m_src);
	StringTools::toLower(ext);
	if (ext == "jpg")
		compressJpeg();
	else if (ext == "png")
		compressPng();
}

void CompressPicture::compressJpeg() const
{
	wxgui::LibJpeg::ImageData data;
	int channels;
	data.pixels = SOIL_load_image(m_src.c_str(), &data.width, &data.height, &channels, 0);

	wxgui::LibJpeg::write_JPEG_file(m_dst, m_params.m_jpgQuality, data);

	delete[] data.pixels;
}

void CompressPicture::compressPng() const
{
	pngquant_options options;
	options.reqcolors = m_params.m_pngColors;
	options.floyd = true;
	options.min_opaque_val = 1;
	options.speed_tradeoff = m_params.m_pngSpeed;
	options.last_index_transparent = false;

	int retval = 0;

	read_info input_image = {}; // initializes all fields to 0
	write_info output_image = {};

	if (!retval) {
		retval = read_image(m_src, false, &input_image);
	}

	if (!retval) {
		verbose_printf("  read %uKB file corrected for gamma %2.1f\n", (input_image.file_size+1023)/1024,
			1.0/input_image.gamma);

		retval = pngquant(&input_image, &output_image, &options);
	}

	if (input_image.rgba_data) {
		free(input_image.rgba_data);
	}
	if (input_image.row_pointers) {
		free(input_image.row_pointers);
	}

	if (!retval) {
		retval = write_image(&output_image, m_dst, false, false);
	}

	if (output_image.indexed_data) {
		free(output_image.indexed_data);
	}
	if (output_image.row_pointers) {
		free(output_image.row_pointers);
	}
}