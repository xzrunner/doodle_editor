#include "TrisFileAdapter.h"
#include "../Dataset/TriangleShape.h"

using namespace FEDITOR;

TrisFileAdapter::~TrisFileAdapter()
{
	for_each(m_layers.begin(), m_layers.end(), DeletePointerFunctor<Layer>());
}

void TrisFileAdapter::load(const std::string& filename)
{
	std::ifstream fin(filename.c_str());

	size_t layerSize;
	fin >> layerSize;
	m_layers.reserve(layerSize);
	for (size_t i = 0; i < layerSize; ++i)
	{
		Layer* layer = new Layer;
		size_t shapeSize;
		fin >> layer->color >> shapeSize;
		layer->shapes.reserve(shapeSize);
		for (size_t j = 0; j < shapeSize; ++j)
		{
			TriangleShape* tri = new TriangleShape;
			tri->loadFromTextFile(fin);
			layer->shapes.push_back(tri);
		}
		m_layers.push_back(layer);
	}

	fin.close();
}