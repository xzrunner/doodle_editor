#ifndef _DEDITOR_BOUNDARY_EXTRACTION_LIBRARY_FILE_ITEM_H_
#define _DEDITOR_BOUNDARY_EXTRACTION_LIBRARY_FILE_ITEM_H_

#include "LibraryItem.h"

#include <wxGUI/wxGUI.h>

namespace deditor
{
	namespace boundary_extraction
	{
		class LibraryFileItem : public LibraryItem
		{
		public:
			LibraryFileItem(const wxString& filename);
			virtual ~LibraryFileItem();
			
			//
			// IObject interface
			//	
			virtual LibraryFileItem* clone() { return NULL; }

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
			void clear();

		private:
			std::vector<wxgui::ISprite*> m_sprites;

		}; // LibraryFileItem
	}
}

#endif // _DEDITOR_BOUNDARY_EXTRACTION_LIBRARY_FILE_ITEM_H_