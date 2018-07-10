#ifndef _WX_GUI_LIB_JPEG_H_
#define _WX_GUI_LIB_JPEG_H_

#include <stdlib.h>

namespace wxgui
{
	class LibJpeg
	{
	public:
		struct ImageData 
		{
			unsigned char* pixels;
			int width;
			int height;
			int channels;

			ImageData() : pixels(NULL), width(0), height(0), channels(0) {}
		};

	public:
		static void write_JPEG_file(const char* filename, int quality, const ImageData& data);
		static int read_JPEG_file(const char* filename, ImageData& data);

	}; // LibJpeg
}

#endif // _WX_GUI_LIB_JPEG_H_