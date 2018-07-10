#ifndef _FEDITOR_LIB_JPEG_H_
#define _FEDITOR_LIB_JPEG_H_

namespace FEDITOR
{
	class LibJpeg
	{
	public:
		static void write_JPEG_file(const char* filename, int w, int h, int quality, unsigned char* data);

	}; // LibJpeg
}

#endif // _FEDITOR_LIB_JPEG_H_