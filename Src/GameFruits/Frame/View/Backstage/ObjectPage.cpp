#include "ObjectPage.h"
#include "DstPanel.h"
#include "Frame/Regulars/ChangeImage.h"
#include "Frame/Regulars/MousePress.h"
#include "Dataset/Object.h"
#include "Dataset/DataConnection.h"

using namespace GAME_FRUITS;
using namespace GAME_FRUITS::VIEW::BACKSTAGE;

ObjectPage::ObjectPage(wxNotebook* parent, Object* object)
	: DstPageBase(parent)
{
	m_parent = parent;
	m_object = object;

	buildPropertyPage();
	initData(object, true);

	m_regularPage->SetDropTarget(new DragTarget(m_regularPage, m_object));
}

void ObjectPage::initData(Object* object, bool hasRegular)
{
	m_object = object;

	m_name->SetValue(m_object->getName());

	int x, y;
	m_object->getPosition(x, y);
	m_x->SetValue(wxVariant(x));
	m_y->SetValue(wxVariant(y));

	int width, height;
	m_object->getSize(width, height);
	m_width->SetValue(wxVariant(width).GetString());
	m_height->SetValue(wxVariant(height).GetString());

	if (hasRegular)
	{
		const std::vector<RegularListItem*>& regulars = object->getAllRegulars();
		for (size_t i = 0, n = regulars.size(); i < n; ++i)
			regulars[i]->createPanel(m_regularPage);
	}
}

void ObjectPage::buildPropertyPage()
{
	wxSizer* topSizer = m_propertyPage->GetSizer();
	buildNameItem(topSizer);
	buildPositionItem(topSizer);
	buildSizeItem(topSizer);
}

void ObjectPage::buildNameItem(wxSizer* topSizer)
{
	wxBoxSizer* nameSizer = new wxBoxSizer(wxHORIZONTAL);
	nameSizer->Add(new wxStaticText(m_propertyPage, wxID_ANY, wxT("NAME")), 0, wxALIGN_LEFT);
	nameSizer->AddStretchSpacer(2);
	m_name = new wxTextCtrl(m_propertyPage, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER);
	nameSizer->Add(m_name, 5, wxALIGN_RIGHT);
	nameSizer->AddStretchSpacer(1);
	topSizer->Add(nameSizer, 0, wxEXPAND);

	Connect(m_name->GetId(), wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler(ObjectPage::onNameChange));
}

void ObjectPage::buildPositionItem(wxSizer* topSizer)
{
	topSizer->Add(new wxStaticText(m_propertyPage, wxID_ANY, wxT("POSITION")), 0, wxALIGN_LEFT);

	wxBoxSizer* xSizer = new wxBoxSizer(wxHORIZONTAL);
	xSizer->AddStretchSpacer(1);
	xSizer->Add(new wxStaticText(m_propertyPage, wxID_ANY, wxT("x")), 0, wxALIGN_LEFT);
	xSizer->AddStretchSpacer(1);
	m_x = new wxTextCtrl(m_propertyPage, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER);
	xSizer->Add(m_x, 5, wxALIGN_RIGHT);
	xSizer->AddStretchSpacer(1);
	topSizer->Add(xSizer, 0, wxEXPAND);

	wxBoxSizer* ySizer = new wxBoxSizer(wxHORIZONTAL);
	ySizer->AddStretchSpacer(1);
	ySizer->Add(new wxStaticText(m_propertyPage, wxID_ANY, wxT("y")), 0, wxALIGN_LEFT);
	ySizer->AddStretchSpacer(1);
	m_y = new wxTextCtrl(m_propertyPage, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER);
	ySizer->Add(m_y, 5, wxALIGN_RIGHT);
	ySizer->AddStretchSpacer(1);
	topSizer->Add(ySizer, 0, wxEXPAND);

	Connect(m_x->GetId(), wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler(ObjectPage::onXChange));
	Connect(m_y->GetId(), wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler(ObjectPage::onYChange));
}

void ObjectPage::buildSizeItem(wxSizer* topSizer)
{
	topSizer->Add(new wxStaticText(m_propertyPage, wxID_ANY, wxT("SIZE")), 0, wxALIGN_LEFT);

	wxBoxSizer* widthSizer = new wxBoxSizer(wxHORIZONTAL);
	widthSizer->AddStretchSpacer(1);
	widthSizer->Add(new wxStaticText(m_propertyPage, wxID_ANY, wxT("width")), 0, wxALIGN_LEFT);
	widthSizer->AddStretchSpacer(1);
	m_width = new wxTextCtrl(m_propertyPage, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER);
	widthSizer->Add(m_width, 5, wxALIGN_RIGHT);
	widthSizer->AddStretchSpacer(1);
	topSizer->Add(widthSizer, 0, wxEXPAND);

	wxBoxSizer* heightSizer = new wxBoxSizer(wxHORIZONTAL);
	heightSizer->AddStretchSpacer(1);
	heightSizer->Add(new wxStaticText(m_propertyPage, wxID_ANY, wxT("height")), 0, wxALIGN_LEFT);
	heightSizer->AddStretchSpacer(1);
	m_height = new wxTextCtrl(m_propertyPage, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER);
	heightSizer->Add(m_height, 5, wxALIGN_RIGHT);
	heightSizer->AddStretchSpacer(1);
	topSizer->Add(heightSizer, 0, wxEXPAND);

	Connect(m_width->GetId(), wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler(ObjectPage::onWidthChange));
	Connect(m_height->GetId(), wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler(ObjectPage::onHeightChange));
}

void ObjectPage::onNameChange(wxCommandEvent& event)
{
	m_object->setName(event.GetString());
	m_parent->SetPageText(2, m_object->getName());
}

void ObjectPage::onXChange(wxCommandEvent& event)
{
	int x, y;
	m_object->getPosition(x, y);
	wxVariant vx = event.GetString();
	m_object->setPosition(vx.GetInteger(), y);
	DataConnection::m_stage->Refresh();
}

void ObjectPage::onYChange(wxCommandEvent& event)
{
	int x, y;
	m_object->getPosition(x, y);
	wxVariant vy = event.GetString();
	m_object->setPosition(x, vy.GetInteger());
	DataConnection::m_stage->Refresh();
}

void ObjectPage::onWidthChange(wxCommandEvent& event)
{
 	int width, height;
 	m_object->getSize(width, height);
 	wxVariant vw = event.GetString();
	m_object->setSize(vw.GetInteger(), height);
	DataConnection::m_stage->Refresh();
}

void ObjectPage::onHeightChange(wxCommandEvent& event)
{
	int width, height;
	m_object->getSize(width, height);
	wxVariant vw = event.GetString();
	m_object->setSize(width, vw.GetInteger());
	DataConnection::m_stage->Refresh();
}

//////////////////////////////////////////////////////////////////////////
// class ObjectPage::DragTarget
//////////////////////////////////////////////////////////////////////////

ObjectPage::DragTarget::DragTarget(wxWindow* parent, Object* object)
	: DragRegularTarget(parent)
{
	m_object = object;
}

bool ObjectPage::DragTarget::OnDropText(wxCoord x, wxCoord y, const wxString& data)
{
	RegularListItem* regular = createRegular(data);
	if (regular)
	{
		regular->createPanel(m_parent);
		m_object->addRegular(regular);
	}
	return true;
}