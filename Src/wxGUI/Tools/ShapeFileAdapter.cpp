#include "ShapeFileAdapter.h"
#include "FileNameTools.h"

#include "Dataset/PolygonShape.h"
#include "Dataset/SymbolMgr.h"
#include "Dataset/ImageSymbol.h"

#include <Fruits2D/Fruits2D.h>

using namespace wxgui;

ShapeFileAdapter::~ShapeFileAdapter()
{
	for_each(m_layers.begin(), m_layers.end(), DeletePointerFunctor<Layer>());
	m_layers.clear();
}

void ShapeFileAdapter::load(const char* filename)
{
	wxString filepathFixed = FilenameTools::getExistFilepath(filename);
	if (filepathFixed == wxEmptyString)
		return;

	std::ifstream fin(filepathFixed.fn_str());

	wxString colorStr = StringTools::getLine(fin);
	m_color.FromString(colorStr);

	size_t layerSize;
	fin >> layerSize;
	for (size_t i = 0; i < layerSize; ++i)
	{
		Layer* layer = new Layer;

		layer->name = StringTools::getLine(fin);

		size_t shapeSize;
		fin >> shapeSize;
		for (size_t j = 0; j < shapeSize; ++j)
		{
			int type;
			f2Colorf color;
			wxString texPath;
			fin >> type;
			if (type == PolygonShape::e_Color)
				fin >> color;
			else if (type == PolygonShape::e_Texture)
				texPath = StringTools::getLine(fin);

			std::vector<f2Vec2> bound;
			size_t boundSize;
			fin >> boundSize;
			bound.reserve(boundSize);
			for (size_t k = 0; k < boundSize; ++k)
			{
				f2Vec2 pos;
				fin >> pos;
				bound.push_back(pos);
			}

			PolygonShape* poly = new PolygonShape(bound);
			poly->m_fillingType = type;
			if (type == PolygonShape::e_Color)
				poly->m_fillingColor = color;
			else if (type == PolygonShape::e_Texture)
				poly->m_fillingTexture = static_cast<ImageSymbol*>(SymbolMgr::Instance()->getSymbol(texPath));
			else
				continue;
			poly->buildFillingTris();
			layer->polys.push_back(poly);
		}

		m_layers.push_back(layer);
	}

	fin.close();
}

//////////////////////////////////////////////////////////////////////////
// class ShapeFileAdapter::Layer
//////////////////////////////////////////////////////////////////////////

ShapeFileAdapter::Layer::~Layer()
{
	for (size_t i = 0, n = polys.size(); i < n; ++i)
		polys[i]->release();
	polys.clear();
}