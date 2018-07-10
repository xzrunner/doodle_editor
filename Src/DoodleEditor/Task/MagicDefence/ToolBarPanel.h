#ifndef _DEDITOR_MAGIC_DEFENCE_TOOLBAR_PANEL_H_
#define _DEDITOR_MAGIC_DEFENCE_TOOLBAR_PANEL_H_

#include <wxGUI/wxGUI.h>

namespace deditor
{
	namespace magic_defence
	{
		class StagePanel;

		class ToolbarPanel : public wxgui::ToolbarPanel
		{
		public:
			ToolbarPanel(wxWindow* parent, StagePanel* editPanel,
				wxgui::LibraryPanel* libraryPanel,
				wxgui::PropertySettingPanel* propertyPanel);

			void setValues(int time, int height);

		protected:
			virtual wxSizer* initLayout();

		private:
			wxSizer* initSettingPanel();
			wxSizer* initButtonsPanel();

			void onGridEdgeChanged(wxScrollEvent& event);
			void onSettingsChanged(wxSpinEvent& event);

			void onPreview(wxCommandEvent& event);

		private:
			wxgui::LibraryPanel* m_libraryPanel;

			wxSlider* m_edgeSlider;

			wxSpinCtrl* m_heightSpin;
			wxSpinCtrl* m_timeSpin;

		}; // StagePanel
	}
}

#endif // _DEDITOR_MAGIC_DEFENCE_TOOLBAR_PANEL_H_