#include "SymbolEditDialog.h"
#include "Dataset/Symbol.h"
#include "Dataset/Mesh.h"
#include "Edit/EditMeshNodeOP.h"
#include "Edit/EditPartSkeletonOP.h"
#include "Edit/AddPartSkeletonJointOP.h"
#include "Edit/EditWholeSkeletonJointOP.h"
#include "View/SymbolEditGLCanvas.h"

#include <wx/colordlg.h>
#include <wx/statline.h>
#include <wx/spinctrl.h>"
#include <wxGUI/wxGUI.h>

using namespace FRUITS_ANIMATOR;

SymbolEditDialog::SymbolEditDialog(wxWindow* parent, Symbol* symbol)
 	: wxDialog(parent, wxID_ANY, "Edit Symbol", wxDefaultPosition, wxSize(800, 600), wxCLOSE_BOX | wxCAPTION | wxMAXIMIZE_BOX)
{
	m_symbol = symbol;
	m_isEditSelect = true;
	initLayout();
	onChooseSelectWay(wxCommandEvent(0));
}

SymbolEditDialog::~SymbolEditDialog()
{
	delete m_editPanel;
}

void SymbolEditDialog::initLayout()
{
	wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
	buildToolBarSettings(sizer);
	buildEditPanel(sizer);
	buildToolBarEditors(sizer);
	SetSizer(sizer);
}

void SymbolEditDialog::buildToolBarSettings(wxSizer* topSizer)
{
	wxBoxSizer* toolSizer = new wxBoxSizer(wxVERTICAL);
	buildSettingsItems(toolSizer);
	toolSizer->AddSpacer(20);
	buildEditModeChoice(toolSizer);
	topSizer->Add(toolSizer, 0);
}

void SymbolEditDialog::buildEditPanel(wxSizer* topSizer)
{
	m_editPanel = new wxgui::EditPanel(this);
	m_editPanel->setCanvas(new SymbolEditGLCanvas(m_editPanel, m_symbol));
	m_editPanel->getCamera()->setScale(0.5f);
	topSizer->Add(m_editPanel, 1, wxEXPAND);
}

void SymbolEditDialog::buildToolBarEditors(wxSizer* topSizer)
{
	wxBoxSizer* toolSizer = new wxBoxSizer(wxVERTICAL);
	buildClipModeToolBar(toolSizer);
	buildMeshModeToolBar(toolSizer);
	buildPartSkeletonModeToolBar(toolSizer);
	buildWholeSkeletonModeToolBar(toolSizer);
	topSizer->Add(toolSizer, 0);

	m_clipModeSizer->Show(true);
	m_meshModeSizer->Show(false);
	m_partSkeletonModeSizer->Show(false);
	m_wholeSkeletonModeSizer->Show(false);
}

void SymbolEditDialog::buildSettingsItems(wxBoxSizer* toolSizer)
{
	wxStaticBox* settingBound = new wxStaticBox(this, wxID_ANY, wxT("����"));
	wxBoxSizer* settingSizer = new wxStaticBoxSizer(settingBound, wxVERTICAL);

	wxButton* btnName = new wxButton(this, wxID_ANY, wxT("����..."));
	Connect(btnName->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(SymbolEditDialog::onSetName));
	settingSizer->Add(btnName, 0);

	wxButton* btnSetColor = new wxButton(this, wxID_ANY, wxT("������ɫ..."));
	Connect(btnSetColor->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(SymbolEditDialog::onSetColor));
	settingSizer->Add(btnSetColor, 0);

	toolSizer->Add(settingSizer, 0);
}

void SymbolEditDialog::buildEditModeChoice(wxBoxSizer* toolSizer)
{
	wxArrayString choices;
	choices.Add(wxT("��Ƭ�ü�"));
	choices.Add(wxT("�������"));
	choices.Add(wxT("�ֲ�����"));
	choices.Add(wxT("�������"));
	m_editModeChoice = new wxRadioBox(this, wxID_ANY, wxT("�༭����"), wxDefaultPosition, wxDefaultSize, choices, 1, wxRA_SPECIFY_COLS);
	Connect(m_editModeChoice->GetId(), wxEVT_COMMAND_RADIOBOX_SELECTED, wxCommandEventHandler(SymbolEditDialog::onSetEditMode));
	Connect(m_editModeChoice->GetId(), wxEVT_UPDATE_UI, wxUpdateUIEventHandler(SymbolEditDialog::onUpdateSetEditMode));
	toolSizer->Add(m_editModeChoice, 0);
}

