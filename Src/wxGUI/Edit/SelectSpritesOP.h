#ifndef _WX_GUI_SELECT_SPRITES_OP_H_
#define _WX_GUI_SELECT_SPRITES_OP_H_

#include "DrawRectangleOP.h"

#include "Dataset/SelectionSet.h"

namespace wxgui
{
	class MultiSpritesImpl;
	class AbstractEditCMPT;
	class PropertySettingPanel;
	class IPropertySetting;

	class SelectSpritesOP : public DrawRectangleOP
	{
	public:
		SelectSpritesOP(EditPanel* editPanel, MultiSpritesImpl* spritesImpl, 
			PropertySettingPanel* propertyPanel, AbstractEditCMPT* callback = NULL,
			const f2Colorf& color = f2Colorf(0, 0, 0));
		virtual ~SelectSpritesOP();

		virtual bool onKeyDown(int keyCode);
		virtual bool onMouseLeftDown(int x, int y);
		virtual bool onMouseLeftUp(int x, int y);

		virtual bool onDraw() const;
		virtual bool clear();

		virtual IPropertySetting* createPropertySetting(ISprite* sprite) const;
		virtual IPropertySetting* createPropertySetting(const std::vector<ISprite*>& sprites) const;

	protected:
		SpriteSelection* m_selection;

		PropertySettingPanel* m_propertyPanel;

	private:
		AbstractEditCMPT* m_callback;

		MultiSpritesImpl* m_spritesImpl;

		f2Vec2 m_firstPos;

	}; // SelectSpritesOP
}

#endif // _WX_GUI_SELECT_SPRITES_OP_H_