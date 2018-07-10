#include "ObstacleCommonCMPT.h"
#include "ObstacleCommonPasteCMPT.h"
#include "StagePanel.h"

using namespace deditor::motox;

ObstacleCommonCMPT::ObstacleCommonCMPT(wxWindow* parent, const wxString& name,
									   StagePanel* editPanel, wxgui::LibraryPanel* libraryPanel,
									   wxgui::PropertySettingPanel* propertyPanel)
	: wxgui::AbstractEditCMPT(parent, name, editPanel)
{
	addChild(new ObstacleCommonPasteCMPT(this, wxT("Õ³ÌùÕÏ°­"), editPanel, libraryPanel));

	wxgui::UniversalArrangeCMPT* arrangeCMPT = new wxgui::UniversalArrangeCMPT(this, wxT("µ÷ÕûÕÏ°­"), editPanel, editPanel, propertyPanel);
	arrangeCMPT->addPhysicsEditOP(editPanel->getWorld(), editPanel->getGround());
	arrangeCMPT->addPhysicsEditOP(editPanel->getWorldReverse(), editPanel->getGroundReverse());
	addChild(arrangeCMPT);
}

wxSizer* ObstacleCommonCMPT::initLayout()
{
	return initChildrenLayout();
}