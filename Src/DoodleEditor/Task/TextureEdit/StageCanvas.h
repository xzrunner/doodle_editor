#ifndef _DEDITOR_TEXTURE_EDIT_STAGE_CANVAS_H_
#define _DEDITOR_TEXTURE_EDIT_STAGE_CANVAS_H_

#include <wxGUI/wxGUI.h>

namespace deditor
{
	namespace texture_edit
	{
		class StagePanel;

		class StageCanvas : public wxgui::GLCanvas
		{
		public:
			StageCanvas(StagePanel* editPanel);

		protected:
			virtual void onDraw();

		private:
			wxgui::SpriteBatch m_batch;

		}; // StageCanvas
	}
}

#endif // _DEDITOR_TEXTURE_EDIT_STAGE_CANVAS_H_