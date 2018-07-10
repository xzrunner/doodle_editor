#ifndef _FRUITS_ANIMATOR_SKELETON_SYMBOL_LIST_H_
#define _FRUITS_ANIMATOR_SKELETON_SYMBOL_LIST_H_

#include <wxGUI/wxGUI.h>

namespace FRUITS_ANIMATOR
{
	class LibraryPanel;
	class Symbol;

	class SkeletonSymbolList : public wxgui::VerticalImageList
	{
	public:
		SkeletonSymbolList(wxWindow* parent, LibraryPanel* library);

		void reloadAllTexture();

		Symbol* getSymbol(int index) const;

	private:

	}; // SkeletonSymbolList
}

#endif // _FRUITS_ANIMATOR_SKELETON_SYMBOL_LIST_H_

