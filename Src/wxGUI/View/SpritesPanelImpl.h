#ifndef _WX_GUI_SPRITES_PANEL_IMPL_H_
#define _WX_GUI_SPRITES_PANEL_IMPL_H_

#include "MultiSpritesImpl.h"

#include <wx/dnd.h>

namespace wxgui
{
	class EditPanel;
	class LibraryPanel;
	class ISprite;

	class SpritesPanelImpl : public MultiSpritesImpl
	{
	public:
		SpritesPanelImpl(EditPanel* editPanel, LibraryPanel* libraryPanel);
		virtual ~SpritesPanelImpl();

		virtual void traverseSprites(IVisitor& visitor, 
			TraverseType type = e_allExisting, bool order = true) const;
		virtual void removeSprite(ISprite* sprite);
		virtual void insertSprite(ISprite* sprite);
		virtual void clear();

	private:
		class DragSymbolTarget : public wxTextDropTarget
		{
		public:
			DragSymbolTarget(SpritesPanelImpl* panelImpl);

			virtual bool OnDropText(wxCoord x, wxCoord y, const wxString& data);

		private:
			SpritesPanelImpl* m_panelImpl;

		}; // DragSymbolTarget

	protected:
		LibraryPanel* m_libraryPanel;

	private:
		EditPanel* m_editPanel;

		std::vector<ISprite*> m_sprites;

		friend class DragSymbolTarget;

	}; // SpritesPanelImpl
}

#endif // _WX_GUI_SPRITES_PANEL_IMPL_H_