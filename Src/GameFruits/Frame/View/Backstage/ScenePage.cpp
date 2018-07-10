#include "ScenePage.h"
#include "Dataset/Scene.h"
#include "Dataset/DataConnection.h"
#include "Frame/View/Backstage/DstPanel.h"
#include "Frame/View/Library/ScenePage.h"

#include <wx/colordlg.h>

using namespace GAME_FRUITS;
using namespace GAME_FRUITS::VIEW::BACKSTAGE;

ScenePage::ScenePage(wxNotebook* parent, Scene* scene)
	: DstPageBase(parent)
{
	m_parent = parent;
	m_scene = scene;

	buildPropertyPage();
	initData(scene);
	setColorButtonColor();
}

void ScenePage::initData(Scene* scene)
{
	m_scene = scene;
	m_name->SetValue(m_scene->getName());
	setColorButtonColor();
}

void ScenePage::buildPropertyPage()
{
	wxSizer* topSizer = m_propertyPage->GetSizer();
	buildNameItem(topSizer);
	topSizer->AddSpacer(20);
	buildColorItem(topSizer);
}

void ScenePage::buildNameItem(wxSizer* topSizer)
{
	wxBoxSizer* nameSizer = new wxBoxSizer(wxHORIZONTAL);
	nameSizer->Add(new wxStaticText(m_propertyPage, wxID_ANY, wxT("NAME")), 0, wxALIGN_LEFT);
	nameSizer->AddStretchSpacer(2);
	m_name = new wxTextCtrl(m_propertyPage, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER);
	nameSizer->Add(m_name, 5, wxALIGN_RIGHT);
	nameSizer->AddStretchSpacer(1);
	topSizer->Add(nameSizer, 0, wxEXPAND);

	Connect(m_name->GetId(), wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler(ScenePage::onNameChange));
}

void ScenePage::buildColorItem(wxSizer* topSizer)
{
	wxBoxSizer* colorSizer = new wxBoxSizer(wxHORIZONTAL);
	colorSizer->Add(new wxStaticText(m_propertyPage, wxID_ANY, wxT("Color")), 0, wxALIGN_LEFT);
	colorSizer->AddStretchSpacer(2);
	m_setColor = new wxButton(m_propertyPage, wxID_ANY);
	colorSizer->Add(m_setColor, 5, wxALIGN_RIGHT);
	colorSizer->AddStretchSpacer(1);
	topSizer->Add(colorSizer, 0, wxEXPAND);

	Connect(m_setColor->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(ScenePage::onSetColor));
}

void ScenePage::setColorButtonColor()
{
	const wxColour& color = m_scene->getColor();
	wxImage img(m_setColor->GetSize().GetWidth(), m_setColor->GetSize().GetHeight());
	img.SetRGB(wxRect(m_setColor->GetSize()), color.Red(), color.Green(), color.Blue());
	wxBitmap bitmap(img);
	m_setColor->SetBitmap(bitmap);
}

void ScenePage::onNameChange(wxCommandEvent& event)
{
	wxString from = m_scene->getName();

	m_scene->setName(event.GetString());
	m_parent->SetPageText(1, m_scene->getName());
	LIBRARY::ScenePage* page = dynamic_cast<LIBRARY::ScenePage*>(DataConnection::m_libraryNotebook->GetPage(1));
	assert(page);
	page->setName(from, event.GetString());
}

void ScenePage::onSetColor(wxCommandEvent& event)
{
	wxColourDialog dialog(this);
	dialog.SetTitle(("Please choose the background colour"));
	if (dialog.ShowModal() == wxID_OK)
	{
		const wxColour& color = dialog.GetColourData().GetColour();
		DataConnection::m_currScene->setColor(color);
		setColorButtonColor();
		DataConnection::m_stage->Refresh();

		LIBRARY::ScenePage* page = dynamic_cast<LIBRARY::ScenePage*>(DataConnection::m_libraryNotebook->GetPage(1));
		assert(page);
		page->updateThumbnail(*DataConnection::m_currScene);
	}
}