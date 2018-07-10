#include "CircleFileAdapter.h"

#include <Fruits2D/Fruits2D.h>

using namespace wxgui;

void CircleFileAdapter::load(const char* filename)
{
	std::ifstream fin(filename);

	m_imgPath = StringTools::getLine(fin);
	fin >> m_width >> m_height;

	fin.close();
}