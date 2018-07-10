#ifndef _WX_GUI_ABSTRACT_ATOMIC_OP_H_
#define _WX_GUI_ABSTRACT_ATOMIC_OP_H_

#include <Fruits2D/Fruits2D.h>

namespace wxgui
{
	class AbstractAtomicOP
	{
	public:
		virtual ~AbstractAtomicOP() {}

		virtual void undo() = 0;
		virtual void redo() = 0;

	}; // AbstractAtomicOP
}

#endif // _WX_GUI_ABSTRACT_ATOMIC_OP_H_