#include "FileIO.h"
#include "StagePanel.h"

using namespace deditor::polygon_edit;

void FileIO::load(const wxString& filepath, StagePanel* stage)
{
	wxgui::ShapeFileAdapter adapter;
	adapter.load(filepath.c_str());

	stage->setColorData(adapter.m_color);
	for (size_t i = 0, n = adapter.m_layers.size(); i < n; ++i)
	{
		wxgui::ShapeFileAdapter::Layer* src = adapter.m_layers[i];
		wxgui::Layer* dst = new wxgui::Layer;

		dst->setName(src->name);
		for (size_t j = 0, m = src->polys.size(); j < m; ++j)
		{
			src->polys[j]->retain();
			dst->insert(src->polys[j]);
		}

		stage->getLayersMgr()->addLayer(dst);
	}
}

void FileIO::store(const wxString& filepath, StagePanel* stage)
{
	std::ofstream fout(filepath.fn_str());

	std::vector<wxgui::Layer*> layers;
	stage->getLayersMgr()->traverseAllLayers(FetchAllVisitor<wxgui::Layer>(layers));
	filterPolygonLayer(layers);

	const wxColourData& colorData = stage->getColorData();
	fout << colorData.ToString() << '\n';

	fout << layers.size() << '\n';
	for (size_t i = 0, n = layers.size(); i < n; ++i)
	{
		fout << layers[i]->getName() << '\n';
		const std::vector<wxgui::IShape*>& shapes = layers[i]->getShapes();
		fout << shapes.size() << '\n';
		for (size_t j = 0, m = shapes.size(); j < m; ++j)
		{
			wxgui::PolygonShape* poly = dynamic_cast<wxgui::PolygonShape*>(shapes[j]);
			if (!poly)
			{
				fout << wxgui::PolygonShape::e_Null << '\n';
			}
			else
			{
				fout << poly->m_fillingType << '\n';
				if (poly->m_fillingType == wxgui::PolygonShape::e_Color)
					fout << poly->m_fillingColor << '\n';
				else if (poly->m_fillingType == wxgui::PolygonShape::e_Texture)
					fout << poly->m_fillingTexture->getFilepath() << '\n';
			}

			const std::vector<f2Vec2>& bound = static_cast<wxgui::ChainShape*>(shapes[j])->getVertices();
			fout << bound.size() << '\n';
			for (size_t k = 0, l = bound.size(); k < l; ++k)
				fout << bound[k] << " ";
			fout << '\n';
		}
	}

	fout.close();
}

void FileIO::filterPolygonLayer(std::vector<wxgui::Layer*>& layers)
{
	std::vector<wxgui::Layer*>::iterator itr = layers.begin();
	for ( ; itr != layers.end(); )
	{
		const std::vector<wxgui::IShape*>& shapes = (*itr)->getShapes();
		bool isPolyLayer = true;
		for (size_t i = 0, n = shapes.size(); i < n; ++i)
		{
			if (!dynamic_cast<wxgui::PolygonShape*>(shapes[i]))
			{
				isPolyLayer = false;
				break;
			}
		}

		if (!isPolyLayer || shapes.empty())
			itr = layers.erase(itr);
		else
			++itr;
	}
}