#ifndef _WX_GUI_DRAW_SPRITES_VISITOR_H_
#define _WX_GUI_DRAW_SPRITES_VISITOR_H_

#include <Fruits2D/Fruits2D.h>

namespace wxgui
{
	class SpriteBatch;

	class DrawSpritesVisitor : public IVisitor
	{
	public:
		DrawSpritesVisitor(SpriteBatch& batch);
		virtual ~DrawSpritesVisitor();

		virtual void visit(IObject* object, bool& bFetchNext);

	private:
		SpriteBatch& m_batch;

	}; // DrawSpritesVisitor
}

#endif // _WX_GUI_DRAW_SPRITES_VISITOR_H_