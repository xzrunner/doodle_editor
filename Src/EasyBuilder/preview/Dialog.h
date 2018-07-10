#ifndef _EASY_BUILDER_PREVIEW_DIALOG_H_
#define _EASY_BUILDER_PREVIEW_DIALOG_H_

#include <wxGUI/wxGUI.h>

namespace ebuilder
{
	class Scene;
	class LibraryPanel;

	namespace preview
	{
		class Dialog : public wxDialog
		{
		public:
			Dialog(wxWindow* parent, Scene* scene,
				LibraryPanel* libraryPanel);
			virtual ~Dialog();

		}; // Dialog
	}
}

#endif // _EASY_BUILDER_PREVIEW_DIALOG_H_