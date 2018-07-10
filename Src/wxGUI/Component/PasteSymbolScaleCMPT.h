#ifndef _WX_GUI_PASTE_SYMBOL_SCALE_CMPT_H_
#define _WX_GUI_PASTE_SYMBOL_SCALE_CMPT_H_

#include "AbstractEditCMPT.h"

namespace wxgui
{
	class MultiSpritesImpl;
	class LibraryPanel;

	class PasteSymbolScaleCMPT : public AbstractEditCMPT
	{
	public:
		PasteSymbolScaleCMPT(wxWindow* parent, const wxString& name,
			EditPanel* editPanel, MultiSpritesImpl* spritesImpl, 
			LibraryPanel* libraryPanel);

	protected:
		virtual wxSizer* initLayout();

	private:
		void onChangeScale(wxSpinEvent& event);

	private:
		float m_scaleVal;

	}; // PasteSymbolScaleCMPT
}

#endif // _WX_GUI_PASTE_SYMBOL_SCALE_CMPT_H_