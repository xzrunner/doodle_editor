#ifndef _WX_GUI_EDIT_PANEL_H_
#define _WX_GUI_EDIT_PANEL_H_

#include "Interface.h"

#include <wx/wx.h>
#include <Fruits2D/Fruits2D.h>

namespace wxgui
{
	class AbstractEditOP;
	class GLCanvas;
	class Camera;
	class AbstractAtomicOP;

	class EditPanel : public wxPanel, public ICameraObserver
	{
	public:
		EditPanel(wxWindow* parent);
		virtual ~EditPanel();

 		//
 		// ICameraObserver interface
 		//
 		virtual void onCameraChanged();

		f2Vec2 transPosScreenToProject(int x, int y) const;
//		f2Vec2 transPosProjectToScreen(const f2Vec2& proj) const;

		void drawEditTemp() const;

		AbstractEditOP* getEditOP() const { return m_editOP; }
		void setEditOP(AbstractEditOP* editOP);

		GLCanvas* getCanvas() const { return m_canvas; }
		void setCanvas(GLCanvas* canvas) { m_canvas = canvas; }

		Camera* getCamera() const { return m_camera; }

		// In Stage, class StagePanel can't get focus, only its class StageGLCanvas has the focus, so 
		// these two func should be called by StageGLCanvas.
		// While in SymbolEdit, class SymbolEditPanel can get focus.
		void onMouse(wxMouseEvent& event);
		virtual void onKeyDown(wxKeyEvent& event);
		virtual void onKeyUp(wxKeyEvent& event);
		void onMouseWheelRotation(int x, int y, int direction);

		void resetCanvas();

		void undo();
		void redo();
		void addHistoryOP(AbstractAtomicOP* op);

		void clear();

	protected:
		void onSize(wxSizeEvent& event);

	private:
		void clearAtomicOPStack(std::stack<AbstractAtomicOP*>& stack);

	protected:
		AbstractEditOP* m_editOP;

		GLCanvas* m_canvas;
		Camera* m_camera;

		std::stack<AbstractAtomicOP*> m_undoStack, m_redoStack;

		DECLARE_EVENT_TABLE()

	}; // EditPanel
}

#endif // _WX_GUI_EDIT_PANEL_H_