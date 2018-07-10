#ifndef _WX_GUI_INTERFACE_LIBRARY_PAGE_H_
#define _WX_GUI_INTERFACE_LIBRARY_PAGE_H_

#include <Fruits2D/Fruits2D.h>
#include <wx/wx.h>

namespace wxgui
{
	class ListItem;
	class ISymbol;
	class LibraryList;

	class ILibraryPage : public wxWindow, public ISerializable
	{
	public:
		ILibraryPage(wxWindow* parent, const wxString& name);

		//
		// ISerializable interface
		//
		virtual void loadFromTextFile(std::ifstream& fin);
		virtual void storeToTextFile(std::ofstream& fout) const;

		virtual bool isHandleSymbol(ISymbol* symbol) const = 0;

		virtual void clear();

		void traverse(IVisitor& visitor) const;

		const wxString& getName() const { return m_name; }

		ListItem* getItem(int index = -1) const;
		ISymbol* getSymbol(int index = -1) const;

		void reloadTexture() const;

		LibraryList* getList() { return m_list; }

	protected:
		virtual void initLayout(bool draggable = true);

		virtual void onAddPress(wxCommandEvent& event) = 0;
		virtual void onDelPress(wxCommandEvent& event);

	protected:
		void initButtons(wxSizer* sizer);

	protected:
		wxString m_name;

		wxButton *m_btnAdd, *m_btnDel;

		LibraryList* m_list;

	}; // ILibraryPage
}

#endif // _WX_GUI_INTERFACE_LIBRARY_PAGE_H_