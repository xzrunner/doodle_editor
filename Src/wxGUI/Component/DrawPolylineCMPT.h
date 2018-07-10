#ifndef _WX_GUI_DRAW_POLYLINE_CMPT_H_
#define _WX_GUI_DRAW_POLYLINE_CMPT_H_

#include "AbstractEditCMPT.h"

#include <Fruits2D/Fruits2D.h>

namespace wxgui
{
	class MultiShapesImpl;

	class DrawPolylineCMPT : public AbstractEditCMPT
	{
	public:
		enum Type
		{
			e_PenLine,
			e_CosineCurve
		};

	public:
		DrawPolylineCMPT(wxWindow* parent, const wxString& name,
			EditPanel* editPanel, MultiShapesImpl* shapesImpl, Type type);

		int getNodeCaptureDistance() const;

	protected:
		virtual wxSizer* initLayout();

	private:
		wxSlider* m_tolSlider;

	}; // DrawPolylineCMPT
}

#endif // _WX_GUI_DRAW_POLYLINE_CMPT_H_