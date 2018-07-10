#ifndef _WX_GUI_ABSTRACT_EDIT_OP_H_
#define _WX_GUI_ABSTRACT_EDIT_OP_H_

#include <Fruits2D/Fruits2D.h>

namespace wxgui
{
	class EditPanel;

	class AbstractEditOP : public Object
	{
	public:
		AbstractEditOP(EditPanel* editPanel) {
			m_editPanel = editPanel;
		}
		virtual ~AbstractEditOP() {}

		virtual bool onKeyDown(int keyCode) { return false; }
		virtual bool onKeyUp(int keyCode) { return false; }
		virtual bool onMouseLeftDown(int x, int y) { return false; }
		virtual bool onMouseLeftUp(int x, int y) { return false; }
		virtual bool onMouseRightDown(int x, int y) { return false; }
		virtual bool onMouseRightUp(int x, int y) { return false; }
		virtual bool onMouseMove(int x, int y) { return false; }
		virtual bool onMouseDrag(int x, int y) { return false; }
		virtual bool onMouseLeftDClick(int x, int y) { return false; }
		virtual bool onMouseWheelRotation(int x, int y, int direction) { return false; }

		virtual bool onDraw() const { return false; }
		virtual bool clear() { return false; }

	protected:
		EditPanel* m_editPanel;

	}; // AbstractEditOP
}

#endif // _WX_GUI_ABSTRACT_EDIT_OP_H_