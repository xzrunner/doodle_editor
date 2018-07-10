#ifndef _DEDITOR_MOTOX_OBSTACLE_PACKAGE2_CMPT_H_
#define _DEDITOR_MOTOX_OBSTACLE_PACKAGE2_CMPT_H_

#include "Task/AutomaticMerge/FileAdapter.h"

namespace deditor
{
	namespace motox
	{
		class StagePanel;

		class ObstaclePackage2CMPT : public wxgui::AbstractEditCMPT
		{
		public:
			ObstaclePackage2CMPT(wxWindow* parent, const wxString& name,
				StagePanel* editPanel);

			static void packageToBin(StagePanel* editPanel, const wxString& src, 
				const wxString& mergeFile, const std::vector<wxString>& obstacleFiles, 
				const wxString& dst);

		protected:
			virtual wxSizer* initLayout();

		private:
			void onStoreToBinFile(wxCommandEvent& event);
			void onLoadFromBinFile(wxCommandEvent& event);
			void onLoadMergedFile(wxCommandEvent& event);

			static void storeToBinFile(StagePanel* editPanel, const automatic_merge::FileAdapter& merged,
				const std::vector<wxString>& obstacleFiles, const wxString& filepath);

		private:
			class SpriteCmp
			{
			public:
				bool operator() (const wxgui::ISprite* s0, const wxgui::ISprite* s1) const {
					return s0->getPosition().x < s1->getPosition().x;
				}
			}; // SpriteCmp

		private:
			static const int SPRITE_X_MIRROR = 0x1;
			static const int SPRITE_Y_MIRROR = 0x2;

		private:
			StagePanel* m_editPanel;

			automatic_merge::FileAdapter m_merged;

		}; // ObstaclePackage2CMPT
	}
}

#endif // _DEDITOR_MOTOX_OBSTACLE_PACKAGE2_CMPT_H_