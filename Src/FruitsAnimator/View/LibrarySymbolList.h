#ifndef _FRUITS_ANIMATOR_LIBRARY_SYMBOL_LIST_H_
#define _FRUITS_ANIMATOR_LIBRARY_SYMBOL_LIST_H_

#include <wxGUI/wxGUI.h>

namespace FRUITS_ANIMATOR
{
	class Symbol;
	class StagePanel;

	class LibrarySymbolList : public wxgui::VerticalImageList, public ISerializable
	{
	public:
		LibrarySymbolList(wxWindow* parent);

		//
		// ISerializable interface
		//
		virtual void loadFromTextFile(std::ifstream& fin);
		virtual void storeToTextFile(std::ofstream& fout) const;

		Symbol* getSymbol(int index) const;
		int getIndex(Symbol* symbol) const;

		void reloadAllTexture();

		void setStagePanel(StagePanel* stagePanel);

	protected:
		virtual void onListDoubleClicked(wxCommandEvent& event);

	private:
		StagePanel* m_stagePanel;

	}; // LibrarySymbolList
}

#endif // _FRUITS_ANIMATOR_LIBRARY_SYMBOL_LIST_H_