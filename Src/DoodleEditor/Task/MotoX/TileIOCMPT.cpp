#include "TileIOCMPT.h"
#include "StagePanel.h"
#include "StageCanvas.h"
#include "TileFileAdapter.h"

#include "Frame/defs.h"

using namespace deditor::motox;

TileIOCMPT::TileIOCMPT(wxWindow* parent, const wxString& name,
					   StagePanel* editPanel, wxgui::LibraryPanel* libraryPanel)
	: AbstractEditCMPT(parent, name, editPanel)
	, m_editPanel(editPanel)
	, m_libraryPanel(libraryPanel)
{
	m_editOP = new wxgui::ZoomViewOP(editPanel, true);
}

void TileIOCMPT::loadToEditpanel(StagePanel* editPanel, const wxString& filepath)
{
	TileFileAdapter adapter;
	adapter.resolve(filepath);

	loadToEditpanel(editPanel, adapter);
}

wxSizer* TileIOCMPT::initLayout()
{
	wxSizer* sizer = new wxBoxSizer(wxVERTICAL);
	{
		m_loadPhysicsCtrl = new wxCheckBox(this, wxID_ANY, wxT("加载物理"));
		m_loadPhysicsCtrl->SetValue(false);
		sizer->Add(m_loadPhysicsCtrl);
	}
	sizer->AddSpacer(5);
	{
		wxButton* btn = new wxButton(this, wxID_ANY, wxT("导入txt..."));
		Connect(btn->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, 
			wxCommandEventHandler(TileIOCMPT::onLoadText));
		sizer->Add(btn);
	}
	{
		wxButton* btn = new wxButton(this, wxID_ANY, wxT("导出txt..."));
		Connect(btn->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, 
			wxCommandEventHandler(TileIOCMPT::onStoreText));
		sizer->Add(btn);
	}
	sizer->AddSpacer(10);
	{
		wxButton* btn = new wxButton(this, wxID_ANY, wxT("导入多边形填充..."));
		Connect(btn->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, 
			wxCommandEventHandler(TileIOCMPT::onLoadPolygonFillings));
		sizer->Add(btn);
	}
	sizer->AddSpacer(20);
	{
		sizer->Add(new wxStaticText(this, wxID_ANY, wxT("当前文件：")));
		sizer->Add(m_currFilenameCtrl = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY));
	}
	return sizer;
}

void TileIOCMPT::onLoadText(wxCommandEvent& event)
{
 	wxString filter = wxT("*_") + MOTOX_TASK_TAG + wxT(".txt");
 	wxFileDialog dlg(this, wxT("导入tile文件"), wxEmptyString, wxEmptyString, filter, wxFD_OPEN);
 	if (dlg.ShowModal() == wxID_OK)
 	{
 		loadFromTextFile(dlg.GetPath());
 		m_currFilenameCtrl->ChangeValue(wxgui::FilenameTools::getFilename(dlg.GetPath()));
 	}
}

void TileIOCMPT::onStoreText(wxCommandEvent& event)
{
 	wxString filter = wxT("*_") + MOTOX_TASK_TAG + wxT(".txt");
 	wxFileDialog dlg(this, wxT("导出tile文件"), wxEmptyString, wxEmptyString, filter, wxFD_SAVE);
 	if (dlg.ShowModal() == wxID_OK)
 	{
 		wxString fixed = wxgui::FilenameTools::getFilenameAddTag(dlg.GetPath(), MOTOX_TASK_TAG, "txt");
 		storeToTextFile(fixed);
 		m_currFilenameCtrl->ChangeValue(wxgui::FilenameTools::getFilename(fixed));
 	}
}

void TileIOCMPT::onLoadPolygonFillings(wxCommandEvent& event)
{
	wxString filter = wxT("*_") + FILLING_POLYGON_TASK_TAG + wxT(".txt");
	wxFileDialog dlg(this, wxT("导入多边形填充文件"), wxEmptyString, wxEmptyString, filter, wxFD_OPEN);
	if (dlg.ShowModal() == wxID_OK)
	{
		loadPolygonFillings(dlg.GetPath());
	}
}

