#include "StagePanel.h"
#include "Dataset/InterimData.h"
#include "Frame/Output/DesignerPage.h"
#include "Frame/Output/LuaPage.h"
#include "Frame/Output/CPlusPlusPage.h"
#include "Frame/Output/JavaPage.h"
#include "Frame/Output/XRCPage.h"
#include "Frame/Output/TextPage.h"

using namespace GAME_FRUITS;
using namespace GAME_FRUITS::VIEW;

BEGIN_EVENT_TABLE(StagePanel, wxPanel)
	EVT_NOTEBOOK_PAGE_CHANGING(wxID_ANY, StagePanel::onPageChanging)
	EVT_NOTEBOOK_PAGE_CHANGED(wxID_ANY, StagePanel::onPageChanged)
END_EVENT_TABLE()

StagePanel::StagePanel(wxWindow* parent)
	: wxPanel(parent)
{
	initLayout();
}

void StagePanel::getInterimData(InterimData& interim) const
{
	OUTPUT::DesignerPage* page = dynamic_cast<OUTPUT::DesignerPage*>(m_notebook->GetPage(0));
	assert(page);
	page->storeToInterimData(interim);
}

void StagePanel::initLayout()
{
	wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
	initTitle(sizer);
	initTabPages(sizer);
	SetSizer(sizer);
}

void StagePanel::initTitle(wxSizer* sizer)
{
	wxStaticText* title = new wxStaticText(this, wxID_ANY, wxT("Stage"));
	title->SetForegroundColour(*wxWHITE);
	title->SetBackgroundColour(*wxBLACK);
	sizer->Add(title, 0, wxEXPAND);
}

void StagePanel::initTabPages(wxSizer* sizer)
{
	m_notebook = new wxNotebook(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxNB_BOTTOM);
	OUTPUT::DesignerPage* designerPage = new OUTPUT::DesignerPage(m_notebook);
	m_notebook->AddPage(designerPage, wxT("Designer"));
	m_notebook->AddPage(new OUTPUT::LuaPage(m_notebook), wxT("Lua"));
	m_notebook->AddPage(new OUTPUT::CPlusPlusPage(m_notebook), wxT("C++"));
	m_notebook->AddPage(new OUTPUT::JavaPage(m_notebook), wxT("Java"));
	m_notebook->AddPage(new OUTPUT::XRCPage(m_notebook), wxT("XRC"));
	m_notebook->AddPage(new OUTPUT::TextPage(m_notebook), wxT("TEXT"));
	sizer->Add(m_notebook, 1, wxEXPAND);
}

void StagePanel::onPageChanging(wxNotebookEvent& event)
{
//	wxMessageBox("onPageChanging");
}

void StagePanel::onPageChanged(wxNotebookEvent& event)
{
	if (m_notebook->GetSelection() != 0)
	{
		OutputPageBase* src = dynamic_cast<OutputPageBase*>(m_notebook->GetPage(0));
		OutputPageBase* dst = dynamic_cast<OutputPageBase*>(m_notebook->GetCurrentPage());
		InterimData interim;
		src->storeToInterimData(interim);
		dst->loadFromInterimData(interim);
	}
}