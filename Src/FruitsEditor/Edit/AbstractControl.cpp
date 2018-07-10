#include "AbstractControl.h"
#include "AbstractView.h"
#include "AbstractModel.h"
#include "ShortcutKeyListener.h"
#include "KeyboardTest.h"
#include "EditOperation/AbstractOp.h"
#include "freeglut/freeglut.h"

using namespace FEDITOR;

AbstractControl::AbstractControl()
{
	m_view = NULL;
	m_model = NULL;
	m_editOp = NULL;
}

AbstractControl::~AbstractControl()
{
	if (m_editOp) delete m_editOp;
	if (m_view) delete m_view;
	if (m_model) delete m_model;
}

void AbstractControl::onKeyboard(unsigned char key, int x, int y)
{
	m_view->getShortcutKeyLsn().onKeyboard(key);

	if (m_editOp) m_editOp->onKeyboard(key);
}

void AbstractControl::onKeyboardSpecial(int key, int x, int y)
{
	if (m_editOp)
	{
		switch (key)
		{
		case GLUT_KEY_LEFT:
			m_editOp->onKeyboardSpecial(KEY_LEFT);
			break;
		case GLUT_KEY_RIGHT:
			m_editOp->onKeyboardSpecial(KEY_RIGHT);
			break;
		case GLUT_KEY_UP:
			m_editOp->onKeyboardSpecial(KEY_UP);
			break;
		case GLUT_KEY_DOWN:
			m_editOp->onKeyboardSpecial(KEY_DOWN);
			break; 
		}
	}
}

void AbstractControl::onMouseDrag(int x, int y)
{
	if (m_editOp) m_editOp->onMouseDrag(x, y);
}

void AbstractControl::onMouseMove(int x, int y)
{
	if (m_editOp) m_editOp->onMouseMove(x, y);
}

void AbstractControl::onMouseWheel(int direction, int x, int y)
{
	m_view->onMouseWheel(direction, x, y);
}

void AbstractControl::onMouseButton(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON)
	{
		if (state == GLUT_DOWN)
			onMouseLeftDown(x, y);
		else if (state == GLUT_UP)
			onMouseLeftUp(x, y);
	}
	else if (button == GLUT_RIGHT_BUTTON)
	{
		if (state == GLUT_DOWN)
			onMouseRightDown(x, y);
		else if (state == GLUT_UP)
			onMouseRightUp(x, y);
	}
}

void AbstractControl::createUIFrame(int mainWnd)
{
	createEditCmpt();
	m_view->createUIRoot(mainWnd);
	m_view->createUIControls();
}

void AbstractControl::step()
{
	update();
	display();
}

void AbstractControl::reshape(int fw, int fh, int vw, int vh)
{
	m_view->reshape(fw, fh, vw, vh);
}

f2Vec2 AbstractControl::transPosScrToPoj(int x, int y) const
{
	return m_view->transPosScrToPoj(x, y);
}

LayersMgr& AbstractControl::getLayersMgr()
{
	return m_model->getLayersMgr();
}

CmptMgr& AbstractControl::getCmptMgr()
{
	return m_view->getCmptMgr();
}

void AbstractControl::setEditOp(AbstractOp* editOp)
{
	if (m_editOp) delete m_editOp;
	m_editOp = editOp;
}

float AbstractControl::getScale() const
{
	return m_view->getScale();
}

AbstractOp* AbstractControl::getEditOp() const
{
	return m_editOp;
}

void AbstractControl::onMouseLeftDown(int x, int y)
{
	if (m_editOp) m_editOp->onMouseLeftDown(x, y);
}

void AbstractControl::onMouseLeftUp(int x, int y)
{
	if (m_editOp) m_editOp->onMouseLeftUp(x, y);
}

void AbstractControl::onMouseRightDown(int x, int y)
{
	if (m_editOp) m_editOp->onMouseRightDown(x, y);
}

void AbstractControl::onMouseRightUp(int x, int y)
{
	if (m_editOp) m_editOp->onMouseRightUp(x, y);
}

void AbstractControl::handleModelEvent()
{
	while (m_model->hasNextEvent())
	{
		Event event = m_model->getNextEvent();
		m_view->onModelEvent(event);
	}
}

void AbstractControl::update()
{
	m_view->update();
	handleUIEvent();
	handleModelEvent();
	handleStep();
}

void AbstractControl::display() const
{
	m_view->display(m_model->getLayersMgrConst());
}