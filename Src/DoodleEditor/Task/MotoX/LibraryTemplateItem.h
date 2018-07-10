#ifndef _DEDITOR_MOTOX_LIBRARY_TEMPLATE_ITEM_H_
#define _DEDITOR_MOTOX_LIBRARY_TEMPLATE_ITEM_H_

#include <wxGUI/wxGUI.h>

namespace deditor
{
	namespace motox
	{
		class LibraryTemplateItem : public wxgui::ISymbol
		{
		public:
			LibraryTemplateItem();

			//
			// IObject interface
			//
			virtual LibraryTemplateItem* clone() { return NULL; }

			//
			// ISerializable interface
			//
			virtual void loadFromTextFile(std::ifstream& fin) {}
			virtual void storeToTextFile(std::ofstream& fout) const {}

			//
			// wxgui::ISymbol interface
			//
			virtual void reloadTexture() const {}
			virtual void draw() const {}
			virtual float getWidth() const;
			virtual float getHeight() const;

			void computeCenter();

		protected:
			virtual void loadResources();

		public:
			std::vector<wxgui::ISprite*> m_sprites;
			
			f2Vec2 m_center;

		}; // LibraryTemplateItem
	}
}

#endif // _DEDITOR_MOTOX_LIBRARY_TEMPLATE_ITEM_H_