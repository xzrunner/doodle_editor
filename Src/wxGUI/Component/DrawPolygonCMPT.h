#ifndef _WX_GUI_DRAW_POLYGON_CMPT_H_
#define _WX_GUI_DRAW_POLYGON_CMPT_H_

#include "DrawPolylineCMPT.h"

#include "Dataset/Bitmap.h"

#include <wx/colordlg.h>

namespace wxgui
{
	class DrawPolygonCMPT : public DrawPolylineCMPT
	{
	public:
		DrawPolygonCMPT(wxWindow* parent, const wxString& name,
			EditPanel* editPanel, MultiShapesImpl* shapesImpl,
			wxColourData& colorData);

		virtual void updateControlValue();

	protected:
		virtual wxSizer* initLayout();

	private:
		wxSizer* initPreviewButtonPanel();

		void onSetColor(wxCommandEvent& event);
		void onChangeFillingType(wxCommandEvent& event);
		void onTriggerFillingColor(wxCommandEvent& event);

		void fillingButton();

	private:
		MultiShapesImpl* m_shapesImpl;

		wxColour m_color;
		wxColourData& m_colorData;

		Bitmap m_bitmap;
		wxString m_filePath;

		wxButton* m_btnReview;

		wxRadioBox* m_fillingTypeChoice;

		wxButton* m_btnTrigger;

	}; // DrawPolygonCMPT
}

#endif // _WX_GUI_DRAW_POLYGON_CMPT_H_