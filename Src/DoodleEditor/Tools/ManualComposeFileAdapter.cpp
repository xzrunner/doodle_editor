#include "ManualComposeFileAdapter.h"

using namespace deditor;

void ManualComposeFileAdapter::load(const char* filename)
{
	std::ifstream fin(filename);

	std::string bgFilePath;
	getline(fin, bgFilePath);
	m_bgFilename = bgFilePath;
	
	size_t size;
	fin >> size;
	m_items.clear();
	m_items.reserve(size);
	for (size_t i = 0; i < size; ++i)
	{
		Item item;

		item.filename = StringTools::getLine(fin);

		std::string strLine = StringTools::getLine(fin);
		std::stringstream ss(strLine);
		ss >> item.pos >> item.angle; 

		m_items.push_back(item);
	}

	fin.close();
}