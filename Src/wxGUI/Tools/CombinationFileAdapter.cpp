#include "CombinationFileAdapter.h"
#include "FileNameTools.h"

using namespace wxgui;

void CombinationFileAdapter::load(const char* filename)
{
	m_data.clear();

	std::ifstream fin(filename);

	size_t size;
	fin >> size;
	m_data.reserve(size);
	for (size_t i = 0; i < size; ++i)
	{
		Entry entry;

		entry.filepath = StringTools::getLine(fin);
		entry.filepath = FilenameTools::getExistFilepath(entry.filepath);

		std::string strLine = StringTools::getLine(fin);
		std::stringstream ss(strLine);
		ss >> entry.pos >> entry.angle >> entry.scale >> entry.xMirror >> entry.yMirror;

		m_data.push_back(entry);
	}

	fin.close();
}