#ifndef _FEDITOR_ARRANGE_SPRITE_OPERATION_H_
#define _FEDITOR_ARRANGE_SPRITE_OPERATION_H_
#include "AbstractOp.h"
#include "SelectSpritesOp.h"

namespace FEDITOR
{
	class Sprite;
	class Layer;
	class SelectionSet;
	class AbstractArrangeSpriteCB;

	class ArrangeSpriteOp : public AbstractOp
	{
	public:
		ArrangeSpriteOp(AbstractControl* task, Layer* editable, bool toInteger = false, 
			AbstractArrangeSpriteCB* callback = NULL, AbstractOp* supplement = NULL);
		virtual ~ArrangeSpriteOp();

		virtual void onKeyboard(unsigned char key);
		virtual void onKeyboardSpecial(int key);
		virtual void onMouseLeftDown(int x, int y);
		virtual void onMouseLeftUp(int x, int y);
		virtual bool onMouseRightDown(int x, int y);
		virtual bool onMouseRightUp(int x, int y);
		virtual void onMouseDrag(int x, int y);

	private:
		static const int DELETE_DIS = 2;

	private:
		void translateSprite(const f2Vec2& delta);
		void translateSpriteTo(const f2Vec2& dst);

		void rotateSpriteTo(const f2Vec2& dst);

		void scaleSpriteTo(const f2Vec2& dst);

	private:
		SelectSpritesOp m_selectOp;

		AbstractArrangeSpriteCB* m_callback;

		Layer* m_layer;
		SelectionSet& m_selection;

		bool m_bRightPress;
		f2Vec2 m_lastPos;

		f2Vec2 m_rightDownPos;	// no trans

		float m_xScaleInit, m_yScaleInit;

		bool m_toInteger;

	}; // ArrangeSpriteOp
}

#endif // _FEDITOR_ARRANGE_SPRITE_OPERATION_H_