void TileIOCMPT::loadFromTextFile(const wxString& filepath)
{
// 	wxgui::SymbolMgr::Instance()->clear();
// 	wxgui::BitmapMgr::Instance()->clear();

	TileFileAdapter* adapter = NULL;
	if (m_loadPhysicsCtrl->IsChecked())
		adapter = new TileFileAdapter(m_editPanel->getWorld(), m_editPanel->getWorldReverse());
	else
		adapter = new TileFileAdapter();
	adapter->resolve(filepath);

	loadToEditpanel(m_editPanel, *adapter);
	m_editPanel->Refresh();

	delete adapter;

	m_libraryPanel->loadFromSymbolMgr(*wxgui::SymbolMgr::Instance());
}

void TileIOCMPT::storeToTextFile(const wxString& filepath) const
{
	wxgui::LayersMgrWidget* layersMgr = m_editPanel->getLayersMgr();
	std::vector<wxgui::Layer*> layers;
	layersMgr->traverseAllLayers(FetchAllVisitor<wxgui::Layer>(layers));

	std::ofstream fout(filepath.fn_str());
	fout << layers.size() << '\n';
	for (size_t i = 0, n = layers.size(); i < n; ++i)
	{
		wxgui::Layer* layer = layers[i];
		fout << layer->getName() << '\n';

		std::vector<wxgui::ISprite*> sprites = layer->getSprites();
		std::sort(sprites.begin(), sprites.end(), wxgui::SpriteCmp());

		fout << sprites.size() << '\n';
		for (size_t j = 0, m = sprites.size(); j < m; ++j)
			storeToTextFile(fout, sprites[j]);
	}
	fout.close();
}

void TileIOCMPT::loadPolygonFillings(const wxString& filepath)
{
	wxgui::ShapeFileAdapter adapter;
	adapter.load(filepath.c_str());

	StageCanvas* canvas = static_cast<StageCanvas*>(m_editPanel->getCanvas());
	for (size_t i = 0, n = adapter.m_layers.size(); i < n; ++i)
	{
		wxgui::ShapeFileAdapter::Layer* layer = adapter.m_layers[i];
		for (size_t j = 0, m = layer->polys.size(); j < m; ++j)
		{
			layer->polys[j]->retain();
			canvas->m_polys.push_back(layer->polys[j]);
		}
	}
	canvas->Refresh();
}

void TileIOCMPT::storeToTextFile(std::ofstream& fout, wxgui::ISprite* sprite) const
{
	TileFileAdapter::Type type = TileFileAdapter::e_image;

	if (sprite->getBody())
	{
		b2Body* body = sprite->getBody()->getBody();
		if (body->GetWorld() == m_editPanel->getWorld())
			type = body->GetType() == b2_staticBody ? TileFileAdapter::e_physics_static : TileFileAdapter::e_physics;
		else
			type = body->GetType() == b2_staticBody ? TileFileAdapter::e_physics_reverse_static : TileFileAdapter::e_physics_reverse;	
	}

	fout << sprite->getSymbol().getFilepath() << '\n';

	bool xMirror, yMirror;
	sprite->getMirror(xMirror, yMirror);
	fout << sprite->getPosition() << " " << sprite->getAngle() << " " 
		<< sprite->getScale() << " " << type << " " << xMirror << " " << yMirror << '\n';
}

void TileIOCMPT::loadToEditpanel(StagePanel* editPanel, 
								 const TileFileAdapter& adapter)
{
	wxgui::LayersMgrWidget* layers = editPanel->getLayersMgr();
	layers->clear();
	for (size_t i = 0, n = adapter.m_layers.size(); i < n; ++i)
	{
		TileFileAdapter::Layer* src = adapter.m_layers[i];
		wxgui::Layer* dst = new wxgui::Layer;
		dst->setName(src->name);
		for (size_t j = 0, m = src->sprites.size(); j < m; ++j)
		{
			src->sprites[j]->retain();
			dst->insert(src->sprites[j]);
		}
		layers->addLayer(dst);
	}
}