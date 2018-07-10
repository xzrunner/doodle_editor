#ifndef _DEDITOR_MOTOX_BREAKABLE_SPRITE_H_
#define _DEDITOR_MOTOX_BREAKABLE_SPRITE_H_

#include "LibraryBreakableItem.h"

#include <wxGUI/wxGUI.h>

namespace deditor
{
	namespace motox
	{
		class BreakableSprite : public wxgui::CombinationSprite
		{
		public:
			BreakableSprite();
			BreakableSprite(const BreakableSprite& sprite);
			BreakableSprite(LibraryBreakableItem* symbol, bool useMeshes);
			BreakableSprite(wxgui::CombinationSymbol* symbol);

			//
			// IObject interface
			//
			virtual BreakableSprite* clone();

			void breakToPiecesOld(std::vector<wxgui::ISprite*>& pieces,
				const f2Vec2& pos) const;
			void breakToPieces(std::vector<wxgui::ISprite*>& pieces,
				const f2Vec2& pos) const;

			const wxString& getFilepath() const;

		private:
			wxgui::ISprite* combineMeshes(const std::vector<wxgui::ISprite*>& meshes) const;

			void initPartPhysics(wxgui::ISprite* part, bool isPiece) const;

		private:
			LibraryBreakableItem* m_item;

		}; // BreakableSprite
	}
}

#endif // _DEDITOR_MOTOX_BREAKABLE_SPRITE_H_