void SymbolEditDialog::buildClipModeToolBar(wxBoxSizer* toolSizer)
{
	m_clipModeSizer = new wxBoxSizer(wxVERTICAL);

	// edit
	wxArrayString editItems;
	editItems.Add(wxT("ѡ��"));
	editItems.Add(wxT("ȡ��"));
	wxRadioBox* editChoice = new wxRadioBox(this, wxID_ANY, wxT("�༭����"), wxDefaultPosition, wxDefaultSize, editItems, 1, wxRA_SPECIFY_COLS);
	Connect(editChoice->GetId(), wxEVT_COMMAND_RADIOBOX_SELECTED, wxCommandEventHandler(SymbolEditDialog::onChooseEditType));
	m_clipModeSizer->Add(editChoice, 0);
	m_clipModeSizer->AddSpacer(20);

	// choice
	wxArrayString choiceItems;
	choiceItems.Add(wxT("��ѡ"));
	choiceItems.Add(wxT("��ѡ"));
	choiceItems.Add(wxT("�����ѡ"));
	wxRadioBox* clipWayChoice = new wxRadioBox(this, wxID_ANY, wxT("ѡ��ʽ"), wxDefaultPosition, wxDefaultSize, choiceItems, 1, wxRA_SPECIFY_COLS);
	Connect(clipWayChoice->GetId(), wxEVT_COMMAND_RADIOBOX_SELECTED, wxCommandEventHandler(SymbolEditDialog::onChooseSelectWay));
	m_clipModeSizer->Add(clipWayChoice, 0);

	wxSizer* magicSizer = new wxBoxSizer(wxHORIZONTAL);
	m_magicMakerText = new wxStaticText(this, wxID_ANY, wxT("ħ����"));
	magicSizer->Add(m_magicMakerText, 0);
	m_magicMarkerDisSpin = new wxSpinCtrl(this, wxID_ANY, wxT("0"), wxDefaultPosition, wxSize(50, -1), wxSP_ARROW_KEYS, 0, 100, 0);
	Connect(m_magicMarkerDisSpin->GetId(), wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler(SymbolEditDialog::onSetMagicMarkerDis));
	magicSizer->Add(m_magicMarkerDisSpin, 0);
	m_clipModeSizer->Add(magicSizer, 0);

	m_clipModeSizer->AddSpacer(20);

	// view
	wxStaticBox* viewBound = new wxStaticBox(this, wxID_ANY, wxT("��ʾ"));
	wxBoxSizer* viewSizer = new wxStaticBoxSizer(viewBound, wxVERTICAL);

	wxCheckBox* pixelBoundCheck = new wxCheckBox(this, wxID_ANY, wxT("���ر߿�"));
	pixelBoundCheck->SetValue(true);
	Connect(pixelBoundCheck->GetId(), wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(SymbolEditDialog::onSetDisplayPixelBound));
	viewSizer->Add(pixelBoundCheck, 0);

	wxCheckBox* origSymbolCheck = new wxCheckBox(this, wxID_ANY, wxT("ԭʼԪ��"));
	origSymbolCheck->SetValue(true);
	Connect(origSymbolCheck->GetId(), wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(SymbolEditDialog::onSetDisplayOriginalSymbol));
	viewSizer->Add(origSymbolCheck, 0);

	m_clipModeSizer->Add(viewSizer, 0);
	m_clipModeSizer->AddSpacer(20);

	// buttons
	wxButton* btnClear = new wxButton(this, wxID_ANY, wxT("���"));
	Connect(btnClear->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(SymbolEditDialog::onClearSelectedPixels));
	m_clipModeSizer->Add(btnClear, 0);

	wxButton* btnCreate = new wxButton(this, wxID_ANY, wxT("����"));
	Connect(btnCreate->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(SymbolEditDialog::onCreateSelectedPixels));
	m_clipModeSizer->Add(btnCreate, 0);

	toolSizer->Add(m_clipModeSizer, 0);
}

void SymbolEditDialog::buildMeshModeToolBar(wxBoxSizer* toolSizer)
{
	m_meshModeSizer = new wxBoxSizer(wxVERTICAL);

	// buttons
	wxButton* btnClear = new wxButton(this, wxID_ANY, wxT("���"));
	Connect(btnClear->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(SymbolEditDialog::onClearMeshNodes));
	m_meshModeSizer->Add(btnClear, 0);

	toolSizer->Add(m_meshModeSizer, 0);
}

void SymbolEditDialog::buildPartSkeletonModeToolBar(wxBoxSizer* toolSizer)
{
	m_partSkeletonModeSizer = new wxBoxSizer(wxVERTICAL);

	// edit choice
	wxArrayString choices;
	choices.Add(wxT("���"));
	choices.Add(wxT("�༭"));
	wxRadioBox* editModeChoice = new wxRadioBox(this, wxID_ANY, wxT("��������"), wxDefaultPosition, wxDefaultSize, choices, 1, wxRA_SPECIFY_COLS);
	Connect(editModeChoice->GetId(), wxEVT_COMMAND_RADIOBOX_SELECTED, wxCommandEventHandler(SymbolEditDialog::onSetSkeletonEditMode));
	m_partSkeletonModeSizer->Add(editModeChoice, 0);

	toolSizer->Add(m_partSkeletonModeSizer, 0);
}

