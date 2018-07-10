#include "LibraryTemplatePage.h"
#include "LibraryTemplateList.h"
#include "LibraryTemplateItem.h"
#include "TEDialog.h"

#include "TETypes.h"

using namespace deditor::motox;

LibraryTemplatePage::LibraryTemplatePage(wxWindow* parent)
	: ILibraryPage(parent, wxT("模板"))
	, m_editPanel(NULL)
{
	m_list = new LibraryTemplateList(this);
	initLayout();
}

bool LibraryTemplatePage::isHandleSymbol(wxgui::ISymbol* symbol) const
{
	return dynamic_cast<LibraryTemplateItem*>(symbol) != NULL;
}

void LibraryTemplatePage::registerContext(wxgui::PropertySettingPanel* propertyPanel,
										  wxgui::EditPanel* editPanel) 
{
	m_propertyPanel = propertyPanel;
	m_editPanel = editPanel;
	static_cast<LibraryTemplateList*>(m_list)->registerContext(propertyPanel, editPanel);
}

void LibraryTemplatePage::initLayout(bool draggable /*= true*/)
{
	wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
	{
		wxBoxSizer* btnSizer = new wxBoxSizer(wxHORIZONTAL);

 		wxButton* btnNew = new wxButton(this, wxID_ANY, "new", wxDefaultPosition, wxSize(40, 20));
 		Connect(btnNew->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(LibraryTemplatePage::onNewBtnPress));
 		btnSizer->Add(btnNew, 0, wxRIGHT, 10);

		initButtons(btnSizer);

		sizer->Add(btnSizer, 0, wxALIGN_RIGHT);
	}
	{
		sizer->Add(m_list, 1, wxEXPAND);
	}
	SetSizer(sizer);
}

void LibraryTemplatePage::onAddPress(wxCommandEvent& event)
{
	wxString filter = wxT("*_") + TEMPLATE_FILE_TAG + wxT(".txt");
	wxFileDialog dlg(this, wxT("导入模板文件"), wxEmptyString, 
		wxEmptyString, filter, wxFD_OPEN | wxFD_MULTIPLE);
	if (dlg.ShowModal() == wxID_OK)
	{
		wxArrayString filenames;
		dlg.GetPaths(filenames);
		for (size_t i = 0, n = filenames.size(); i < n; ++i)
		{
			LibraryTemplateItem* item = new LibraryTemplateItem;
			item->loadFromFile(filenames[i]);
			m_list->insert(item);
		}
	}
}

void LibraryTemplatePage::onNewBtnPress(wxCommandEvent& event)
{
	LibraryTemplateItem* item = new LibraryTemplateItem();
	m_list->insert(item);

	TEDialog dlg(this, item, m_propertyPanel);
	dlg.ShowModal();
	if (m_editPanel) 
		m_editPanel->resetCanvas();
}