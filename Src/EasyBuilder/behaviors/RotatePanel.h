#ifndef _EASY_BUILDER_ROTATE_PANEL_H_
#define _EASY_BUILDER_ROTATE_PANEL_H_

#include "BehaviorPanel.h"

namespace ebuilder
{
	class Rotate;

	class RotatePanel : public BehaviorPanel
	{
	private:
		RotatePanel(wxWindow* parent, ebuilder::Rotate* behavior);

	protected:
		virtual wxSizer* createExtend(wxWindow* extend);

	private:
		void onPGChange(wxPropertyGridEvent& event);

	private:
		ebuilder::Rotate* m_behavior;

		wxPropertyGrid* m_pg;

		friend class BehaviorFactory;

	}; // RotatePanel
}

#endif // _EASY_BUILDER_ROTATE_PANEL_H_