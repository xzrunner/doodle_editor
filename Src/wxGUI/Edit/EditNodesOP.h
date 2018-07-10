#ifndef _WX_GUI_EDIT_NODES_OP_H_
#define _WX_GUI_EDIT_NODES_OP_H_

#include "SelectNodesOP.h"

namespace wxgui
{
	class EditNodesOP : public SelectNodesOP
	{
	public:
		EditNodesOP(EditPanel* editPanel, MultiShapesImpl* shapesImpl);

		virtual bool onKeyDown(int keyCode);
		virtual bool onMouseLeftDown(int x, int y);
		virtual bool onMouseDrag(int x, int y);

		virtual bool onDraw() const;
		virtual bool clear();

		void simplify(float threshold);
		void smooth(float samplingWidth);
		void updateModified();

	private:
		struct Modified
		{
			SelectNodesOP::ChainSelectedNodes* src;
			std::vector<f2Vec2> dst;
		};

	private:
		f2Vec2 m_lastPos;

		std::vector<Modified> m_buffer;

	}; // EditNodesOP
}

#endif // _WX_GUI_EDIT_NODES_OP_H_