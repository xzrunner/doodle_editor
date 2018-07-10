#ifndef _WX_GUI_SELECT_SHAPES_OP_H_
#define _WX_GUI_SELECT_SHAPES_OP_H_

#include "DrawRectangleOP.h"

#include "Dataset/SelectionSet.h"

namespace wxgui
{
	class MultiShapesImpl;
	class AbstractEditCMPT;

	class SelectShapesOP : public DrawRectangleOP
	{
	public:
		SelectShapesOP(EditPanel* editPanel, MultiShapesImpl* shapesImpl, 
			AbstractEditCMPT* callback = NULL);
		virtual ~SelectShapesOP();

		virtual bool onKeyDown(int keyCode);
		virtual bool onMouseLeftDown(int x, int y);
		virtual bool onMouseLeftUp(int x, int y);

		virtual bool onDraw() const;
		virtual bool clear();

	private:
		void clearClipboard();

	protected:
		f2Vec2 m_firstPos;

		ShapeSelection* m_selection;

	private:
		AbstractEditCMPT* m_callback;

		MultiShapesImpl* m_shapeImpl;

		std::vector<IShape*> m_clipboard;

		bool m_lastCtrlPress;

	}; // SelectShapesOP
}

#endif // _WX_GUI_SELECT_SHAPES_OP_H_