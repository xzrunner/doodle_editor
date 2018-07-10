#ifndef _FRUITS_ANIMATOR_SPRITE_EDIT_GL_CANVAS_H_
#define _FRUITS_ANIMATOR_SPRITE_EDIT_GL_CANVAS_H_
#include <wxGUI/wxGUI.h>

namespace FRUITS_ANIMATOR
{
	class Sprite;

	class SpriteEditGLCanvas : public wxgui::GLCanvas
	{
	public:
		SpriteEditGLCanvas(wxgui::EditPanel* parent, Sprite* sprite);

	protected:
		virtual void initGL();
		virtual void onDraw();

		void onMouse(wxMouseEvent& event);

	private:
		Sprite* m_sprite;

	}; // SpriteEditGLCanvas
}

#endif // _FRUITS_ANIMATOR_SPRITE_EDIT_GL_CANVAS_H_