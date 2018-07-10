#ifndef _FEDITOR_DRAW_POLYLINE_OPERATION_H_
#define _FEDITOR_DRAW_POLYLINE_OPERATION_H_
#include "AbstractOp.h"

namespace FEDITOR
{
	class NodeCaptureCmpt;

	class DrawPolylineOp : public AbstractOp
	{
	public:
		DrawPolylineOp(AbstractControl* task, NodeCaptureCmpt* capture, AbstractEditOpCB* callback);

		virtual void onMouseLeftDown(int x, int y);
		virtual bool onMouseRightDown(int x, int y);
		virtual void onMouseMove(int x, int y);

	private:
		void straightLineFix(f2Vec2& pos) const;

	private:
		int m_count;

		NodeCaptureCmpt* m_capture;

//		f2Vec2 m_lastPos;
		std::stack<f2Vec2> m_ctlpos;

	}; // DrawPolylineOp
}

#endif // _FEDITOR_DRAW_POLYLINE_OPERATION_H_