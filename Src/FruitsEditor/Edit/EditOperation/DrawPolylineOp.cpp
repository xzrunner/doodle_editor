#include "DrawPolylineOp.h"
#include "AbstractEditOpCB.h"
#include "Edit/EditComponent/NodeCaptureCmpt.h"
#include "Edit/KeyboardTest.h"

using namespace FEDITOR;

DrawPolylineOp::DrawPolylineOp(AbstractControl* task, NodeCaptureCmpt* capture, AbstractEditOpCB* callback)
	: AbstractOp(task, NULL, callback)
{
	m_count = 0;
	m_capture = capture;
}

void DrawPolylineOp::onMouseLeftDown(int x, int y)
{
	f2Vec2 pos = getMousePos(x, y);
	++m_count;

	const bool capture = m_capture && m_capture->captureByPos(pos);
	if (capture)
		pos = m_capture->getCapturedAddr().getPos();

	straightLineFix(pos);
	m_ctlpos.push(pos);

	if (m_callback) m_callback->afterMouseLeftDown(pos);
}

bool DrawPolylineOp::onMouseRightDown(int x, int y)
{
	if (m_count != 0)
	{
		--m_count;
		f2Vec2 pos = m_ctlpos.top(); m_ctlpos.pop();
		if (m_callback) m_callback->afterMouseRightDown(pos);
		return true;
	}
	else
	{
		return false;
	}
}

void DrawPolylineOp::onMouseMove(int x, int y)
{
	f2Vec2 pos = getMousePos(x, y);
	straightLineFix(pos);
	if (m_callback) m_callback->afterMouseMove(pos);
}

void DrawPolylineOp::straightLineFix(f2Vec2& pos) const
{
	if (!m_ctlpos.empty() && KeyBoardTest::isShiftPress())
	{
		f2Vec2 last = m_ctlpos.top();

		float nearest;
		f2Vec2 fixed = pos;

		const float dx = fabs(pos.x - last.x);
		nearest = dx;
		fixed.set(last.x, pos.y);

		const float dy = fabs(pos.y - last.y);
		if (dy < nearest)
		{
			nearest = dy;
			fixed.set(pos.x, last.y);
		}

		f2Vec2 other(last.x + 1, last.y - 1);
		const float dxyDown = f2Math::getDisPointToStraightLine(pos, last, other);
		if (dxyDown < nearest)
		{
			nearest = dxyDown;
			f2Math::getFootOfPerpendicular(last, other, pos, &fixed);
		}

		other.set(last.x + 1, last.y + 1);
		const float dxyUp = f2Math::getDisPointToStraightLine(pos, last, other);
		if (dxyUp < nearest)
		{
			nearest = dxyUp;
			f2Math::getFootOfPerpendicular(last, other, pos, &fixed);
		}

		pos = fixed;
	}
}