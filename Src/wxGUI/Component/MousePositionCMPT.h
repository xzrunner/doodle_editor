#ifndef _WX_GUI_MOUSE_POSITION_CMPT_H_
#define _WX_GUI_MOUSE_POSITION_CMPT_H_

#include "AbstractEditCMPT.h"

#include <Fruits2D/Fruits2D.h>

namespace wxgui
{
	class MousePositionCMPT : public AbstractEditCMPT
	{
	public:
		MousePositionCMPT(wxWindow* parent, const wxString& name, EditPanel* editPanel);

		void updatePosition(const f2Vec2& pos);

	protected:
		virtual wxSizer* initLayout();

	private:
		wxTextCtrl *m_xText, *m_yText;

	}; // MousePositionCMPT
}

#endif // _WX_GUI_MOUSE_POSITION_CMPT_H_