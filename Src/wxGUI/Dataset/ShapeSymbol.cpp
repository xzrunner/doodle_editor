#include "ShapeSymbol.h"

#include "Dataset/PolygonShape.h"
#include "Tools/ShapeFileAdapter.h"

using namespace wxgui;

ShapeSymbol::ShapeSymbol()
{
}

ShapeSymbol::ShapeSymbol(const ShapeSymbol& symbol)
{
	m_filepath = symbol.m_filepath;
	m_shapes.reserve(symbol.m_shapes.size());
	for (size_t i = 0, n = symbol.m_shapes.size(); i < n; ++i)
		m_shapes.push_back(symbol.m_shapes[i]->clone());
}

ShapeSymbol::~ShapeSymbol()
{
	clear();
}

ShapeSymbol* ShapeSymbol::clone()
{
	return new ShapeSymbol(*this); 
}

void ShapeSymbol::loadFromTextFile(std::ifstream& fin)
{

}

void ShapeSymbol::storeToTextFile(std::ofstream& fout) const
{

}

void ShapeSymbol::reloadTexture() const
{

}

void ShapeSymbol::draw() const
{
	for (size_t i = 0, n = m_shapes.size(); i < n; ++i)
		m_shapes[i]->draw();
}

float ShapeSymbol::getWidth() const
{
	return 0;
}

float ShapeSymbol::getHeight() const
{
	return 0;
}

void ShapeSymbol::loadResources()
{
	clear();

	ShapeFileAdapter adapter;
	adapter.load(m_filepath.c_str());

	for (size_t i = 0, n = adapter.m_layers.size(); i < n; ++i)
	{
		for (size_t j = 0, m = adapter.m_layers[i]->polys.size(); j < m; ++j)
		{
			adapter.m_layers[i]->polys[j]->retain();
			m_shapes.push_back(adapter.m_layers[i]->polys[j]);
		}
	}
}

void ShapeSymbol::clear()
{
	for (size_t i = 0, n = m_shapes.size(); i < n; ++i)
		m_shapes[i]->release();
	m_shapes.clear();
}