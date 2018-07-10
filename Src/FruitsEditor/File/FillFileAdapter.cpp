#include "FillFileAdapter.h"
#include "../Dataset/ShapeFactory.h"
#include "../Dataset/ChainShape.h"

using namespace FEDITOR;

FillFileAdapter::~FillFileAdapter()
{
	for_each(m_regions.begin(), m_regions.end(), DeletePointerFunctor<Region>());
}

void FillFileAdapter::load(const std::string& filename)
{
	std::ifstream fin(filename.c_str());

	size_t size;
	fin >> size;
	m_regions.reserve(size);
	for (size_t i = 0; i < size; ++i)
	{
		Region* r = new Region;

		fin >> r->filename;
		ChainShape* cs = static_cast<ChainShape*>(ShapeFactory::createShape(fin));
		assert(cs && cs->m_isLoop);
		r->shape = cs;
		
		m_regions.push_back(r);
	}

	fin.close();
}