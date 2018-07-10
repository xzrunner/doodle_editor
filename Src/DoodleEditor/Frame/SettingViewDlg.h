#ifndef _DEDITOR_SETTING_VIEW_DLG_H_
#define _DEDITOR_SETTING_VIEW_DLG_H_

#include <wxGUI/wxGUI.h>

namespace deditor
{
	class SettingViewDlg : public wxDialog
	{
	public:
		SettingViewDlg(wxWindow* parent, wxgui::GLCanvas* canvas);

	private:
		wxSizer* initDisplayTypePanel();
		wxSizer* initStylePanel();

		void onChangeDisplayType(wxCommandEvent& event);
		void onChangeStyle(wxSpinEvent& event);
		void onChangeDisplayTriangles(wxCommandEvent& event);
		void onChangeDisplayPolygonBound(wxCommandEvent& event);

	private:
		wxgui::GLCanvas* m_canvas;

		wxSpinCtrl* m_ctlPointSize;

	}; // SettingViewDlg
}

#endif // _DEDITOR_SETTING_VIEW_DLG_H_