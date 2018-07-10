#ifndef _DEDITOR_MOTOX_LIBRARY_COMBINATION_ITEM_H_
#define _DEDITOR_MOTOX_LIBRARY_COMBINATION_ITEM_H_

#include <wxGUI/wxGUI.h>

namespace deditor
{
	namespace motox
	{
		class LibraryCombinationItem : public wxgui::ISymbol
		{
		public:
			LibraryCombinationItem();

			//
			// IObject interface
			//
			virtual LibraryCombinationItem* clone() { return NULL; }

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

//			void createBitmap();

			const std::vector<wxgui::ISprite*>& getAllSprites() const { 
				return m_sprites; 
			}

			const f2Vec2& getCenter() const { return m_center; }

		protected:
			virtual void loadResources();

		private:
			void setCenter();

		private:
			std::vector<wxgui::ISprite*> m_sprites;

			f2Vec2 m_center;

		}; // LibraryCombinationItem
	}
}

#endif // _DEDITOR_MOTOX_LIBRARY_COMBINATION_ITEM_H_