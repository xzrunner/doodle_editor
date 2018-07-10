#include "StagePanel.h"
#include "StageCanvas.h"

using namespace deditor::polygon_edit;

StagePanel::StagePanel(wxWindow* parent)
	: EditPanel(parent)
	, MultiShapesImpl(this)
	, m_layersMgr(NULL)
{
	m_canvas = new StageCanvas(this);
}

StagePanel::~StagePanel()
{
	clear();
}

void StagePanel::traverseShapes(IVisitor& visitor, 
								wxgui::TraverseType type/* = wxgui::e_allExisting*/) const
{
	std::vector<wxgui::Layer*> layers;
	switch (type)
	{
	case wxgui::e_editable:
		m_layersMgr->traverseEditableLayers(FetchAllVisitor<wxgui::Layer>(layers));
		break;
	case wxgui::e_visible:
		m_layersMgr->traverseVisibleLayers(FetchAllVisitor<wxgui::Layer>(layers));
		break;
	case wxgui::e_selectable:
		m_layersMgr->traverseSelectableLayers(FetchAllVisitor<wxgui::Layer>(layers));
		break;
	case wxgui::e_allExisting:
		m_layersMgr->traverseAllLayers(FetchAllVisitor<wxgui::Layer>(layers));
		break;
	}
	traverseLayersShape(visitor, layers);
}

void StagePanel::removeShape(wxgui::IShape* shape)
{
	wxgui::Layer* layer = m_layersMgr->getEditedLayer();
	if (layer)
	{
		layer->remove(shape);
		shape->release();
	}
}

void StagePanel::insertShape(wxgui::IShape* shape)
{
	wxgui::Layer* layer = m_layersMgr->getEditedLayer();
	if (layer)
	{
		wxgui::ChainShape* chain = static_cast<wxgui::ChainShape*>(shape);
		chain->setClosed(true);
		layer->insert(shape);
	}
}

void StagePanel::clear()
{
	m_shapeSelection->clear();
	m_layersMgr->clear();
	m_canvas->clear();
}

void StagePanel::loadBackgroundLine(const wxString& filepath)
{
	if (wxgui::FileNameParser::getFileType(filepath) != wxgui::FileNameParser::e_polyline)
		return;

	std::vector<wxgui::ChainShape*>* data = new std::vector<wxgui::ChainShape*>;
	wxgui::PolylineFileAdapter fileAdapter(*data);
	fileAdapter.load(filepath.c_str());

	wxgui::Layer* layer = new wxgui::Layer;
	layer->setName(wxT("±³¾°Ïß"));
	for (size_t i = 0, n = data->size(); i < n; ++i)
		layer->insert((*data)[i]);
	m_layersMgr->addLayer(layer);

	Refresh();
}

void StagePanel::loadBorderLine(const wxString& filepath)
{
	if (wxgui::FileNameParser::getFileType(filepath) != wxgui::FileNameParser::e_polyline)
		return;

	std::vector<wxgui::ChainShape*>* data = new std::vector<wxgui::ChainShape*>;
	wxgui::PolylineFileAdapter fileAdapter(*data);
	fileAdapter.load(filepath.c_str());

	wxgui::Layer* layer = m_layersMgr->getEditedLayer();
	if (layer)
	{
		for (size_t i = 0, n = data->size(); i < n; ++i)
		{
			layer->insert(new wxgui::PolygonShape((*data)[i]->getVertices()));
			delete (*data)[i];
		}
		delete data;
		Refresh();
	}
	else
	{
		for (size_t i = 0, n = data->size(); i < n; ++i)
			delete (*data)[i];
		delete data;
	}
}

void StagePanel::traverseLayersShape(IVisitor& visitor, 
									 const std::vector<wxgui::Layer*>& layers) const
{
	bool bStop = false;
	for (size_t i = 0, n = layers.size(); i < n && !bStop; ++i)
	{
		const std::vector<wxgui::IShape*>& shapes = layers[i]->getShapes();		
		std::vector<wxgui::IShape*>::const_iterator itr = shapes.begin();
		for ( ; itr != shapes.end() && !bStop; ++itr)
		{
			bool hasNext = true;
			visitor.visit(*itr, hasNext);
			if (!hasNext) bStop = true;
		}
	}
}