#ifndef _WX_GUI_SPRITE_PROPERTY_SETTING_H_
#define _WX_GUI_SPRITE_PROPERTY_SETTING_H_

#include "IPropertySetting.h"

#include <Fruits2D/Fruits2D.h>

namespace wxgui
{
	class ISprite;

	class SpritePropertySetting : public IPropertySetting
	{
	public:
		SpritePropertySetting(EditPanel* editPanel, ISprite* sprite);

		virtual void updatePanel(PropertySettingPanel* panel);

		virtual void onPropertyGridChange(const wxString& name, const wxAny& value);
		virtual void updatePropertyGrid(PropertySettingPanel* panel);
		virtual void enablePropertyGrid(PropertySettingPanel* panel, bool bEnable);

	private:
		ISprite* m_sprite;

	}; // SpritePropertySetting
}

#endif // _WX_GUI_SPRITE_PROPERTY_SETTING_H_