#ifndef _EASY_BUILDER_PREVIEW_CANVAS_H_
#define _EASY_BUILDER_PREVIEW_CANVAS_H_

#include <wxGUI/wxGUI.h>

namespace ebuilder
{
	class LibraryPanel;

	namespace preview
	{
		class Panel;

		class Canvas : public wxgui::GLCanvas
		{
		public:
			Canvas(Panel* panel, LibraryPanel* libraryPanel);
			virtual ~Canvas();

		protected:
			virtual void initGL();
			virtual void onDraw();

		private:
			LibraryPanel* m_libraryPanel;

		}; // Canvas
	}
}

#endif // _EASY_BUILDER_PREVIEW_CANVAS_H_