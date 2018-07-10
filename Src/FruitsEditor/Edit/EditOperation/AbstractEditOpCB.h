#ifndef _FEDITOR_ABSTRACT_EDIT_OPERATION_CALLBACK_H_
#define _FEDITOR_ABSTRACT_EDIT_OPERATION_CALLBACK_H_
#include <Fruits2D/Fruits2D.h>

namespace FEDITOR
{
	class AbstractEditOpCB
	{
	public:
		virtual ~AbstractEditOpCB() {}

		virtual void afterKeyboard(unsigned char key) {}
		virtual void afterMouseLeftDown(const f2Vec2& pos) {}
		virtual void afterMouseLeftUp(const f2Vec2& pos) {}
		virtual void afterMouseRightDown(const f2Vec2& pos) {}
		virtual void afterMouseRightUp(const f2Vec2& pos) {}
		virtual void afterMouseMove(const f2Vec2& pos) {}
		virtual void afterMouseDrag(const f2Vec2& pos) {}

	}; // AbstractEditOpCB
}

#endif // _FEDITOR_ABSTRACT_EDIT_OPERATION_CALLBACK_H_