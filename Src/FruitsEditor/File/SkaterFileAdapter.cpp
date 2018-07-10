#include "SkaterFileAdapter.h"
#include "Dataset/Layer.h"

using namespace FEDITOR;

SkaterFileAdapter::~SkaterFileAdapter()
{
	for (size_t i = 0, n = m_data.size(); i < n; ++i)
		for_each(m_data[i]->entries.begin(), m_data[i]->entries.end(), DeletePointerFunctor<Entry>());
}

void SkaterFileAdapter::load(const std::string& filename)
{
	std::ifstream fin(filename.c_str());

	size_t cLayer;
	fin >> cLayer;
	for (size_t i = 0; i < cLayer; ++i)
	{
		Batch* layer = new Batch;
		size_t cSprite;
		fin >> cSprite;
		for (size_t j = 0; j < cSprite; ++j)
		{
			Entry* sprite = new Entry;
			fin >> sprite->filename >> sprite->pos >> sprite->angle >> sprite->xScale >> sprite->yScale >> sprite->leftLow >> sprite->rightTop;
			layer->entries.push_back(sprite);
		}
		m_data.push_back(layer);
	}

	fin.close();
}