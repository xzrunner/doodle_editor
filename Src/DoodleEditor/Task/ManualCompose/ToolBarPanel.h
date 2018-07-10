#ifndef _DEDITOR_MANUAL_COMPOSE_TOOLBAR_PANEL_H_
#define _DEDITOR_MANUAL_COMPOSE_TOOLBAR_PANEL_H_

#include <wxGUI/wxGUI.h>

namespace deditor
{
	namespace manual_compose
	{
		class ToolbarPanel : public wxgui::ToolbarPanel
		{
		public:
			ToolbarPanel(wxWindow* parent, wxgui::EditPanel* editPanel);

		protected:
			virtual wxSizer* initLayout();

		private:
			void onChooseBackground(wxCommandEvent& event);

		}; // ToolbarPanel
	}
}

#endif // _DEDITOR_MANUAL_COMPOSE_TOOLBAR_PANEL_H_