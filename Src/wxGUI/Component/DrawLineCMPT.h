#ifndef _WX_GUI_DRAW_LINE_CMPT_H_
#define _WX_GUI_DRAW_LINE_CMPT_H_

#include "AbstractEditCMPT.h"

namespace wxgui
{
	class MultiShapesImpl;

	class DrawLineCMPT : public AbstractEditCMPT
	{
	public:
		DrawLineCMPT(wxWindow* parent, const wxString& name,
			EditPanel* editPanel, MultiShapesImpl* shapesImpl);

	protected:
		virtual wxSizer* initLayout();

	}; // DrawLineCMPT
}

#endif // _WX_GUI_DRAW_LINE_CMPT_H_