#ifndef _DEDITOR_MONSTER_TOOLBAR_PANEL_H_
#define _DEDITOR_MONSTER_TOOLBAR_PANEL_H_

#include <wxGUI/wxGUI.h>

namespace deditor
{
	namespace monster
	{
		class StagePanel;

		class ToolbarPanel : public wxgui::ToolbarPanel
		{
		public:
			ToolbarPanel(wxWindow* parent, StagePanel* editPanel,
				wxgui::LibraryPanel* libraryPanel,
				wxgui::PropertySettingPanel* propertyPanel);

			void setValues(int time, int height/*, int edge*/,
				int min, int max);

		protected:
			virtual wxSizer* initLayout();

		private:
			wxSizer* initSettingPanel();
			wxSizer* initButtonsPanel();

			void onGridEdgeChanged(wxScrollEvent& event);
			void onSettingsChanged(wxSpinEvent& event);
			void onMinMaxValChanged(wxCommandEvent& event);

			void onPreview(wxCommandEvent& event);

		private:
			wxgui::LibraryPanel* m_libraryPanel;

			wxSlider* m_edgeSlider;

			wxSpinCtrl* m_heightSpin;
			wxSpinCtrl* m_timeSpin;

			wxTextCtrl* m_minText;
			wxTextCtrl* m_maxText;

		}; // ToolbarPanel 
	}
}

#endif // _DEDITOR_MONSTER_TOOLBAR_PANEL_H_