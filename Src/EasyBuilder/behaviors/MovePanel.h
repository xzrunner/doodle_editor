#ifndef _EASY_BUILDER_MOVE_PANEL_H_
#define _EASY_BUILDER_MOVE_PANEL_H_

#include "BehaviorPanel.h"

namespace ebuilder
{
	class Move;

	class MovePanel : public BehaviorPanel
	{
	private:
		MovePanel(wxWindow* parent, ebuilder::Move* behavior);

	protected:
		virtual wxSizer* createExtend(wxWindow* extend);

	private:
		void onPGChange(wxPropertyGridEvent& event);

	private:
		ebuilder::Move* m_behavior;

		wxPropertyGrid* m_pg;

		friend class BehaviorFactory;

	}; // MovePanel
}

#endif // _EASY_BUILDER_MOVE_PANEL_H_