#ifndef _EASY_BUILDER_BEHAVIOR_PANEL_H_
#define _EASY_BUILDER_BEHAVIOR_PANEL_H_

#include "CollapsiblePane.h"

#include <wxGUI/wxGUI.h>

namespace ebuilder
{
	class BehaviorPanel : public CollapsiblePane
	{
	public:
		BehaviorPanel(wxWindow* parent, const wxString& name);

		virtual BehaviorPanel* clone() {
			return NULL;
		}

		virtual void update(const wxgui::LibraryList& list) {}

		void createPanel(wxWindow* parent);

	protected:
		virtual wxSizer* createExtend(wxWindow* extend) = 0;

	protected:
		static const wxString TIP_DRAG_BEHAVIOR;

		static const wxSize TIP_SIZE;

	}; // BehaviorPanel
}

#endif // _EASY_BUILDER_BEHAVIOR_PANEL_H_