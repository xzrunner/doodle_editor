#ifndef _DEDITOR_BOUNDARY_EXTRACTION_LIBRARY_IMAGE_ITEM_H_
#define _DEDITOR_BOUNDARY_EXTRACTION_LIBRARY_IMAGE_ITEM_H_

#include "LibraryItem.h"

#include <wxGUI/wxGUI.h>

namespace deditor
{
	namespace boundary_extraction
	{
		class LibraryImageItem : public LibraryItem
		{
		public:
			LibraryImageItem(const wxString& filename);
			virtual ~LibraryImageItem();
			
			//
			// IObject interface
			//	
			virtual LibraryImageItem* clone() { return NULL; }

			//
			// ISerializable interface
			//
			virtual void loadFromTextFile(std::ifstream& fin);
			virtual void storeToTextFile(std::ofstream& fout) const;

			//
			// wxgui::ISymbol interface
			//	
			virtual void reloadTexture() const;
			virtual void draw() const;

		protected:
			virtual void loadResources();

		private:
			wxgui::ISymbol* m_symbol;

		}; // LibraryImageItem
	}
}

#endif // _DEDITOR_BOUNDARY_EXTRACTION_LIBRARY_IMAGE_ITEM_H_