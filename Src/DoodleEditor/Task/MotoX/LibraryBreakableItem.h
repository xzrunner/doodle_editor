#ifndef _DEDITOR_MOTOX_LIBRARY_BREAKABLE_ITEM_H_
#define _DEDITOR_MOTOX_LIBRARY_BREAKABLE_ITEM_H_

#include <wxGUI/wxGUI.h>

namespace deditor
{
	namespace motox
	{
		class LibraryBreakableItem : public wxgui::ISymbol
		{
		public:
			static const wxString TAG;

		public:
			LibraryBreakableItem();

			//
			// IObject interface
			//
			virtual LibraryBreakableItem* clone() { return NULL; }

			//
			// ISerializable interface
			//
			virtual void loadFromTextFile(std::ifstream& fin);
			virtual void storeToTextFile(std::ofstream& fout) const;

			//
			// wxgui::ISymbol interfaces
			//
			virtual void reloadTexture() const;
			virtual void draw() const;
			virtual float getWidth() const;
			virtual float getHeight() const;

			const wxgui::CombinationSymbol* getSpriteCombineSymbol() const {
				return m_spriteCombine;
			}
			const wxgui::CombinationSymbol* getMeshCombineSymbol() const {
				return m_meshCombine;
			}

		protected:
			virtual void loadResources();

		private:
			wxgui::CombinationSymbol* m_spriteCombine;
			wxgui::CombinationSymbol* m_meshCombine;

		}; // LibraryBreakableItem
	}
}

#endif // _DEDITOR_MOTOX_LIBRARY_BREAKABLE_ITEM_H_