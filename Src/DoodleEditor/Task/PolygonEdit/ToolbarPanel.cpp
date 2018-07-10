#include "ToolbarPanel.h"
#include "StagePanel.h"
#include "FileIOCMPT.h"
#include "PackageCMPT.h"

using namespace deditor::polygon_edit;

ToolbarPanel::ToolbarPanel(wxWindow* parent, StagePanel* editPanel)
	: wxgui::ToolbarPanel(parent, editPanel)
	, m_editPanel(editPanel)
	, m_layersMgr(NULL)
{
	addChild(new FileIOCMPT(this, wxT("�������"), editPanel));
	addChild(new wxgui::DrawPolygonCMPT(this, wxT("�������"), editPanel, editPanel, editPanel->getColorData()));
	addChild(new wxgui::EditNodesCMPT(this, wxT("�༭�ڵ�"), editPanel, editPanel));
	addChild(new wxgui::EditPolylinesCMPT(this, wxT("�༭��"), editPanel, editPanel));
	addChild(new PackageCMPT(this, wxT("���"), editPanel));

	SetSizer(initLayout());	
}

ToolbarPanel::~ToolbarPanel()
{
	delete m_layersMgr;
}

wxSizer* ToolbarPanel::initLayout()
{
	wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);

	m_layersMgr = new wxgui::LayersMgrWidget(this, m_editPanel);
	sizer->Add(m_layersMgr);
	sizer->AddSpacer(20);
 	sizer->Add(initChildrenLayout());

	return sizer;
}
