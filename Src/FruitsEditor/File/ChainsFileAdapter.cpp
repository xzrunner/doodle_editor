#include "ChainsFileAdapter.h"
#include "../Dataset/ShapeFactory.h"
#include "../Dataset/ChainShape.h"

using namespace FEDITOR;

ChainsFileAdapter::~ChainsFileAdapter()
{
	for_each(m_chains.begin(), m_chains.end(), DeletePointerFunctor<ChainShape>());
}

void ChainsFileAdapter::load(const std::string& filename)
{
	std::ifstream fin(filename.c_str());

	size_t chainSize;
	fin >> chainSize;
	m_chains.reserve(chainSize);
	for (size_t i = 0; i < chainSize; ++i)
	{
		ChainShape* shape = dynamic_cast<ChainShape*>(ShapeFactory::createShape(fin));
		assert(shape && !shape->m_isLoop);
		m_chains.push_back(shape);
	}

	fin.close();
}