#ifndef _DEDITOR_MEDELING_PREVIEW_DIALOG_H_
#define _DEDITOR_MEDELING_PREVIEW_DIALOG_H_

#include <wxGUI/wxGUI.h>

namespace deditor
{
	namespace modeling
	{
		class StagePanel;

		class PreviewDialog : public wxDialog
		{
		public:
			PreviewDialog(StagePanel* stagePanel, 
				wxgui::LibraryPanel* libraryPanel);

		}; // PreviewDialog
	}
}

#endif // _DEDITOR_MEDELING_PREVIEW_DIALOG_H_