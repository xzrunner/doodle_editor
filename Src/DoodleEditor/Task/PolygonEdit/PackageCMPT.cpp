#include "PackageCMPT.h"
#include "StagePanel.h"
#include "PackageFileIO.h"

#include "Frame/defs.h"
#include "Task/MotoX/TileFileAdapter.h"

#include <wx/spinctrl.h>

using namespace deditor::polygon_edit;

PackageCMPT::PackageCMPT(wxWindow* parent, const wxString& name,
						 StagePanel* editPanel)
	 : AbstractEditCMPT(parent, name, editPanel)
	 , m_editPanel(editPanel)
{
	m_editOP = new wxgui::ZoomViewOP(editPanel, true);
}

void PackageCMPT::packageToBin(const wxString& src, const wxString& mergeFile,
							   const wxString& motoxFile, const wxString& dst)
{
	const float GRID_WIDTH = 400.0f;

	wxgui::ShapeFileAdapter adapter;
	adapter.load(src.c_str());

	std::vector<wxgui::Layer*> layers;
	layers.push_back(loadMotoXLayer(motoxFile));
	for (size_t i = 0, n = adapter.m_layers.size(); i < n; ++i)
	{
		wxgui::ShapeFileAdapter::Layer* srcLayer = adapter.m_layers[i];
		wxgui::Layer* dstLayer = new wxgui::Layer;

		dstLayer->setName(srcLayer->name);
		for (size_t j = 0, m = srcLayer->polys.size(); j < m; ++j)
		{
			srcLayer->polys[j]->retain();
			dstLayer->insert(srcLayer->polys[j]);
		}

		layers.push_back(dstLayer);
	}
	
	{
		f2AABB aabb;
		aabb.makeInfinite();
		for (size_t i = 0, n = layers.size(); i < n; ++i)
			layers[i]->traverseShapes(GetTotAABBVisitor(aabb));

		std::vector<f2Vec2> lines;
		lines.reserve((aabb.xLength() / GRID_WIDTH) * 2);
		float xCurr = aabb.xMin + GRID_WIDTH;
		while (xCurr < aabb.xMax)
		{
			lines.push_back(f2Vec2(xCurr, aabb.yMin - 100));
			lines.push_back(f2Vec2(xCurr, aabb.yMax + 100));
			xCurr += GRID_WIDTH;
		}

		for (size_t i = 0, n = layers.size(); i < n; ++i)
			layers[i]->traverseShapes(TriangulateVisitor(wxgui::Math::e_Constrained, lines));
	}

	automatic_merge::FileAdapter merged;
	merged.resolve(mergeFile);

	PackageFileIO fileIO(merged, GRID_WIDTH);
	fileIO.storeToFile(dst, layers);
}

wxSizer* PackageCMPT::initLayout()
{
	wxSizer* sizer = new wxBoxSizer(wxVERTICAL);
	{
		wxButton* btnOut = new wxButton(this, wxID_ANY, wxT("导出bin..."));
		Connect(btnOut->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, 
			wxCommandEventHandler(PackageCMPT::onStoreToBinFile));
		sizer->Add(btnOut);

		sizer->AddSpacer(5);

		wxButton* btnIn = new wxButton(this, wxID_ANY, wxT("导入bin..."));
		Connect(btnIn->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, 
			wxCommandEventHandler(PackageCMPT::onLoadFromBinFile));
		sizer->Add(btnIn);

		sizer->AddSpacer(10);

		wxButton* btnMerged = new wxButton(this, wxID_ANY, wxT("导入合图文件..."));
		Connect(btnMerged->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, 
			wxCommandEventHandler(PackageCMPT::onLoadMergedFile));
		sizer->Add(btnMerged);

		wxButton* btnMotox = new wxButton(this, wxID_ANY, wxT("导入motox..."));
		Connect(btnMotox->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, 
			wxCommandEventHandler(PackageCMPT::onLoadMotoXFile));
		sizer->Add(btnMotox);

		sizer->AddSpacer(10);

		wxButton* btnOutText = new wxButton(this, wxID_ANY, wxT("导出伟强版..."));
		Connect(btnOutText->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, 
			wxCommandEventHandler(PackageCMPT::onStoreToTextFile));
		sizer->Add(btnOutText);
	}
	sizer->AddSpacer(20);
	{
		wxArrayString choices;
		choices.Add(wxT("constrained"));
		choices.Add(wxT("conforming"));
		choices.Add(wxT("角度"));
		choices.Add(wxT("面积"));
		choices.Add(wxT("数量"));

		m_typeChoice = new wxRadioBox(this, wxID_ANY, wxT("三角剖分"), 
			wxDefaultPosition, wxDefaultSize, choices, 1, wxRA_SPECIFY_COLS);
		Connect(m_typeChoice->GetId(), wxEVT_COMMAND_RADIOBOX_SELECTED, 
			wxCommandEventHandler(PackageCMPT::onChangeTriangulateType));
		sizer->Add(m_typeChoice);
	}
	sizer->AddSpacer(10);
	{
		m_widthSpin = new wxSpinCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, 
			wxSize(50, -1), wxSP_ARROW_KEYS, 10, 1000, 400);
		Connect(m_widthSpin->GetId(), wxEVT_COMMAND_SPINCTRL_UPDATED, 
			wxSpinEventHandler(PackageCMPT::onSetGridWidth));
		sizer->Add(m_widthSpin);
	}
	return sizer;
}