void SymbolEditDialog::buildWholeSkeletonModeToolBar(wxBoxSizer* toolSizer)
{
	m_wholeSkeletonModeSizer = new wxBoxSizer(wxVERTICAL);

	toolSizer->Add(m_wholeSkeletonModeSizer, 0);
}

void SymbolEditDialog::onSetName(wxCommandEvent& event)
{
	wxPoint pos(GetScreenPosition() + wxPoint(100, 200));
	wxgui::SetValueDialog dlg(this, wxT("Set symbol's name"), m_symbol->getName(), pos);
	if (dlg.ShowModal() == wxID_OK)
	{
		m_symbol->setName(dlg.getText().ToStdString());
		m_parent->Refresh();
	}
}

void SymbolEditDialog::onSetColor(wxCommandEvent& event)
{
	wxColourDialog dlg(this);
	dlg.SetTitle(("Please choose the background colour"));
	if (dlg.ShowModal() == wxID_OK)
	{
		const wxColour& color = dlg.GetColourData().GetColour();
		SymbolEditGLCanvas* canvas = static_cast<SymbolEditGLCanvas*>(m_editPanel->getCanvas());
		canvas->setBgColor(f2Colorf(
			color.Red() / 255.0f,
			color.Green() / 255.0f,
			color.Blue() / 255.0f,
			color.Alpha() / 255.0f
			));
		m_editPanel->Refresh();
	}
	m_editPanel->SetFocus();
}

void SymbolEditDialog::onSetEditMode(wxCommandEvent& event)
{
	SymbolEditGLCanvas* canvas = static_cast<SymbolEditGLCanvas*>(m_editPanel->getCanvas());
	assert(canvas);
	switch (event.GetInt())
	{
	case 0:
		canvas->setDrawMode(SymbolEditGLCanvas::DrawInPixels);
		break;
	case 1:
		canvas->setDrawMode(SymbolEditGLCanvas::DrawInTexture);
		break;
	case 2:
		canvas->setDrawMode(SymbolEditGLCanvas::DrawInTexture);
		break;
	case 3:
		canvas->setDrawMode(SymbolEditGLCanvas::DrawInTexture);
		break;
	}

	m_editPanel->Refresh();
}

void SymbolEditDialog::onUpdateSetEditMode(wxUpdateUIEvent& event)
{
	static int state = -1;
	if (m_editModeChoice->GetSelection() == state)
		return;

	switch (m_editModeChoice->GetSelection())
	{
	case 0:
		onChooseSelectWay(wxCommandEvent(0));
		m_editPanel->Refresh();

		m_clipModeSizer->Show(true);
		m_meshModeSizer->Show(false);
		m_partSkeletonModeSizer->Show(false);
		m_wholeSkeletonModeSizer->Show(false);
		Layout();
		state = 0;

		break;
	case 1:
		{
			wxgui::AbstractEditOP* op = new EditMeshNodeOP(m_editPanel, m_symbol->createMesh());
			m_editPanel->setEditOP(op);
			op->release();
		}
		m_editPanel->Refresh();

		m_clipModeSizer->Show(false);
		m_meshModeSizer->Show(true);
		m_partSkeletonModeSizer->Show(false);
		m_wholeSkeletonModeSizer->Show(false);
		Layout();
		state = 1;

		break;
	case 2:
		{
			wxgui::AbstractEditOP* op = new AddPartSkeletonJointOP(m_editPanel, m_symbol->createSkeleton());
			m_editPanel->setEditOP(op);
			op->release();
		}
		m_editPanel->Refresh();

		m_clipModeSizer->Show(false);
		m_meshModeSizer->Show(false);
		m_partSkeletonModeSizer->Show(true);
		m_wholeSkeletonModeSizer->Show(false);
		Layout();
		state = 2;

		break;
	case 3:
		{
			wxgui::AbstractEditOP* op = new EditWholeSkeletonJointOP(m_editPanel, m_symbol->createSkeletonBody());
			m_editPanel->setEditOP(op);
			op->release();
		}
		m_editPanel->Refresh();

		m_clipModeSizer->Show(false);
		m_meshModeSizer->Show(false);
		m_partSkeletonModeSizer->Show(false);
		m_wholeSkeletonModeSizer->Show(true);
		Layout();
		state = 3;

		break;
	}

	m_editPanel->SetFocus();
}

