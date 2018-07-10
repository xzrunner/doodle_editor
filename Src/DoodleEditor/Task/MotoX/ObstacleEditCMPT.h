#ifndef _DEDITOR_MOTOX_OBSTACLE_EDIT_CMPT_H_
#define _DEDITOR_MOTOX_OBSTACLE_EDIT_CMPT_H_

#include <wxGUI/wxGUI.h>

namespace deditor
{
	namespace motox
	{
		class StagePanel;

		class ObstacleEditCMPT : public wxgui::AbstractEditCMPT
		{
		public:
			ObstacleEditCMPT(wxWindow* parent, const wxString& name,
				StagePanel* editPanel, wxgui::LibraryPanel* libraryPanel,
				wxgui::PropertySettingPanel* propertyPanel);

			static void loadToEditpanel(StagePanel* editPanel,
				const wxString& filepath);

		public:
			static const wxString OBSTACLE_FILE_TAG;

		protected:
			virtual wxSizer* initLayout();

		private:
			void onLoadText(wxCommandEvent& event);
			void onStoreText(wxCommandEvent& event);

			void loadFromTextFile(const wxString& filepath);
			void storeToTextFile(const wxString& filepath) const;

		private:
			enum ObstacleType
			{
				e_common = 0,
				e_bridge,
				e_soft,
				e_breakable
			};

		private:
			wxgui::LibraryPanel* m_libraryPanel;

		}; // ObstacleEditCMPT
	}
}

#endif // _DEDITOR_MOTOX_OBSTACLE_EDIT_CMPT_H_