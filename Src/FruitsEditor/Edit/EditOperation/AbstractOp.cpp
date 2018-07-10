#include "AbstractOp.h"
#include "AbstractEditOpCB.h"
#include "../AbstractControl.h"

using namespace FEDITOR;

AbstractOp::AbstractOp(AbstractControl* task, AbstractOp* supplement/* = NULL*/, AbstractEditOpCB* callback/* = NULL*/)
{
	m_task = task;
	m_supplement = supplement;
	m_callback = callback;
}

AbstractOp::~AbstractOp()
{
	if (m_supplement) delete m_supplement;
	if (m_callback) delete m_callback;
}

void AbstractOp::onKeyboard(unsigned char key)
{
	if (m_supplement) m_supplement->onKeyboard(key);
}

void AbstractOp::onKeyboardSpecial(int key)
{
	if (m_supplement) m_supplement->onKeyboardSpecial(key);
}

void AbstractOp::onMouseLeftDown(int x, int y)
{
	if (m_supplement) m_supplement->onMouseLeftDown(x, y);
}

void AbstractOp::onMouseLeftUp(int x, int y)
{
	if (m_supplement) m_supplement->onMouseLeftUp(x, y);
}

bool AbstractOp::onMouseRightDown(int x, int y) 
{
	if (m_supplement) return m_supplement->onMouseRightDown(x, y);
	else return false; 
}

bool AbstractOp::onMouseRightUp(int x, int y) 
{ 
	if (m_supplement) return m_supplement->onMouseRightUp(x, y);
	else return false; 
}

void AbstractOp::onMouseMove(int x, int y) 
{
	if (m_supplement) m_supplement->onMouseMove(x, y);
}

void AbstractOp::onMouseDrag(int x, int y) 
{
	if (m_supplement) m_supplement->onMouseDrag(x, y);
}

f2Vec2 AbstractOp::getMousePos(int x, int y) const
{
	return m_task->transPosScrToPoj(x, y);
}