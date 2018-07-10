#ifndef _FEDITOR_DRAW_POLYLINE_CALLBACK_H_
#define _FEDITOR_DRAW_POLYLINE_CALLBACK_H_
#include "AbstractEditOpCB.h"

namespace FEDITOR
{
	class ChainShape;
	class Sprite;

	class DrawPolylineCB : public AbstractEditOpCB
	{
	public:
		DrawPolylineCB(Sprite* sprite);
		DrawPolylineCB(Sprite* sprite, const std::vector<f2Vec2>& preload);
		virtual ~DrawPolylineCB();

		virtual void afterMouseLeftDown(const f2Vec2& pos);
		virtual void afterMouseRightDown(const f2Vec2& pos);
		virtual void afterMouseMove(const f2Vec2& pos);

	private:
		void eraseEmptyShape();

	private:
		Sprite* m_sprite;
		ChainShape *m_staticShape, *m_dynamicShape;

		bool m_finishDirSet;

	}; // DrawPolylineCB
}

#endif // _FEDITOR_DRAW_POLYLINE_CALLBACK_H_