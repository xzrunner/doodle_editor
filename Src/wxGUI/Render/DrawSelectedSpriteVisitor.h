#ifndef _WX_GUI_DRAW_SELECTED_SPRITE_VISITOR_H_
#define _WX_GUI_DRAW_SELECTED_SPRITE_VISITOR_H_

#include <Fruits2D/Fruits2D.h>

namespace wxgui
{
	class DrawSelectedSpriteVisitor : public IVisitor
	{
	public:
		DrawSelectedSpriteVisitor(const f2Colorf& color);

		virtual void visit(IObject* object, bool& bFetchNext);

	private:
		f2Colorf m_color;

	}; // DrawSelectedSpriteVisitor
}

#endif // _WX_GUI_DRAW_SELECTED_SPRITE_VISITOR_H_