#ifndef _WX_GUI_VERTICAL_IMAGE_LIST_H_
#define _WX_GUI_VERTICAL_IMAGE_LIST_H_

#include <wx/wx.h>
#include <wx/vlbox.h>
#include <Fruits2D/Fruits2D.h>

namespace wxgui
{
	class ListItem;

	class VerticalImageList : public wxVListBox
	{
	public:
		VerticalImageList(wxWindow* parent, const wxString& name = wxEmptyString,
			bool draggable = true);
		virtual ~VerticalImageList();

		// VerticalImageList
		virtual void onListSelected(wxCommandEvent& event) {}
		virtual void onListDoubleClicked(wxCommandEvent& event) {}

		void traverse(IVisitor& visitor) const;

		void clear();
		void insert(ListItem* item);
		void remove();

	protected:
		// wxVListBox
		virtual void OnDrawItem(wxDC& dc, const wxRect& rect, size_t n) const;
//		virtual void OnDrawBackground(wxDC& dc, const wxRect& rect, size_t n) const;
		virtual void OnDrawSeparator(wxDC& dc, wxRect& rect, size_t n) const;
		virtual wxCoord OnMeasureItem(size_t n) const;

	private:
		void onDragInit(wxMouseEvent& event);

	private:
		static const int SPACE_UP = 5;
		static const int SPACE_DOWN = 25;

	protected:
		std::vector<ListItem*> m_items;

	private:
		wxString m_name;

	}; // VerticalImageList
}

#endif // _WX_GUI_VERTICAL_IMAGE_LIST_H_