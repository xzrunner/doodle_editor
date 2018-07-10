#ifndef _WX_GUI_PASTE_SYMBOL_OP_H_
#define _WX_GUI_PASTE_SYMBOL_OP_H_

#include "ZoomViewOP.h"

namespace wxgui
{
	class MultiSpritesImpl;
	class LibraryPanel;

	class PasteSymbolOP : public ZoomViewOP
	{
	public:
		PasteSymbolOP(EditPanel* editPanel, MultiSpritesImpl* panelImpl, 
			LibraryPanel* libraryPanel, float* pScale = NULL);

		virtual bool onMouseLeftDown(int x, int y);
		virtual bool onMouseMove(int x, int y);

		virtual bool onDraw() const;
		virtual bool clear();

	protected:
		MultiSpritesImpl* m_panelImpl;

		LibraryPanel* m_libraryPanel;

		float* m_pScale;

		f2Vec2 m_pos;

	}; // PasteSymbolOP
}

#endif // _WX_GUI_PASTE_SYMBOL_OP_H_