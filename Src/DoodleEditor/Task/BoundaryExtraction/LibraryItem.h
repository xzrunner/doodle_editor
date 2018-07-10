#ifndef _DEDITOR_BOUNDARY_EXTRACTION_LIBRARY_ITEM_H_
#define _DEDITOR_BOUNDARY_EXTRACTION_LIBRARY_ITEM_H_

#include <wxGUI/wxGUI.h>

namespace deditor
{
	namespace boundary_extraction
	{
		class LibraryItem : public wxgui::ISymbol, public UserDataImpl
		{
		public:
			virtual ~LibraryItem();

			//
			// UserDataImpl interface
			//	
			virtual void clearUserData(bool deletePtr);

			//
			// wxgui::ISymbol interface
			//
			virtual float getWidth() const;
			virtual float getHeight() const;

		}; // LibraryItem
	}
}

#endif // _DEDITOR_BOUNDARY_EXTRACTION_LIBRARY_ITEM_H_