#include "ImagesPage.h"

#include <wxGUI/wxGUI.h>
#include <wx/listctrl.h>

using namespace GAME_FRUITS::VIEW::LIBRARY;

ImagesPage::ImagesPage(wxWindow* parent)
	: LibraryPageBase(parent)
{
	Connect(m_add->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(ImagesPage::onAddImage));
	Connect(m_del->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(ImagesPage::onDelImage));

	m_imageList = new wxImageList(IMG_LIST_GRID_EDGE, IMG_LIST_GRID_EDGE);
	m_listCtrl->SetImageList(m_imageList, wxIMAGE_LIST_NORMAL);

	SetDropTarget(new wxgui::DragTargetNull);
	Connect(m_listCtrl->GetId(), wxEVT_COMMAND_LIST_BEGIN_DRAG, wxListEventHandler(ImagesPage::onDragInit));

	m_listCtrl->SetSingleStyle(wxLC_SINGLE_SEL | wxLC_AUTOARRANGE, true);
}

wxString ImagesPage::getImagePath(const wxString& imgName) const
{
	long item = -1;
	while (true)
	{
		item = m_listCtrl->GetNextItem(item);
		if (item == -1)
			break;

		wxListItem entry;
		entry.SetId(item);
		entry.SetMask(wxLIST_MASK_TEXT);
		m_listCtrl->GetItem(entry);

		if (entry.GetText() == imgName) break;
	}

	if (item != -1)
	{
		wxString* path = (wxString*) m_listCtrl->GetItemData(item);
		return *path;
	}
	else
		return "";	
}

void ImagesPage::onAddImage(wxCommandEvent& event)
{
	wxFileDialog dialog(this, wxT("Please choose a image"), wxEmptyString, wxEmptyString, wxT("*.png;*.jpg"), wxFD_OPEN);
	if (dialog.ShowModal() == wxID_OK)
	{
		wxString path(dialog.GetPath());
		wxImage image;
		image.LoadFile(path);

		wxBitmap* bitmap = new wxBitmap(image);
		const int w = bitmap->GetWidth(),
			h = bitmap->GetHeight();
		wxImage tmp = bitmap->ConvertToImage();

		int nw, nh;
		if (w > h)
		{
			nh = IMG_LIST_GRID_EDGE * h / w;
			nw = IMG_LIST_GRID_EDGE;
		}
		else
		{
			nw = IMG_LIST_GRID_EDGE * w / h;
			nh = IMG_LIST_GRID_EDGE;
		}
		*bitmap = wxBitmap(tmp.Scale(nw, nh));

		m_imageList->Add(*bitmap, *wxRED);

		int itemSize = m_listCtrl->GetItemCount();

		wxListItem *item = new wxListItem;
		item->SetText(dialog.GetFilename());
		item->SetImage(itemSize);
		item->SetData(new wxString(path));

		m_listCtrl->InsertItem(*item);

		updateListeners();
	}
}

void ImagesPage::onDelImage(wxCommandEvent& event)
{
	long item = -1;
	while (true)
	{
		item = m_listCtrl->GetNextItem(item, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
		if (item == -1)
			break;

// 		wxListItem entry;
// 		entry.SetId(item);
// 		entry.SetMask(wxLIST_MASK_IMAGE);
// 		m_listCtrl->GetItem(entry);
// 		long imgId = entry.GetImage();

		m_listCtrl->DeleteItem(item);
//		m_imageList->Remove(imgId);


// 		// debug
// 		wxListItem entry;
// 		entry.SetId(0);
// 		entry.SetState(wxLIST_STATE_FOCUSED | wxLIST_STATE_SELECTED);
// 		m_listCtrl->SetItem(entry);

		updateListeners();
	}
}

void ImagesPage::onDragInit(wxListEvent& event)
{
	wxString* path = (wxString*) m_listCtrl->GetItemData(event.GetIndex());

	wxTextDataObject tdo(*path);
	wxDropSource ds(tdo, m_listCtrl);
	ds.DoDragDrop(wxDrag_CopyOnly);
}