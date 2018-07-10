#ifndef _WX_GUI_PASTE_SYMBOL_CAPTURE_OP_H_
#define _WX_GUI_PASTE_SYMBOL_CAPTURE_OP_H_

#include "PasteSymbolOP.h"

namespace wxgui
{
	class MultiSpritesImpl;
	class LibraryPanel;
	class PasteSymbolCaptureCMPT;

	class PasteSymbolCaptureOP : public PasteSymbolOP
	{
	public:
		PasteSymbolCaptureOP(EditPanel* editPanel, MultiSpritesImpl* spritesImpl, 
			LibraryPanel* libraryPanel, PasteSymbolCaptureCMPT* cmpt);

		virtual bool onMouseLeftDown(int x, int y);
		virtual bool onMouseMove(int x, int y);

		virtual bool clear();

	private:
		PasteSymbolCaptureCMPT* m_cmpt;

		bool m_bCaptured;
		f2Vec2 m_lastPos;

	}; // PasteSymbolCaptureOP
}

#endif // _WX_GUI_PASTE_SYMBOL_CAPTURE_OP_H_