void PackageCMPT::onStoreToBinFile(wxCommandEvent& event)
{
 	wxString filter = wxT("*_surface.bin");
 	wxFileDialog dlg(this, wxT("导出二进制文件"), wxEmptyString, wxEmptyString, filter, wxFD_SAVE);
 	if (dlg.ShowModal() == wxID_OK)
 	{
 		wxString fixed = wxgui::FilenameTools::getFilenameAddTag(dlg.GetPath(), "surface", "bin");
		PackageFileIO fileIO(m_merged, m_widthSpin->GetValue());

		std::vector<wxgui::Layer*> layers;
		m_editPanel->getLayersMgr()->traverseAllLayers(FetchAllVisitor<wxgui::Layer>(layers));

		fileIO.storeToFile(fixed, layers);
 	}
}

void PackageCMPT::onLoadFromBinFile(wxCommandEvent& event)
{
 	wxString filter = wxT("*_surface.bin");
 	wxFileDialog dlg(this, wxT("导入二进制文件"), wxEmptyString, wxEmptyString, filter, wxFD_OPEN);
 	if (dlg.ShowModal() == wxID_OK)
 	{
		PackageFileIO fileIO(m_merged, m_widthSpin->GetValue());

		std::vector<wxgui::Layer*> layers;
		fileIO.loadFromFile(dlg.GetPath(), layers);

		for (size_t i = 0, n = layers.size(); i < n; ++i)
			m_editPanel->getLayersMgr()->addLayer(layers[i]);

		m_editPanel->Refresh();
 	}
}

void PackageCMPT::onLoadMergedFile(wxCommandEvent& event)
{
	wxString filter = "*_" + AUTOMATIC_MERGE_TASK_TAG + ".txt";
	wxFileDialog dlg(this, wxT("选择合图文件"), wxEmptyString, wxEmptyString, filter, wxFD_OPEN);
	if (dlg.ShowModal() == wxID_OK)
	{
		m_merged.resolve(dlg.GetPath());
	}
}

void PackageCMPT::onLoadMotoXFile(wxCommandEvent& event)
{
	wxString filter = "*_" + MOTOX_TASK_TAG + ".txt";
	wxFileDialog dlg(this, wxT("选择motox文件"), wxEmptyString, wxEmptyString, filter, wxFD_OPEN);
	if (dlg.ShowModal() == wxID_OK)
	{
		wxgui::Layer* layer = loadMotoXLayer(dlg.GetPath());

		wxgui::LayersMgrWidget* layersMgr = m_editPanel->getLayersMgr();
		layersMgr->addLayerBottom(layer);

		m_editPanel->Refresh();
	}
}

void PackageCMPT::onStoreToTextFile(wxCommandEvent& event)
{
	wxString filter = wxT("*_surface(wq).txt");
	wxFileDialog dlg(this, wxT("导出text文件"), wxEmptyString, wxEmptyString, filter, wxFD_SAVE);
	if (dlg.ShowModal() == wxID_OK)
	{
		wxString fixed = wxgui::FilenameTools::getFilenameAddTag(dlg.GetPath(), "surface(wq)", "txt");
		PackageFileIO fileIO(m_merged, m_widthSpin->GetValue());

		std::vector<wxgui::Layer*> layers;
		m_editPanel->getLayersMgr()->traverseAllLayers(FetchAllVisitor<wxgui::Layer>(layers));

		fileIO.storeToTextFile(fixed, layers);
	}
}

