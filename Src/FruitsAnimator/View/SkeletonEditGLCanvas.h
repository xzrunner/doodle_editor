#ifndef _FRUITS_ANIMATOR_SKELETON_EDIT_GL_CANVAS_H_
#define _FRUITS_ANIMATOR_SKELETON_EDIT_GL_CANVAS_H_

#include "Dataset/WholeSkeleton.h"

#include <wxGUI/wxGUI.h>

namespace FRUITS_ANIMATOR
{
	class WholeSkeleton;
	class SkeletonSymbolList;

	class SkeletonEditGLCanvas : public wxgui::GLCanvas
	{
	public:
		SkeletonEditGLCanvas(wxgui::EditPanel* editPanel, WholeSkeleton* skeleton, 
			SkeletonSymbolList* symbolList);

	protected:
		virtual void initGL();
		virtual void onDraw();

		void onMouse(wxMouseEvent& event);

	private:
		WholeSkeleton* m_skeleton;
		SkeletonSymbolList* m_symbolList;

		DECLARE_EVENT_TABLE()

	}; // SkeletonEditGLCanvas
}

#endif // _FRUITS_ANIMATOR_SKELETON_EDIT_GL_CANVAS_H_