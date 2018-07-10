#ifndef _WX_GUI_LIBRARY_LIST_H_
#define _WX_GUI_LIBRARY_LIST_H_

#include "Widgets/VerticalImageList.h"

#include <Fruits2D/Fruits2D.h>

namespace wxgui
{
	class ISymbol;

	class LibraryList : public VerticalImageList, public ISerializable
	{
	public:
		LibraryList(wxWindow* parent, const wxString& filter = wxT("symbol"),
			bool draggable = true);

		//
		// ISerializable interface
		//
		virtual void loadFromTextFile(std::ifstream& fin);
		virtual void storeToTextFile(std::ofstream& fout) const;

		ListItem* getItem(int index = -1) const;
		ISymbol* getSymbol(int index = -1) const;

		void reloadTexture() const;

	}; // LibraryList
}

#endif // _WX_GUI_LIBRARY_LIST_H_