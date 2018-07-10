#include "TileEditCMPT.h"
#include "TileIOCMPT.h"
#include "PasteTileCMPT.h"
#include "TilePackageCMPT.h"
#include "StagePanel.h"

using namespace deditor::motox;

TileEditCMPT::TileEditCMPT(wxWindow* parent, const wxString& name, 
						   wxgui::LibraryPanel* libraryPanel,
						   wxgui::PropertySettingPanel* propertyPanel,
						   StagePanel* editPanel)
	: wxgui::AbstractEditCMPT(parent, name, editPanel)
	, m_editPanel(editPanel)
	, m_layersMgr(NULL)
{
	addChild(new TileIOCMPT(this, wxT("�������"), editPanel, libraryPanel));
	addChild(new PasteTileCMPT(this, wxT("ճ��Ԫ��"), editPanel, libraryPanel));

	wxgui::UniversalArrangeCMPT* arrangeCMPT 
		= new wxgui::UniversalArrangeCMPT(this, wxT("����Ԫ��"), editPanel, editPanel, propertyPanel);
	arrangeCMPT->addPhysicsEditOP(editPanel->getWorld(), editPanel->getGround());
	arrangeCMPT->addPhysicsEditOP(editPanel->getWorldReverse(), editPanel->getGroundReverse());
	addChild(arrangeCMPT);

	addChild(new TilePackageCMPT(this, wxT("���"), editPanel));
}

TileEditCMPT::~TileEditCMPT()
{
	delete m_layersMgr;
}

wxSizer* TileEditCMPT::initLayout()
{
	wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);

	m_layersMgr = new wxgui::LayersMgrWidget(this, m_editPanel);
	sizer->Add(m_layersMgr);
	sizer->AddSpacer(20);
	sizer->Add(initChildrenLayout());

	return sizer;
}