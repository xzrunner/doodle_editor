#include "VerticalImageList.h"
#include "ListItem.h"

#include <wxGUI/wxGUI.h>

using namespace wxgui;

VerticalImageList::VerticalImageList(wxWindow* parent, const wxString& name/* = wxEmptyString*/,
									 bool draggable /*= true*/)
	: wxVListBox(parent)
	, m_name(name)
{
	SetBackgroundColour(wxColour(229, 229, 229));

	Connect(GetId(), wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler(VerticalImageList::onListSelected));
	Connect(GetId(), wxEVT_COMMAND_LISTBOX_DOUBLECLICKED, wxCommandEventHandler(VerticalImageList::onListDoubleClicked));

	if (draggable)
	{
		SetDropTarget(new DragTargetNull);
		Connect(GetId(), wxEVT_MOTION, wxMouseEventHandler(VerticalImageList::onDragInit));
	}
}

VerticalImageList::~VerticalImageList()
{
	clear();
}

void VerticalImageList::traverse(IVisitor& visitor) const
{
	std::vector<ListItem*>::const_iterator itr = m_items.begin();
	for ( ; itr != m_items.end(); ++itr)
	{
		bool hasNext;
		visitor.visit(*itr, hasNext);
		if (!hasNext) break;
	}
}

void VerticalImageList::clear()
{
//	for_each(m_items.begin(), m_items.end(), DeletePointerFunctor<ListItem>());
	m_items.clear();
	SetItemCount(0);
	Refresh();
}

void VerticalImageList::insert(ListItem* item)
{
	m_items.push_back(item);
	SetItemCount(m_items.size());
	SetSelection(m_items.size() - 1);
	Refresh();
}

void VerticalImageList::remove()
{
	int index = GetSelection();
	if (index >= 0 && index < m_items.size())
	{
//		delete m_items[index];
		m_items.erase(m_items.begin() + index);
		onListSelected(wxCommandEvent(GetSelection()));
		SetItemCount(m_items.size());
		Refresh();
	}
}

void VerticalImageList::OnDrawItem(wxDC& dc, const wxRect& rect, size_t n) const
{
	int y = rect.y + SPACE_UP;

	const Bitmap* bmp = m_items[n]->getBitmap();
	if (bmp)
	{
		const wxBitmap* wxBmp = bmp->getBitmap();
		int x = wxBmp->GetWidth() > rect.width ? 0 : (rect.width - wxBmp->GetWidth()) * 0.5f;
		dc.DrawBitmap(*wxBmp, x, y);
		y += wxBmp->GetHeight();
	}

	wxString name = m_items[n]->getName();
	wxSize size = dc.GetTextExtent(name);
	dc.DrawText(name, rect.x + rect.width * 0.5f - size.GetWidth() * 0.5f, y + SPACE_UP);
}

// void VerticalImageList::OnDrawBackground(wxDC& dc, const wxRect& rect, size_t n) const
// {
//   	dc.SetPen(*wxRED_PEN);
//   	dc.DrawRectangle(rect);
// }

void VerticalImageList::OnDrawSeparator(wxDC& dc, wxRect& rect, size_t n) const
{
	dc.SetPen(wxPen(wxColour(0, 0, 0), 3));
	dc.DrawLine(rect.GetLeftBottom(), rect.GetRightBottom());
}

wxCoord VerticalImageList::OnMeasureItem(size_t n) const
{
	const Bitmap* bmp = m_items[n]->getBitmap();
	if (bmp) 
		return bmp->getBitmap()->GetHeight() + SPACE_UP + SPACE_DOWN;
	else 
		return SPACE_UP + SPACE_DOWN;
}

void VerticalImageList::onDragInit(wxMouseEvent& event)
{
	if (event.Dragging())
	{
		wxTextDataObject tdo(m_name + "," + wxString::FromDouble(GetSelection()));
		wxDropSource ds(tdo);
		ds.DoDragDrop(wxDrag_CopyOnly);
	}
}