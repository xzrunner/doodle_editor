#ifndef _WX_GUI_DRAW_PENCIL_LINE_CMPT_H_
#define _WX_GUI_DRAW_PENCIL_LINE_CMPT_H_

#include "AbstractEditCMPT.h"

namespace wxgui
{
	class MultiShapesImpl;

	class DrawPencilLineCMPT : public AbstractEditCMPT
	{
	public:
		DrawPencilLineCMPT(wxWindow* parent, const wxString& name,
			EditPanel* editPanel, MultiShapesImpl* shapesImpl);

		float getSimplifyThreshold() const {
			return m_thresholdSlider->GetValue() * 0.1f;
		}

	protected:
		virtual wxSizer* initLayout();

	private:
		wxSlider* m_thresholdSlider;

	}; // DrawPencilLineCMPT
}

#endif // _WX_GUI_DRAW_PENCIL_LINE_CMPT_H_