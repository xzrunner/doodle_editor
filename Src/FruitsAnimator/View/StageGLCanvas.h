#ifndef _FRUITS_ANIMATOR_STAGE_GL_CANVAS_H_
#define _FRUITS_ANIMATOR_STAGE_GL_CANVAS_H_

#include <wxGUI/wxGUI.h>

namespace FRUITS_ANIMATOR
{
	class StagePanel;

	class StageGLCanvas : public wxgui::GLCanvas
	{
	public:
		StageGLCanvas(StagePanel* editPanel);

	protected:
		virtual void onDraw();

		void onMouse(wxMouseEvent& event);
		void onKeyDown(wxKeyEvent& event);

	private:
		void drawbackground() const;

	private:
		class DrawVisitor : public IVisitor
		{
		public:
			DrawVisitor();
			virtual void visit(IObject* object, bool& bFetchNext);
		}; // DrawVisitor

	}; // StageGLCanvas
}

#endif // _FRUITS_ANIMATOR_STAGE_GL_CANVAS_H_