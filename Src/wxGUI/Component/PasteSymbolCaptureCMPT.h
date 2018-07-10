#ifndef _WX_GUI_PASTE_SYMBOL_CAPTURE_CMPT_H_
#define _WX_GUI_PASTE_SYMBOL_CAPTURE_CMPT_H_

#include "AbstractEditCMPT.h"

#include <Fruits2D/Fruits2D.h>

namespace wxgui
{
	class MultiSpritesImpl;
	class LibraryPanel;

	class PasteSymbolCaptureCMPT : public AbstractEditCMPT
	{
	public:
		PasteSymbolCaptureCMPT(wxWindow* parent, const wxString& name,
			EditPanel* editPanel, MultiSpritesImpl* spritesImpl, 
			LibraryPanel* libraryPanel);

		f2Vec2 getOffset() const;

	protected:
		virtual wxSizer* initLayout();

	private:
		wxSpinCtrl *m_xSpin, *m_ySpin;

	}; // PasteSymbolCaptureCMPT
}

#endif // _WX_GUI_PASTE_SYMBOL_CAPTURE_CMPT_H_