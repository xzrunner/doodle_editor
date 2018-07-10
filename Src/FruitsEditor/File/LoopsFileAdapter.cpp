#include "LoopsFileAdapter.h"
#include "../Dataset/ShapeFactory.h"
#include "../Dataset/ChainShape.h"

using namespace FEDITOR;

LoopsFileAdapter::~LoopsFileAdapter()
{
	for_each(m_loops.begin(), m_loops.end(), DeletePointerFunctor<ChainShape>());
}

void LoopsFileAdapter::load(const std::string& filename)
{
	std::ifstream fin(filename.c_str());

	fin >> m_imgFilename >> m_coordsType;

	size_t loopSize;
	fin >> loopSize;
	m_loops.reserve(loopSize);
	for (size_t i = 0; i < loopSize; ++i)
	{
		ChainShape* shape = dynamic_cast<ChainShape*>(ShapeFactory::createShape(fin));
		assert(shape && shape->m_isLoop);
		m_loops.push_back(shape);
	}

	fin.close();
}