#ifndef _WX_GUI_INTERFACE_PROPERTY_SETTING_H_
#define _WX_GUI_INTERFACE_PROPERTY_SETTING_H_

#include <wx/wx.h>
#include <wx/propgrid/propgrid.h>

namespace wxgui
{
	class EditPanel;
	class PropertySettingPanel;

	class IPropertySetting
	{
	public:
		IPropertySetting(wxgui::EditPanel* editPanel, const wxString& type);
		virtual ~IPropertySetting() {}

		virtual void updatePanel(PropertySettingPanel* panel) = 0;

		virtual void onPropertyGridChange(const wxString& name, const wxAny& value) = 0;
		virtual void updatePropertyGrid(PropertySettingPanel* panel) = 0;
		virtual void enablePropertyGrid(PropertySettingPanel* panel, bool bEnable) = 0;

	protected:
		wxString getPGType(wxPropertyGrid* pg) const;

	protected:
		static const wxString TYPE_NAME;

	protected:
		wxgui::EditPanel* m_editPanel;

		wxString m_type;

	}; // IPropertySetting
}

#endif // _WX_GUI_INTERFACE_PROPERTY_SETTING_H_