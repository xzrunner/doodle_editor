#include "PreviewDialog.h"
#include "PreviewGLCanvas.h"

using namespace FRUITS_ANIMATOR;

PreviewDialog::PreviewDialog(wxWindow* parent, LayersMgr* layers, LibraryPanel* library, int fps/* = 24*/)
 	: wxDialog(parent, wxID_ANY, "Preview", wxDefaultPosition, wxSize(800, 600), wxCLOSE_BOX | wxCAPTION)
{
	initLayout(layers, library, fps);
}

PreviewDialog::~PreviewDialog()
{
	delete m_editPanel;
}

void PreviewDialog::initLayout(LayersMgr* layers, LibraryPanel* library, int fps)
{
	wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
	buildToolBar(sizer);
	buildEditPanel(sizer, layers, library, fps);
	SetSizer(sizer);
}

void PreviewDialog::buildToolBar(wxSizer* topSizer)
{
	wxBoxSizer* toolSizer = new wxBoxSizer(wxVERTICAL);

	wxCheckBox* circulateCheck = new wxCheckBox(this, wxID_ANY, wxT("Ñ­»·"));
	circulateCheck->SetValue(true);
	Connect(circulateCheck->GetId(), wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(PreviewDialog::onSetCirculate));
	toolSizer->Add(circulateCheck, 0);

	wxCheckBox* stopCheck = new wxCheckBox(this, wxID_ANY, wxT("ÔÝÍ£"));
	stopCheck->SetValue(false);
	Connect(stopCheck->GetId(), wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(PreviewDialog::onSetStop));
	toolSizer->Add(stopCheck, 0);

	topSizer->Add(toolSizer, 0);
}

void PreviewDialog::buildEditPanel(wxSizer* topSizer, LayersMgr* layers, LibraryPanel* library, int fps)
{
	m_editPanel = new wxgui::EditPanel(this);
	m_editPanel->setEditOP(new wxgui::ZoomViewOP(m_editPanel, false));
	m_editPanel->setCanvas(new PreviewGLCanvas(m_editPanel, layers, library, fps));
	topSizer->Add(m_editPanel, 1, wxEXPAND);
}

void PreviewDialog::onSetCirculate(wxCommandEvent& event)
{
	PreviewGLCanvas* canvas = static_cast<PreviewGLCanvas*>(m_editPanel->getCanvas());
	assert(canvas);
	PreviewGLCanvas::PlaySetting& setting = canvas->getPlaySetting();
	setting.isCirculate = event.IsChecked();

	m_editPanel->Refresh();
	m_editPanel->SetFocus();
}

void PreviewDialog::onSetStop(wxCommandEvent& event)
{
	PreviewGLCanvas* canvas = static_cast<PreviewGLCanvas*>(m_editPanel->getCanvas());
	assert(canvas);
	PreviewGLCanvas::PlaySetting& setting = canvas->getPlaySetting();
	setting.isStop = event.IsChecked();

	m_editPanel->Refresh();
	m_editPanel->SetFocus();
}