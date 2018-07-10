#ifndef _WX_GUI_PASTE_SYMBOL_RANDOM_WIDGET_H_
#define _WX_GUI_PASTE_SYMBOL_RANDOM_WIDGET_H_

#include <wx/wx.h>
#include <Fruits2D/Fruits2D.h>

namespace wxgui
{
	class ISymbol;
	class LibraryPanel;

	class PasteSymbolRandomWidget : public wxPanel
	{
	public:
		struct RandomValue
		{
			ISymbol* symbol;
			float scale;
			float angle;	// in radian
		};

	public:
		PasteSymbolRandomWidget(wxWindow* parent, LibraryPanel* libraryPanel);

		void getRandomValue(RandomValue& val) const;

	private:
		void initLayout();

	private:
		class FilterSymbolVisitor : public IVisitor
		{
		public:
			FilterSymbolVisitor(const wxString& filter, std::vector<ISymbol*>& result);

			virtual void visit(IObject* object, bool& bFetchNext);

		private:
			wxString m_filter;

			std::vector<ISymbol*>& m_result;
		};

	private:
		LibraryPanel* m_libraryPanel;

		wxTextCtrl* m_symbolFilterCtrl;
		wxSpinCtrl *m_scaleMinCtrl, *m_scaleMaxCtrl;
		wxSpinCtrl *m_angleMinCtrl, *m_angleMaxCtrl;

	}; // PasteSymbolRandomWidget
}

#endif // _WX_GUI_PASTE_SYMBOL_RANDOM_WIDGET_H_