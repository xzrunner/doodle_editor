#ifndef _DEDITOR_MAGIC_DEFENCE_PREVIEW_DIALOG_H_
#define _DEDITOR_MAGIC_DEFENCE_PREVIEW_DIALOG_H_

#include <wxGUI/wxGUI.h>

namespace deditor
{
	namespace magic_defence
	{
		class StagePanel;

		class PreviewDialog : public wxDialog
		{
		public:
			PreviewDialog(wxWindow* parent, StagePanel* stagePanel,
				wxgui::LibraryPanel* libraryPanel);

		}; // PreviewDialog 
	}
}

#endif // _DEDITOR_MAGIC_DEFENCE_PREVIEW_DIALOG_H_