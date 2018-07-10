#include "ChangeScene.h"
#include "Dataset/DataConnection.h"
#include "Frame/View/Library/LibraryPageBase.h"
#include <wx/notebook.h>

using namespace GAME_FRUITS;
using namespace GAME_FRUITS::REGULAR;

ChangeScene::ChangeScene()
	: RegularListItem(wxT("Change Scene"))
{
	m_selectList = NULL;
	SetText(m_name);
}

Scene* ChangeScene::getSelectedScene() const
{
	int index = m_selectList->GetSelection();
	wxString name = m_selectList->GetString(index);
	return DataConnection::m_game.queryScene(name);
}

wxSizer* ChangeScene::createExtend(wxWindow* extend)
{
	wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
	sizer->Add(createChooseListItem(extend));
	return sizer;
}

wxSizer* ChangeScene::createChooseListItem(wxWindow* extend)
{
	wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);

 	sizer->Add(new wxStaticText(extend, wxID_ANY, wxT("Change Scene to ")));
 
 	m_selectList = new wxChoice(extend, wxID_ANY);
 
 	VIEW::LibraryPageBase* page = dynamic_cast<VIEW::LibraryPageBase*>(DataConnection::m_libraryNotebook->GetPage(1));
 	assert(page);
	page->registerListener(m_selectList);

	sizer->Add(m_selectList, 0, wxALIGN_LEFT);
	return sizer;
}