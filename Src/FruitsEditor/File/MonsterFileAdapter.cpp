#include "MonsterFileAdapter.h"

using namespace FEDITOR;

void MonsterFileAdapter::load(const std::string& filename)
{
	std::ifstream fin(filename.c_str());

	fin >> m_time >> m_length >> m_minEmptyGrid >> m_maxEmptyGrid;;
	size_t size;
	fin >> size;
	m_items.reserve(size);
	for (size_t i = 0; i < size; ++i)
	{
		Item item;
		fin >> item.name >> item.col >> item.row >> item.id;
		m_items.push_back(item);
	}

	fin.close();
}