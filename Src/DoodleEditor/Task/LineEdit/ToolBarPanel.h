#ifndef _DEDITOR_LINE_EDIT_TOOLBAR_PANEL_H_
#define _DEDITOR_LINE_EDIT_TOOLBAR_PANEL_H_

#include <wxGUI/wxGUI.h>

namespace deditor
{
	namespace line_edit
	{
		class StagePanel;

		class ToolbarPanel : public wxgui::ToolbarPanel
		{
		public:
			ToolbarPanel(wxWindow* parent, StagePanel* editPanel);

		protected:
			virtual wxSizer* initLayout();

		}; // ToolbarPanel
	}
}

#endif // _DEDITOR_LINE_EDIT_TOOLBAR_PANEL_H_