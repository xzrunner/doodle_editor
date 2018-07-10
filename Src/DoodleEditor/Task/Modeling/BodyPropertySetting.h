#ifndef _DEDITOR_MODELING_BODY_PROPERTY_SETTING_H_
#define _DEDITOR_MODELING_BODY_PROPERTY_SETTING_H_

#include <wxGUI/wxGUI.h>

namespace deditor
{
	namespace modeling
	{
		class BodyData;

		class BodyPropertySetting : public wxgui::IPropertySetting
		{
		public:
			BodyPropertySetting(wxgui::EditPanel* editPanel, wxgui::ISprite* sprite);

			virtual void updatePanel(wxgui::PropertySettingPanel* panel);

			virtual void onPropertyGridChange(const wxString& name, const wxAny& value);
			virtual void updatePropertyGrid(wxgui::PropertySettingPanel* panel);
			virtual void enablePropertyGrid(wxgui::PropertySettingPanel* panel, bool bEnable);

		private:
			BodyData* m_body;

		}; // BodyPropertySetting
	}
}

#endif // _DEDITOR_MODELING_BODY_PROPERTY_SETTING_H_