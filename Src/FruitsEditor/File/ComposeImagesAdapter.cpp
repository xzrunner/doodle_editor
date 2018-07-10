#include "ComposeImagesAdapter.h"

using namespace FEDITOR;

void ComposeImagesAdapter::load(const std::string& filename)
{
	std::ifstream fin(filename.c_str());

	size_t size;
	fin >> size;
	m_entries.reserve(size);
	for (size_t i = 0; i < size; ++i)
	{
		Entry entry;
		fin >> entry.filename >> entry.x >> entry.y >> entry.angle;
		m_entries.push_back(entry);
	}

	fin.close();
}