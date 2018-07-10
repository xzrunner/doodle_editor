#ifndef _FRUITS_ANIMATOR_LIBRARY_SYMBOL_PAGE_H_
#define _FRUITS_ANIMATOR_LIBRARY_SYMBOL_PAGE_H_

#include <wxGUI/wxGUI.h>

namespace FRUITS_ANIMATOR
{
	class Symbol;
	class LibrarySymbolList;
	class StagePanel;

	class LibrarySymbolPage : public wxgui::ILibraryPage
	{
	public:
		LibrarySymbolPage(wxWindow* parent);

		//
		// ISerializable interface
		//
		virtual void loadFromTextFile(std::ifstream& fin);
		virtual void storeToTextFile(std::ofstream& fout) const;

		virtual void traverse(IVisitor& visitor) const;

		Symbol* getSymbol(int index) const;
		int getIndex(Symbol* symbol) const;

		void reloadAllTexture();

		void setStagePanel(StagePanel* stagePanel);

		void clear();

	protected:
		virtual void onAddPress(wxCommandEvent& event);
		virtual void onDelPress(wxCommandEvent& event);

	private:
		LibrarySymbolList* m_symbolList;

	}; // LibrarySymbolPage
}

#endif // _FRUITS_ANIMATOR_LIBRARY_SYMBOL_PAGE_H_