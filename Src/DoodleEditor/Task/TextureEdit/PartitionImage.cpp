#include "PartitionImage.h"

#include <wxGUI/wxGUI.h>
#include <SOIL/SOIL.h>
// #include <SOIL/stb_image_write.h>

using namespace deditor::texture_edit;

void PartitionImage::partition(const wxString& filepath, 
							   size_t row, size_t col)
{
	int sw, sh, sc;
	unsigned char* src_data = SOIL_load_image(filepath.c_str(), &sw, &sh, &sc, 0);

	int width = std::ceil((float) sw / col);
	int height = std::ceil((float) sh / row);

	wxString path_part = wxgui::FilenameTools::getFilePathExceptExtension(filepath);

	unsigned char* dst_data = (unsigned char*) malloc(sc * width * height);
	for (size_t i = 0; i < col; ++i)
	{
		size_t dw = (i == col - 1) ? sw - width * (col - 1) : width;
		for (size_t j = 0; j < row; ++j)
		{
			size_t dh = (j == row - 1) ? sh - height * (row - 1) : height;
			memset(dst_data, 0, sc * dw * dh);
			for (size_t iRow = 0; iRow < dh; ++iRow) {
				for (size_t iCol = 0; iCol < dw; ++iCol) {
					const int baseFrom = (sw * (j * height + iRow) + i * width + iCol) * sc,
						baseTo = (iRow * width + iCol) * sc;
					for (size_t iCanel = 0; iCanel < sc; ++iCanel)
						dst_data[baseTo + iCanel] = src_data[baseFrom + iCanel];
				}
			}

			wxString dstFile = path_part + "_" + wxString::FromDouble(int(j)) + "_" + wxString::FromDouble(int(i)) + ".jpg";

			wxgui::LibJpeg::ImageData data;
			data.width = dw;
			data.height = dh;
			data.pixels = dst_data;
			wxgui::LibJpeg::write_JPEG_file(dstFile.c_str(), 80, data);
		}
	}

	delete[] src_data;
	//	free((void*)dst_data);
}
