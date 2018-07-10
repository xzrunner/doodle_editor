#ifndef _WX_GUI_TOOLS_DRAG_TARGET_NULL_H_
#define _WX_GUI_TOOLS_DRAG_TARGET_NULL_H_

#include <wx/dnd.h>

namespace wxgui
{
	class DragTargetNull : public wxTextDropTarget
	{
	public:
		virtual bool OnDropText(wxCoord x, wxCoord y, const wxString& data) {
			return true;
		}

	}; // DragTargetNull
}

#endif // _WX_GUI_TOOLS_DRAG_TARGET_NULL_H_