void SymbolEditDialog::onChooseSelectWay(wxCommandEvent& event)
{
	SymbolEditGLCanvas* canvas = static_cast<SymbolEditGLCanvas*>(m_editPanel->getCanvas());
	assert(canvas);

	wxgui::AbstractEditOP* op = new wxgui::SelectPixelsOP(
		m_editPanel, 
		canvas->getRawPixels(), 
		wxgui::SelectPixelsOP::e_Mode(event.GetInt()), 
		canvas->getSelectedPixels(),
		m_isEditSelect,
		m_magicMarkerDisSpin->GetValue()
		);
	m_editPanel->setEditOP(op);
	op->release();

	if (event.GetInt() == 1) 
	{
		m_magicMakerText->Enable();
		m_magicMarkerDisSpin->Enable();
	}
	else
	{
		m_magicMakerText->Disable();
		m_magicMarkerDisSpin->Disable();
	}

	m_editPanel->Refresh();
	m_editPanel->SetFocus();
}

void SymbolEditDialog::onChooseEditType(wxCommandEvent& event)
{
	m_isEditSelect = (event.GetInt() == 0);
	wxgui::SelectPixelsOP* op = dynamic_cast<wxgui::SelectPixelsOP*>(m_editPanel->getEditOP());
	if (op) 
		op->setEditType(m_isEditSelect);
	m_editPanel->SetFocus();
}

void SymbolEditDialog::onSetMagicMarkerDis(wxSpinEvent& event)
{
	m_isEditSelect = (event.GetInt() == 0);
	wxgui::SelectPixelsOP* op = dynamic_cast<wxgui::SelectPixelsOP*>(m_editPanel->getEditOP());
	if (op) 
		op->setMagicMarkerDis(m_magicMarkerDisSpin->GetValue());
	m_editPanel->SetFocus();
}

void SymbolEditDialog::onSetDisplayPixelBound(wxCommandEvent& event)
{
	SymbolEditGLCanvas* canvas = static_cast<SymbolEditGLCanvas*>(m_editPanel->getCanvas());
	assert(canvas);
	SymbolEditGLCanvas::RenderSetting& setting = canvas->getRenderSetting();
	setting.drawPixelBound = event.IsChecked();

	m_editPanel->Refresh();
	m_editPanel->SetFocus();
}

void SymbolEditDialog::onSetDisplayOriginalSymbol(wxCommandEvent& event)
{
	SymbolEditGLCanvas* canvas = static_cast<SymbolEditGLCanvas*>(m_editPanel->getCanvas());
	assert(canvas);
	SymbolEditGLCanvas::RenderSetting& setting = canvas->getRenderSetting();
	setting.drawOriginalSymbol = event.IsChecked();

	m_editPanel->Refresh();
	m_editPanel->SetFocus();
}

void SymbolEditDialog::onClearSelectedPixels(wxCommandEvent& event)
{
	SymbolEditGLCanvas* canvas = static_cast<SymbolEditGLCanvas*>(m_editPanel->getCanvas());
	assert(canvas);
	wxgui::RawPixels::PixelBuf& buf = canvas->getSelectedPixels();
	for_each(buf.begin(), buf.end(), DeletePointerFunctor<wxgui::RawPixels::PixelsPos>());
	buf.clear();

	m_editPanel->Refresh();
	m_editPanel->SetFocus();
}

void SymbolEditDialog::onCreateSelectedPixels(wxCommandEvent& event)
{
 	SymbolEditGLCanvas* canvas = static_cast<SymbolEditGLCanvas*>(m_editPanel->getCanvas());
 	assert(canvas);
	m_symbol->replaceBySelectedPixels(canvas->getSelectedPixels());

	m_editPanel->Refresh();
	m_editPanel->SetFocus();
}

void SymbolEditDialog::onClearMeshNodes(wxCommandEvent& event)
{
	m_symbol->getMesh()->clear();

	m_editPanel->Refresh();
	m_editPanel->SetFocus();
}

void SymbolEditDialog::onSetSkeletonEditMode(wxCommandEvent& event)
{
	switch (event.GetInt())
	{
	case 0:
		{
			wxgui::AbstractEditOP* op = new AddPartSkeletonJointOP(m_editPanel, m_symbol->getSkeleton());
			m_editPanel->setEditOP(op);
			op->release();
		}
		m_editPanel->Refresh();
		m_editPanel->SetFocus();
		break;
	case 1:
		{
			wxgui::AbstractEditOP* op = new EditPartSkeletonOP(m_editPanel, m_symbol->getSkeleton());
			m_editPanel->setEditOP(op);
			op->release();
		}
		m_editPanel->Refresh();
		m_editPanel->SetFocus();
		break;
	}
}