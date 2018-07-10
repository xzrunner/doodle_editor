#ifndef _WX_GUI_PASTE_SPRITE_CMPT_H_
#define _WX_GUI_PASTE_SPRITE_CMPT_H_

#include "AbstractEditCMPT.h"

namespace wxgui
{
	class SpritesPanelImpl;
	class PropertySettingPanel;

	class PasteSpriteCMPT : public AbstractEditCMPT
	{
	public:
		PasteSpriteCMPT(wxWindow* parent, const wxString& name, EditPanel* editPanel, 
			SpritesPanelImpl* spritesImpl, PropertySettingPanel* propertyPanel);

		bool isHorMirror() const { return m_xMirror->IsChecked(); }
		bool isVerMirror() const { return m_yMirror->IsChecked(); }

	protected:
		virtual wxSizer* initLayout();

	private:
		wxCheckBox* m_xMirror;
		wxCheckBox* m_yMirror;

	}; // PasteSpriteCMPT
}

#endif // _WX_GUI_PASTE_SPRITE_CMPT_H_