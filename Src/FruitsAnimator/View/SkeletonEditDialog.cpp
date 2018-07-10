#include "SkeletonEditDialog.h"
#include "SkeletonSymbolList.h"
#include "SkeletonEditPanel.h"

using namespace FRUITS_ANIMATOR;

BEGIN_EVENT_TABLE(SkeletonEditDialog, wxDialog)
	EVT_SIZE(SkeletonEditDialog::onSize)
END_EVENT_TABLE()

SkeletonEditDialog::SkeletonEditDialog(wxWindow* parent, WholeSkeleton* skeleton,
									   LibraryPanel* library)
 	: wxDialog(parent, wxID_ANY, "Edit Skeleton", wxDefaultPosition, 
	wxSize(800, 600), wxCLOSE_BOX | wxCAPTION/* | wxMAXIMIZE_BOX*/)
{
	m_skeleton = skeleton;
	initLayout(library);
}

SkeletonEditDialog::~SkeletonEditDialog()
{
	delete m_editPanel;
}

void SkeletonEditDialog::onSize(wxSizeEvent& event)
{
	Layout();
	Refresh();
}

void SkeletonEditDialog::initLayout(LibraryPanel* library)
{
	wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);

	SkeletonSymbolList* skeletonList = new SkeletonSymbolList(this, library);
	sizer->Add(skeletonList, 1, wxEXPAND);

	wxTextCtrl* layerTextCtrl = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER);
	Connect(layerTextCtrl->GetId(), wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler(SkeletonEditDialog::onLayerChange));
	m_editPanel = new SkeletonEditPanel(this, m_skeleton, skeletonList, layerTextCtrl);
	sizer->Add(m_editPanel, 5, wxEXPAND);

	wxBoxSizer* toolSizer = new wxBoxSizer(wxVERTICAL);
	wxStaticText* layerText = new wxStaticText(this, wxID_ANY, wxT("��(1-10) : "));
	toolSizer->Add(layerText);
	toolSizer->Add(layerTextCtrl);
	sizer->Add(toolSizer, 0);

	SetSizer(sizer);
}

void SkeletonEditDialog::onLayerChange(wxCommandEvent& event)
{
	wxVariant vx = event.GetString();
	m_editPanel->setSelectedBoneLayer(vx.GetInteger());
}