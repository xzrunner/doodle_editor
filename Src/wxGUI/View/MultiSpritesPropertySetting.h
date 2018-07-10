#ifndef _WX_GUI_MULTI_SPRITES_PROPERTY_SETTING_H
#define _WX_GUI_MULTI_SPRITES_PROPERTY_SETTING_H

#include "IPropertySetting.h"

#include <vector>

namespace wxgui
{
	class ISprite;

	class MultiSpritesPropertySetting : public IPropertySetting
	{
	public:
		MultiSpritesPropertySetting(EditPanel* editPanel, 
			const std::vector<ISprite*>& sprites);

		virtual void updatePanel(PropertySettingPanel* panel);

		virtual void onPropertyGridChange(const wxString& name, const wxAny& value);
		virtual void updatePropertyGrid(PropertySettingPanel* panel);
		virtual void enablePropertyGrid(PropertySettingPanel* panel, bool bEnable);

	private:
		std::vector<ISprite*> m_sprites;

	}; // MultiSpritesPropertySetting
}

#endif // _WX_GUI_MULTI_SPRITES_PROPERTY_SETTING_H
