#ifndef _EASY_BUILDER_SCALE_SIZE_PANEL_H_
#define _EASY_BUILDER_SCALE_SIZE_PANEL_H_

#include "BehaviorPanel.h"

namespace ebuilder
{
	class ScaleSize;

	class ScaleSizePanel : public BehaviorPanel
	{
	private:
		ScaleSizePanel(wxWindow* parent, ScaleSize* behavior);

	protected:
		virtual wxSizer* createExtend(wxWindow* extend);

	private:
		wxSizer* createSetValueItem(wxWindow* extend);

		void onScaleChanged(wxSpinEvent& event);

	private:
		ScaleSize* m_behavior;

		friend class BehaviorFactory;

	}; // ScaleSizePanel
}

#endif // _EASY_BUILDER_SCALE_SIZE_PANEL_H_