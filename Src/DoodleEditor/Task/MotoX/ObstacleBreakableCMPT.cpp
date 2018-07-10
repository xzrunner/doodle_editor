#include "ObstacleBreakableCMPT.h"
#include "ObstacleBreakableOP.h"
#include "StagePanel.h"

using namespace deditor::motox;

ObstacleBreakableCMPT::ObstacleBreakableCMPT(wxWindow* parent, const wxString& name,
											 StagePanel* editPanel, wxgui::LibraryPanel* libraryPanel,
											 wxgui::PropertySettingPanel* propertyPanel)
	: wxgui::AbstractEditCMPT(parent, name, editPanel)
{
	addChild(new wxgui::UniversalCMPT(this, wxT("Õ³ÌùÕÏ°­"), editPanel, 
		new ObstacleBreakableOP(editPanel, libraryPanel)));
	
	wxgui::UniversalArrangeCMPT* arrangeCMPT = new wxgui::UniversalArrangeCMPT(this, wxT("µ÷ÕûÕÏ°­"), editPanel, editPanel, propertyPanel);
	arrangeCMPT->addPhysicsEditOP(editPanel->getWorld(), editPanel->getGround());
	addChild(arrangeCMPT);
}

wxSizer* ObstacleBreakableCMPT::initLayout()
{
	wxSizer* topSizer = new wxBoxSizer(wxVERTICAL);
	topSizer->Add(initChildrenLayout());
	topSizer->AddSpacer(10);
	{
		wxCheckBox* staticCtrl = new wxCheckBox(this, wxID_ANY, wxT("¹Ì¶¨"));
		staticCtrl->SetValue(false);
		Connect(staticCtrl->GetId(), wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(ObstacleBreakableCMPT::onChangeStaticType));
		topSizer->Add(staticCtrl);
	}
	return topSizer;
}

void ObstacleBreakableCMPT::onChangeStaticType(wxCommandEvent& event)
{
	ObstacleBreakableOP* editOP = static_cast<ObstacleBreakableOP*>(m_editOP);
	editOP->setStatic(event.IsChecked());
}