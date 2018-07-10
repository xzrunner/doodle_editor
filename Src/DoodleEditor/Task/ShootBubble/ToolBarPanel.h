#ifndef _DEDITOR_SHOOT_BUBBLE_TOOLBAR_PANEL_H_
#define _DEDITOR_SHOOT_BUBBLE_TOOLBAR_PANEL_H_

#include <wxGUI/wxGUI.h>

namespace deditor
{
	namespace shoot_bubble
	{
		class StagePanel;

		class ToolbarPanel : public wxgui::ToolbarPanel
		{
		public:
			ToolbarPanel(wxWindow* parent, StagePanel* editPanel,
				wxgui::LibraryPanel* libraryPanel,
				wxgui::PropertySettingPanel* propertyPanel);

		protected:
			virtual wxSizer* initLayout();

		private:
			void onParamsChanged(wxSpinEvent& event);

		private:
			wxSpinCtrl *m_row, *m_col;
			wxSpinCtrl* m_edge;

		}; // ToolbarPanel
	}
}

#endif // _DEDITOR_SHOOT_BUBBLE_TOOLBAR_PANEL_H_