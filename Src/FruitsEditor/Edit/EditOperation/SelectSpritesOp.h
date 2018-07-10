#ifndef _FEDITOR_SELECT_SPRITES_OPERATION_H_
#define _FEDITOR_SELECT_SPRITES_OPERATION_H_
#include "AbstractOp.h"

namespace FEDITOR
{
	class ChainShape;
	class Sprite;
	class Layer;
	class SelectionSet;

	class SelectSpritesOp : public AbstractOp
	{
	public:
		SelectSpritesOp(AbstractControl* task, Layer* editable, bool isAccurate = false);
		virtual ~SelectSpritesOp();

		virtual void onKeyboard(unsigned char key);
		virtual void onMouseLeftDown(int x, int y);
		virtual void onMouseLeftUp(int x, int y);
		virtual bool onMouseRightDown(int x, int y);
		virtual void onMouseDrag(int x, int y);

		SelectionSet& getSelection();

	private:
		void prepareSelectDraw();

	private:
		Layer* m_dataLayer;
		SelectionSet& m_selection;

		bool m_isAccurate;

		// todo
		f2Vec2 m_firstPos;

		Layer* m_tmpLayer;
		Sprite* m_tmpSprite;
		ChainShape* m_tmpShape;
		// 

	}; // SelectSpritesOp

	inline SelectionSet& SelectSpritesOp::getSelection()
	{
		return m_selection;
	}
}

#endif // _FEDITOR_SELECT_SPRITES_OPERATION_H_