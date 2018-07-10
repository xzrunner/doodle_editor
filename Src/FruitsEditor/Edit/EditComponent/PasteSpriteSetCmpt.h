#ifndef _FEDITOR_PASTE_SPRITE_SET_CMPT_H_
#define _FEDITOR_PASTE_SPRITE_SET_CMPT_H_
#include "AbstractCmpt.h"
#include "../Utility.h"

namespace FEDITOR
{
	class PasteSpriteSetCmpt : public AbstractCmpt
	{
	public:
		PasteSpriteSetCmpt(CmptMgr& cmptMgr);

		virtual void createUIControls(GLUI_Node* parent, ShortcutKeyListener* shortcutLsn);
		virtual void handleUIEvent();

		void getScale(float& x, float& y) const;

	private:
		void smallLayoutUI(GLUI_Node* parent);
		void largeLayoutUI(GLUI_Node* parent);

	private:
		float m_scale;
		int m_mirrorType;
			// 0 Null
			// 1 x
			// 2 y
			// 3 xy

	}; // PasteSpriteSetCmpt
}

#endif // _FEDITOR_PASTE_SPRITE_SET_CMPT_H_