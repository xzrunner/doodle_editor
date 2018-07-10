#include "CircleFileAdapter.h"

using namespace FEDITOR;

void CircleFileAdapter::load(const std::string& filename)
{
	std::ifstream fin(filename.c_str());

	fin >> m_imgFilename >> m_width >> m_height;

	fin.close();
}