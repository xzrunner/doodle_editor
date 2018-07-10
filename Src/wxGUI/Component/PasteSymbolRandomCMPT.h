#ifndef _WX_GUI_PASTE_SYMBOL_RANDOM_CMPT_H_
#define _WX_GUI_PASTE_SYMBOL_RANDOM_CMPT_H_

#include "AbstractEditCMPT.h"

namespace wxgui
{
	class MultiSpritesImpl;
	class LibraryPanel;
	class PasteSymbolRandomWidget;

	class PasteSymbolRandomCMPT : public AbstractEditCMPT
	{
	public:
		PasteSymbolRandomCMPT(wxWindow* parent, const wxString& name,
			EditPanel* editPanel, MultiSpritesImpl* spritesImpl, 
			LibraryPanel* libraryPanel);

	protected:
		virtual wxSizer* initLayout();

	private:
		PasteSymbolRandomWidget* m_randomWidget;

	}; // PasteSymbolRandomCMPT
}

#endif // _WX_GUI_PASTE_SYMBOL_RANDOM_CMPT_H_