#ifndef _WX_GUI_GL_CANVAS_H_
#define _WX_GUI_GL_CANVAS_H_

#include <Fruits2D/Fruits2D.h>
#include <wx/glcanvas.h>

namespace wxgui
{
	class Camera;
	class EditPanel;

	class GLCanvas : public wxGLCanvas
	{
	public:
		GLCanvas(EditPanel* editPanel);
		virtual ~GLCanvas();

		virtual void clear() {}

		void resetInitState();		// Another GLCanvas closed, refresh the under one

		void resetViewport();		// On Mouse Wheel
									// onSize no use, if the size not change
									// also can put gluOrtho2D in each onPaint, save this and Camera's observer pattern

		void setBgColor(const f2Colorf& color);

	protected:
		virtual void initGL();
		virtual void onDraw() = 0;

		void onSize(wxSizeEvent& event);
		void onPaint(wxPaintEvent& event);
		void onEraseBackground(wxEraseEvent& event);
 		void onMouse(wxMouseEvent& event);
 		void onKeyDown(wxKeyEvent& event);
		void onKeyUp(wxKeyEvent& event);

	protected:
		EditPanel* m_editPanel;

		Camera* m_camera;

		f2Colorf m_bgColor;

		int m_width, m_height;

	private:
		bool m_isInit;
		wxGLContext* m_context;

		DECLARE_EVENT_TABLE()

	}; // GLCanvas
}

#endif // _WX_GUI_GL_CANVAS_H_