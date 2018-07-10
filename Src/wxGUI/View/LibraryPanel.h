#ifndef _WX_GUI_LIBRARY_PANEL_H_
#define _WX_GUI_LIBRARY_PANEL_H_

#include <Fruits2D/Fruits2D.h>
#include <wx/wx.h>
#include <wx/notebook.h>

namespace wxgui
{
	class ISymbol;
	class ILibraryPage;
	class SymbolMgr;
	class LibraryList;

	class LibraryPanel : public wxPanel, public ISerializable
	{
	public:
		LibraryPanel(wxWindow* parent);

		//
		// ISerializable interface
		//
		virtual void loadFromTextFile(std::ifstream& fin);
		virtual void storeToTextFile(std::ofstream& fout) const;

		virtual void onPageChanged(wxBookCtrlEvent& event);

		void clear();

		void reloadTexture() const;

		void addPage(ILibraryPage* page);

		ISymbol* getSymbol(int index = -1) const;

		void loadFromSymbolMgr(const SymbolMgr& mgr);

		void traverse(IVisitor& visitor) const;

		wxWindow* getNotebook() { return m_notebook; }

	private:
		void initLayout();

	protected:
		wxNotebook* m_notebook;

		std::vector<ILibraryPage*> m_pages;

		ILibraryPage* m_selected;

	}; // LibraryPanel
}

#endif // _WX_GUI_LIBRARY_PANEL_H_