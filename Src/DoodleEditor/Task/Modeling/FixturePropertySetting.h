#ifndef _DEDITOR_MODELING_FIXTURE_PROPERTY_SETTING_H_
#define _DEDITOR_MODELING_FIXTURE_PROPERTY_SETTING_H_

#include <wxGUI/wxGUI.h>

namespace deditor
{
	namespace modeling
	{
		class FixtureData;

		class FixturePropertySetting : public wxgui::IPropertySetting
		{
		public:
			FixturePropertySetting(wxgui::EditPanel* editPanel, FixtureData* fixture);

			virtual void updatePanel(wxgui::PropertySettingPanel* panel);

			virtual void onPropertyGridChange(const wxString& name, const wxAny& value);
			virtual void updatePropertyGrid(wxgui::PropertySettingPanel* panel);
			virtual void enablePropertyGrid(wxgui::PropertySettingPanel* panel, bool bEnable);

		private:
			FixtureData* m_fixture;

		}; // FixturePropertySetting
	}
}

#endif // _DEDITOR_MODELING_FIXTURE_PROPERTY_SETTING_H_