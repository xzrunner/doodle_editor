#ifndef _WX_GUI_PASTE_SYMBOL_PHYSICS_CMPT_H_
#define _WX_GUI_PASTE_SYMBOL_PHYSICS_CMPT_H_

#include "AbstractEditCMPT.h"

#include <Fruits2D/Fruits2D.h>
#include <Box2D/Box2D.h>

namespace wxgui
{
	class MultiSpritesImpl;
	class LibraryPanel;
	class PhysicsPanelImpl;
	class PasteSymbolRandomWidget;

	class PasteSymbolPhysicsCMPT : public AbstractEditCMPT
	{
	public:
		PasteSymbolPhysicsCMPT(wxWindow* parent, const wxString& name,
			EditPanel* editPanel, MultiSpritesImpl* spritesImpl, LibraryPanel* libraryPanel,
			PhysicsPanelImpl* physicsImpl, b2World* world, b2World* worldReverse,
			float* pScale = NULL, PasteSymbolRandomWidget* randomWidget = NULL);

	protected:
		virtual wxSizer* initLayout();

	private:
		void onChangeGravity(wxCommandEvent& event);

		void onChangeStaticType(wxCommandEvent& event);

	private:
		wxRadioBox* m_gravityChoice;

		b2World *m_world, *m_worldReverse;

	}; // PasteSymbolPhysicsCMPT
}

#endif // _WX_GUI_PASTE_SYMBOL_PHYSICS_CMPT_H_