#ifndef _DEDITOR_LINE_EDIT_STAGE_PANEL_H_
#define _DEDITOR_LINE_EDIT_STAGE_PANEL_H_

#include <wxGUI/wxGUI.h>

namespace deditor
{
	namespace line_edit
	{
		class StagePanel : public wxgui::EditPanel, public wxgui::ShapesPanelImpl
		{
		public:
			StagePanel(wxWindow* parent);

			virtual void clear();

		}; // StagePanel
	}
}

#endif // _DEDITOR_LINE_EDIT_STAGE_PANEL_H_