#include "EditPanel.h"
#include "Edit/AbstractEditOP.h"
#include "Atomic/AbstractAtomicOP.h"
#include "View/Camera.h"

#include <wxGUI/wxGUI.h>

using namespace wxgui;

BEGIN_EVENT_TABLE(EditPanel, wxPanel)
	EVT_MOUSE_EVENTS(EditPanel::onMouse)
	EVT_KEY_DOWN(EditPanel::onKeyDown)
	EVT_KEY_UP(EditPanel::onKeyUp)
	EVT_SIZE(EditPanel::onSize)
END_EVENT_TABLE()

EditPanel::EditPanel(wxWindow* parent)
	: wxPanel(parent)
{
	m_editOP = NULL;
	m_canvas = NULL;
	m_camera = new Camera;
	m_camera->addObserver(this);
	SetFocus();		// For onMouseWheelRotation
}

EditPanel::~EditPanel()
{
	delete m_camera;
	delete m_canvas;
	if (m_editOP) m_editOP->release();
	clearAtomicOPStack(m_undoStack);
	clearAtomicOPStack(m_redoStack);
}

void EditPanel::onCameraChanged()
{
	if (m_canvas)
		m_canvas->resetViewport();
}

f2Vec2 EditPanel::transPosScreenToProject(int x, int y) const
{
	return m_camera->transPosScreenToProject(x, y, GetSize().GetWidth(), GetSize().GetHeight());
}

// f2Vec2 EditPanel::transPosProjectToScreen(const f2Vec2& proj) const
// {
// 	return m_camera->transPosProjectToScreen(proj, GetSize().GetWidth(), GetSize().GetHeight());
// }

void EditPanel::drawEditTemp() const
{
	if (m_editOP) m_editOP->onDraw();
}

void EditPanel::setEditOP(AbstractEditOP* editOP)
{
	if (m_editOP)
	{
		m_editOP->clear();
		m_editOP->release();
	}

	editOP->retain();
	m_editOP = editOP;
}

void EditPanel::onMouse(wxMouseEvent& event)
{
	if (!m_editOP) return;

	if (event.LeftDown())
		m_editOP->onMouseLeftDown(event.GetX(), event.GetY());
	else if (event.LeftUp())
		m_editOP->onMouseLeftUp(event.GetX(), event.GetY());
	else if (event.RightDown())
		m_editOP->onMouseRightDown(event.GetX(), event.GetY());
	else if (event.RightUp())
		m_editOP->onMouseRightUp(event.GetX(), event.GetY());
	else if (event.Moving())
		m_editOP->onMouseMove(event.GetX(), event.GetY());
	else if (event.Dragging())
		m_editOP->onMouseDrag(event.GetX(), event.GetY());
	else if (event.LeftDClick())
		m_editOP->onMouseLeftDClick(event.GetX(), event.GetY());
	else if (event.GetWheelRotation())
		m_editOP->onMouseWheelRotation(event.GetX(), event.GetY(), event.GetWheelRotation());
}

void EditPanel::onKeyDown(wxKeyEvent& event)
{
	if (wxGetKeyState(WXK_CONTROL_Z))
		undo();
	else if (wxGetKeyState(WXK_CONTROL_Y))
		redo();
	
	m_editOP->onKeyDown(event.GetKeyCode());
}

void EditPanel::onKeyUp(wxKeyEvent& event)
{
	m_editOP->onKeyUp(event.GetKeyCode());
}

void EditPanel::onMouseWheelRotation(int x, int y, int direction)
{
	const float oldScale = m_camera->getScale();
	const float newScale = direction > 0 ? oldScale / 1.1f : oldScale * 1.1f;
	const float cx = static_cast<float>(x),
		cy = static_cast<float>(GetSize().GetHeight() - y);
	m_camera->setScale(newScale, cx, cy, GetSize().GetWidth(), GetSize().GetHeight());
	Refresh();
}

void EditPanel::resetCanvas()
{
	if (m_canvas)
	{
		m_canvas->resetInitState();
		Refresh();
	}
}

void EditPanel::undo()
{
	if (!m_undoStack.empty())
	{
		AbstractAtomicOP* op = m_undoStack.top();
		m_undoStack.pop();
		op->undo();
		m_redoStack.push(op);
		Refresh();
	}
}

void EditPanel::redo()
{
	if (!m_redoStack.empty())
	{
		AbstractAtomicOP* op = m_redoStack.top();
		m_redoStack.pop();
		op->redo();
		m_undoStack.push(op);
		Refresh();
	}
}

void EditPanel::addHistoryOP(AbstractAtomicOP* op)
{
	m_undoStack.push(op);
	clearAtomicOPStack(m_redoStack);
}

void EditPanel::clear()
{
	m_editOP->clear();
}

void EditPanel::onSize(wxSizeEvent& event)
{
	if (m_canvas)
		m_canvas->SetSize(event.GetSize());
	m_camera->setCenter(f2Vec2(0.0f, 0.0f));
	Refresh();	// no refresh when change window size
}

void EditPanel::clearAtomicOPStack(std::stack<AbstractAtomicOP*>& stack)
{
	while (!stack.empty())
	{
		delete stack.top();
		stack.pop();
	}
}