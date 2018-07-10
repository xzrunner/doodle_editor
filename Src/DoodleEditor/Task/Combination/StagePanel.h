#ifndef _DEDITOR_COMBINATION_STAGE_PANEL_H_
#define _DEDITOR_COMBINATION_STAGE_PANEL_H_

#include <wxGUI/wxGUI.h>

namespace deditor
{
	namespace combination
	{
		class StagePanel : public wxgui::EditPanel, public wxgui::SpritesPanelImpl, 
			public wxgui::ShapesPanelImpl
		{
		public:
			StagePanel(wxWindow* parent, wxgui::PropertySettingPanel* propertyPanel,
				wxgui::LibraryPanel* libraryPanel);
			virtual ~StagePanel();

			virtual void clear();

		}; // StagePanel
	}
}

#endif // _DEDITOR_COMBINATION_STAGE_PANEL_H_