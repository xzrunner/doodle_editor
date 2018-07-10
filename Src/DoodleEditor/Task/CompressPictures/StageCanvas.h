#ifndef _DEDITOR_COMPRESS_PICTURE_STAGE_CANVAS_H_
#define _DEDITOR_COMPRESS_PICTURE_STAGE_CANVAS_H_

#include <wxGUI/wxGUI.h>

namespace deditor
{
	namespace compress_pictures
	{
		class StageCanvas : public wxgui::GLCanvas
		{
		public:
			StageCanvas(wxgui::EditPanel* parent);

		protected:
			virtual void onDraw();

		private:
			static const int SPACING = 5;

		}; // StageCanvas
	}
}

#endif // _DEDITOR_COMPRESS_PICTURE_STAGE_CANVAS_H_