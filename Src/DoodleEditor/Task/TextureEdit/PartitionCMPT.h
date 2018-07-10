#ifndef _DEDITOR_TEXTURE_EDIT_PARTITION_CMPT_H_
#define _DEDITOR_TEXTURE_EDIT_PARTITION_CMPT_H_

#include <wxGUI/wxGUI.h>

namespace deditor
{
	namespace texture_edit
	{
		class StagePanel;

		class PartitionCMPT : public wxgui::AbstractEditCMPT
		{
		public:
			PartitionCMPT(wxWindow* parent, const wxString& name,
				StagePanel* editPanel);

		protected:
			virtual wxSizer* initLayout();

		private:
			void onPartitionImage(wxCommandEvent& event);

		private:
			wxSpinCtrl* m_rowNum;
			wxSpinCtrl* m_colNum;

		}; // PartitionCMPT
	}
}

#endif // _DEDITOR_TEXTURE_EDIT_PARTITION_CMPT_H_