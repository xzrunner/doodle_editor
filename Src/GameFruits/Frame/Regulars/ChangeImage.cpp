#include "ChangeImage.h"
#include "Dataset/DataConnection.h"
#include "Frame/View/Library/LibraryPageBase.h"
#include "Frame/View/Library/ImagesPage.h"
#include <wx/notebook.h>

using namespace GAME_FRUITS;
using namespace GAME_FRUITS::REGULAR;

ChangeImage::ChangeImage()
	: RegularListItem(wxT("Change Image"))
{
	SetText(m_name);
}

wxString ChangeImage::getImagePath() const
{
	int index = m_selectList->GetSelection();
	wxString name = m_selectList->GetString(index);

	VIEW::LIBRARY::ImagesPage* page = dynamic_cast<VIEW::LIBRARY::ImagesPage*>(DataConnection::m_libraryNotebook->GetPage(4));
	assert(page);
	wxString path = page->getImagePath(name);
	assert(path != "");

	return path;
}

wxSizer* ChangeImage::createExtend(wxWindow* extend)
{
	wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
	sizer->Add(createChooseListItem(extend));
	return sizer;	
}

wxSizer* ChangeImage::createChooseListItem(wxWindow* extend)
{
	wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);

	sizer->Add(new wxStaticText(extend, wxID_ANY, wxT("Change Image to ")));

	m_selectList = new wxChoice(extend, wxID_ANY);

	VIEW::LibraryPageBase* page = dynamic_cast<VIEW::LibraryPageBase*>(DataConnection::m_libraryNotebook->GetPage(4));
	assert(page);
	page->registerListener(m_selectList);

	sizer->Add(m_selectList, 0, wxALIGN_LEFT);
	return sizer;
}