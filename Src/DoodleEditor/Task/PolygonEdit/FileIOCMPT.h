#ifndef _DEDITOR_POLYGON_EDIT_FILE_IO_CMPT_H_
#define _DEDITOR_POLYGON_EDIT_FILE_IO_CMPT_H_

#include <wxGUI/wxGUI.h>

namespace deditor
{
	namespace polygon_edit
	{
		class StagePanel;

		class FileIOCMPT : public wxgui::AbstractEditCMPT
		{
		public:
			FileIOCMPT(wxWindow* parent, const wxString& name,
				StagePanel* editPanel);

		protected:
			virtual wxSizer* initLayout();

		private:
			void onLoadBackgroundLine(wxCommandEvent& event);
			void onLoadBorderLine(wxCommandEvent& event);

			void onLoadMotoXFile(wxCommandEvent& event);

		private:
			StagePanel* m_editPanel;

			wxTextCtrl* m_currPolylineFilenameText;

		}; // FileIOCMPT
	}
}

#endif // _DEDITOR_POLYGON_EDIT_FILE_IO_CMPT_H_