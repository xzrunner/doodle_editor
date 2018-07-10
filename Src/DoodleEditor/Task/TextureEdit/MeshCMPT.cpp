#include "MeshCMPT.h"
#include "MeshEditOP.h"
#include "MeshBuilder.h"
#include "StagePanel.h"

using namespace deditor::texture_edit;

MeshCMPT::MeshCMPT(wxWindow* parent, const wxString& name, 
				   StagePanel* editPanel)
	: wxgui::AbstractEditCMPT(parent, name, editPanel)
{
	m_editOP = new MeshEditOP(editPanel, this);
}

int MeshCMPT::getNodeCaptureDistance() const
{
	return m_tolSlider->GetValue();
}

wxSizer* MeshCMPT::initLayout()
{
	wxSizer* topSizer = new wxBoxSizer(wxVERTICAL);
	{
		wxStaticBox* bounding = new wxStaticBox(this, wxID_ANY, wxT("结点捕捉精度"));
		wxBoxSizer* sizer = new wxStaticBoxSizer(bounding, wxVERTICAL);
		m_tolSlider = new wxSlider(this, wxID_ANY, 5, 0, 15, wxDefaultPosition, wxDefaultSize, wxSL_LABELS);
		sizer->Add(m_tolSlider);
		topSizer->Add(sizer);
	}
	topSizer->AddSpacer(10);
	{
		wxButton* btn = new wxButton(this, wxID_ANY, wxT("创建边界"));
		Connect(btn->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, 
			wxCommandEventHandler(MeshCMPT::onCreateTextureBounding));
		topSizer->Add(btn);
	}
	topSizer->AddSpacer(10);
	{
		wxButton* btn = new wxButton(this, wxID_ANY, wxT("输出所选mesh"));
		Connect(btn->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, 
			wxCommandEventHandler(MeshCMPT::onStoreSelectedMesh));
		topSizer->Add(btn);
	}
	return topSizer;
}

void MeshCMPT::onCreateTextureBounding(wxCommandEvent& event)
{
	StagePanel* editPanel = static_cast<StagePanel*>(m_editPanel);

	wxgui::Image* image = editPanel->getTexture();
	if (!image) return;

	const float hWidth = image->width() * 0.5f,
		hHeight = image->height() * 0.5f;

	std::vector<f2Vec2> bounding;
	bounding.push_back(f2Vec2(-hWidth, -hHeight));
	bounding.push_back(f2Vec2( hWidth, -hHeight));
	bounding.push_back(f2Vec2( hWidth,  hHeight));
	bounding.push_back(f2Vec2(-hWidth,  hHeight));
	wxgui::ChainShape* chain = new wxgui::ChainShape(bounding, true);
	editPanel->insertShape(chain);
}

void MeshCMPT::onStoreSelectedMesh(wxCommandEvent& event)
{
	const wxString& tag = wxgui::FileNameParser::getFileTag(wxgui::FileNameParser::e_mesh);
	wxString filter = wxT("*_") + tag + wxT(".txt");
	wxFileDialog dlg(this, wxT("导出mesh文件"), wxEmptyString, wxEmptyString, filter, wxFD_SAVE);
	if (dlg.ShowModal() == wxID_OK)
	{
		wxString fixed = wxgui::FilenameTools::getFilenameAddTag(dlg.GetPath(), tag, "txt");
		storeSelectedMesh(fixed);
	}
}

void MeshCMPT::storeSelectedMesh(const wxString& filepath)
{
	StagePanel* editPanel = static_cast<StagePanel*>(m_editPanel);

	wxgui::Image* image = editPanel->getTexture();
	if (!image) return;

	std::vector<wxgui::ChainShape*> chains;
	editPanel->getShapeSelection()->traverse(FetchAllVisitor<wxgui::ChainShape>(chains));
	if (chains.empty()) return;

	std::vector<std::vector<f2Vec2> > loops;
	loops.reserve(chains.size());
	for (size_t i = 0, n = chains.size(); i < n; ++i)
		loops.push_back(chains[i]->getVertices());

	MeshBuilder builder(*image, loops);
	builder.storeToTextFile(filepath);
}