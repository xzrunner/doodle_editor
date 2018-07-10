#ifndef _FEDITOR_ABSTRACT_OPERATION_H_
#define _FEDITOR_ABSTRACT_OPERATION_H_
#include <Fruits2D/Fruits2D.h>

namespace FEDITOR
{
	class AbstractControl;
	class AbstractEditOpCB;

	class AbstractOp
	{
	public:
		AbstractOp(AbstractControl* task, AbstractOp* supplement = NULL, AbstractEditOpCB* callback = NULL);
		virtual ~AbstractOp();

		virtual void onKeyboard(unsigned char key);
		virtual void onKeyboardSpecial(int key);
		virtual void onMouseLeftDown(int x, int y);
		virtual void onMouseLeftUp(int x, int y);
		virtual bool onMouseRightDown(int x, int y);
		virtual bool onMouseRightUp(int x, int y);
		virtual void onMouseMove(int x, int y);
		virtual void onMouseDrag(int x, int y);

	protected:
		f2Vec2 getMousePos(int x, int y) const;

	protected:
		AbstractControl* m_task;

		AbstractOp* m_supplement;

		AbstractEditOpCB* m_callback;

	}; // AbstractOp
}

#endif // _FEDITOR_ABSTRACT_OPERATION_H_