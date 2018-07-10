#ifndef _FRUITS_ANIMATOR_LIBRARY_PANEL_H_
#define _FRUITS_ANIMATOR_LIBRARY_PANEL_H_

#include <Fruits2D/Fruits2D.h>
#include <wx/wx.h>

namespace FRUITS_ANIMATOR
{
	class Symbol;
	class WholeSkeleton;
	class StagePanel;
	class LibrarySymbolPage;
	class LibrarySymbolList;
	class LibrarySkeletonPage;

	class LibraryPanel : public wxPanel, public ISerializable
	{
	public:
		static const wxString SYMBOL_LIST_NAME;
		static const wxString SKELETON_LIST_NAME;

	public:
		LibraryPanel(wxWindow* parent);

		//
		// ISerializable interface
		//
		virtual void loadFromTextFile(std::ifstream& fin);
		virtual void storeToTextFile(std::ofstream& fout) const;

		Symbol* getSymbol(int index) const;
		WholeSkeleton* getSkeleton(int index) const;

		int getIndex(Symbol* symbol) const;
		int getIndex(WholeSkeleton* skeleton) const;

		void reloadAllTexture();

		void setStagePanel(StagePanel* stagePanel);

		void clear();

	private:
		void initLayout();

		void initTitle(wxSizer* sizer);
		void initTabPages(wxSizer* sizer);

	private:
		LibrarySymbolPage* m_symbolPage;
		LibrarySkeletonPage* m_skeletonPage;

	}; // LibraryPanel
}

#endif // _FRUITS_ANIMATOR_LIBRARY_PANEL_H_