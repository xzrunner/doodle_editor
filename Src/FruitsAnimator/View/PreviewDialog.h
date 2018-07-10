#ifndef _FRUITS_ANIMATOR_PREVIEW_DIALOG_H_
#define _FRUITS_ANIMATOR_PREVIEW_DIALOG_H_

#include <wx/wx.h>
#include <wxGUI/wxGUI.h>

namespace FRUITS_ANIMATOR
{
	class LayersMgr;
	class LibraryPanel;

	class PreviewDialog : public wxDialog
	{
	public:
		PreviewDialog(wxWindow* parent, LayersMgr* layers, LibraryPanel* library, int fps = 24);
		~PreviewDialog();

	private:
		void initLayout(LayersMgr* layers, LibraryPanel* library, int fps);

		void buildToolBar(wxSizer* topSizer);
		void buildEditPanel(wxSizer* topSizer, LayersMgr* layers, LibraryPanel* library, int fps);

		void onSetCirculate(wxCommandEvent& event);
		void onSetStop(wxCommandEvent& event);

	private:
		wxgui::EditPanel* m_editPanel;
		
	}; // PreviewDialog
}

#endif // _FRUITS_ANIMATOR_PREVIEW_DIALOG_H_