void PackageCMPT::onChangeTriangulateType(wxCommandEvent& event)
{
	triangulateAllPolygons();
}

void PackageCMPT::onSetGridWidth(wxSpinEvent& event)
{
	triangulateAllPolygons();
}

void PackageCMPT::triangulateAllPolygons()
{
	f2AABB aabb;
	aabb.makeInfinite();
	m_editPanel->traverseShapes(GetTotAABBVisitor(aabb));

	std::vector<f2Vec2> lines;
	lines.reserve((aabb.xLength() / m_widthSpin->GetValue()) * 2);
	float xCurr = aabb.xMin + m_widthSpin->GetValue();
	while (xCurr < aabb.xMax)
	{
		lines.push_back(f2Vec2(xCurr, aabb.yMin - 100));
		lines.push_back(f2Vec2(xCurr, aabb.yMax + 100));
		xCurr += m_widthSpin->GetValue();
	}

	m_editPanel->traverseShapes(TriangulateVisitor(wxgui::Math::TriangulateType(m_typeChoice->GetSelection()), lines));
	m_editPanel->Refresh();
}

wxgui::Layer* PackageCMPT::loadMotoXLayer(const wxString& filepath)
{
	motox::TileFileAdapter adapter;
	adapter.resolve(filepath);

	wxgui::Layer* layer = new wxgui::Layer;
	layer->setName(wxT("motox"));
	for (size_t i = 0, n = adapter.m_layers.size(); i < n; ++i)
	{
		for (size_t j = 0, m = adapter.m_layers[i]->sprites.size(); j < m; ++j)
		{
			wxgui::ShapeSprite* shapeSprite 
				= dynamic_cast<wxgui::ShapeSprite*>(adapter.m_layers[i]->sprites[j]);
			if (shapeSprite)
			{
				bool xMirror, yMirror;
				shapeSprite->getMirror(xMirror, yMirror);

				const wxgui::ShapeSymbol& symbol = shapeSprite->getSymbol();
				const std::vector<wxgui::IShape*>& shapes = symbol.getAllShapes();
				for (size_t k = 0, l = shapes.size(); k < l; ++k)
				{
					wxgui::PolygonShape* poly = dynamic_cast<wxgui::PolygonShape*>(shapes[k])->clone();

					std::vector<f2Vec2> vertices = poly->getVertices();
					for (size_t i = 0, n = vertices.size(); i < n; ++i)
					{
						if (xMirror)
							vertices[i].x = -vertices[i].x;
						if (yMirror)
							vertices[i].y = -vertices[i].y;
						vertices[i] += shapeSprite->getPosition();
					}
					poly->setVertices(vertices);
					poly->buildFillingTris();

					layer->insert(poly);
				}
			}
		}
	}

	return layer;
}

//////////////////////////////////////////////////////////////////////////  
// class PackageCMPT::GetTotAABBVisitor
//////////////////////////////////////////////////////////////////////////

void PackageCMPT::GetTotAABBVisitor::visit(IObject* object, bool& bFetchNext)
{
	wxgui::PolygonShape* poly = dynamic_cast<wxgui::PolygonShape*>(object);
	if (!poly) return;

	m_aabb.combine(poly->getAABB());

	bFetchNext = true;
}

//////////////////////////////////////////////////////////////////////////
// class PackageCMPT::TriangulateVisitor
//////////////////////////////////////////////////////////////////////////

void PackageCMPT::TriangulateVisitor::visit(IObject* object, bool& bFetchNext)
{
	bFetchNext = true;

	wxgui::PolygonShape* poly = dynamic_cast<wxgui::PolygonShape*>(object);
	if (!poly) return;

	if (poly->m_fillingType == wxgui::PolygonShape::e_Null)
	{
		poly->m_fillingType = wxgui::PolygonShape::e_Color;
		poly->m_fillingColor = f2Colorf(0, 0, 0);
	}
	poly->buildFillingTris(m_lines);
}