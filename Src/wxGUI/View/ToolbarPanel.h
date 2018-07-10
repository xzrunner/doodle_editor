#ifndef _WX_GUI_TOOLBAR_PANEL_H_
#define _WX_GUI_TOOLBAR_PANEL_H_

#include "Component/AbstractEditCMPT.h"

namespace wxgui
{
	class AbstractEditCMPT;

	class ToolbarPanel : public AbstractEditCMPT
	{
	public:
		ToolbarPanel(wxWindow* parent, EditPanel* editPanel);

	}; // ToolbarPanel
}

#endif // _WX_GUI_TOOLBAR_PANEL_H_