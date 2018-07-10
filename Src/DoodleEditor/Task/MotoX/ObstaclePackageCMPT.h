#ifndef _DEDITOR_MOTOX_OBSTACLE_PACKAGE_CMPT_H_
#define _DEDITOR_MOTOX_OBSTACLE_PACKAGE_CMPT_H_

#include "Task/AutomaticMerge/FileAdapter.h"

namespace deditor
{
	namespace motox
	{
		class StagePanel;

		class ObstaclePackageCMPT : public wxgui::AbstractEditCMPT
		{
		public:
			ObstaclePackageCMPT(wxWindow* parent, const wxString& name,
				StagePanel* editPanel);

			static void packageToBin(StagePanel* editPanel, const wxString& src, 
				const wxString& mergeFile, const wxString& dst);

		protected:
			virtual wxSizer* initLayout();

		private:
			void onStoreToBinFile(wxCommandEvent& event);
			void onLoadFromBinFile(wxCommandEvent& event);
			void onLoadMergedFile(wxCommandEvent& event);

		private:
			StagePanel* m_editPanel;

			automatic_merge::FileAdapter m_merged;

		}; // ObstaclePackageCMPT
	}
}

#endif // _DEDITOR_MOTOX_OBSTACLE_PACKAGE_CMPT_H_