#ifndef _WX_GUI_EDIT_POLYLINES_CMPT_H_
#define _WX_GUI_EDIT_POLYLINES_CMPT_H_

#include "AbstractEditCMPT.h"

#include <Fruits2D/Fruits2D.h>

namespace wxgui
{
	class MultiShapesImpl;

	class EditPolylinesCMPT : public AbstractEditCMPT
	{
	public:
		EditPolylinesCMPT(wxWindow* parent, const wxString& name,
			EditPanel* editPanel, MultiShapesImpl* shapesImpl);

		virtual void updateControlValue();

		float getSimplifyThreshold() const;

	protected:
		virtual wxSizer* initLayout();

	private:
		wxSizer* initSimplifyPanel();
		wxSizer* initSmoothPanel();
		wxSizer* initEditPanel();

		void onSimplifyThresholdChanged(wxSpinEvent& event);
		void onUpdateFromSimplified(wxCommandEvent& event);

		void onMergeTwoChain(wxCommandEvent& event);
		void onTranslate(wxCommandEvent& event);

	private:
		MultiShapesImpl* m_shapesImpl;

		wxSpinCtrl* m_simplifySpin;

		wxButton* m_btnMerge;

	}; // EditPolylinesCMPT
}

#endif // _WX_GUI_EDIT_POLYLINES_CMPT_H_