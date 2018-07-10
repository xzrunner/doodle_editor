#ifndef _EASY_BUILDER_PROPERTY_SETTING_PANEL_H_
#define _EASY_BUILDER_PROPERTY_SETTING_PANEL_H_

#include <wxGUI/wxGUI.h>

namespace ebuilder
{
	class PropertySettingPanel : public wxgui::PropertySettingPanel
	{
	public:
		PropertySettingPanel(wxWindow* parent);

	private:
		void initLayout();

		void initTitle(wxSizer* sizer);
		void initPropertyGrid(wxSizer* sizer);

	}; // PropertySettingPanel
}

#endif // _EASY_BUILDER_PROPERTY_SETTING_PANEL_H_