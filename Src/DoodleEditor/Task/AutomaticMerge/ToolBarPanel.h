#ifndef _DEDITOR_AUTOMATIC_MERGE_TOOLBAR_PANEL_H_
#define _DEDITOR_AUTOMATIC_MERGE_TOOLBAR_PANEL_H_

#include <wxGUI/wxGUI.h>

namespace deditor
{
	namespace automatic_merge
	{
		class StagePanel;

		class ToolbarPanel : public wxgui::ToolbarPanel
		{
		public:
			enum IMG_TYPE
			{
				e_bmp,
				e_jpg,
				e_png
			};

		public:
			ToolbarPanel(wxWindow* parent, StagePanel* stagePanel);

			IMG_TYPE getImgType() const;

		protected:
			virtual wxSizer* initLayout();

		private:
			void initSizeSettingPanel(wxSizer* topSizer);
			void initFormatChoicePanel(wxSizer* topSizer);
			void initRearrangePanel(wxSizer* topSizer);
			void initLoadListPanel(wxSizer* topSizer);
			void initPackagePanel(wxSizer* topSizer);

			void onChangeOutputImageSize(wxCommandEvent& event);
			void onRearrange(wxCommandEvent& event);
			void onLoadLibraryList(wxCommandEvent& event);
			void onPackageOutput(wxCommandEvent& event);

		private:
			static const int BASE_EDGE = 32;
			static const int TOTLE_EDGE_TYPES = 6;

		private:
			wxChoice *m_widthChoice, *m_heightChoice;
			wxRadioBox* m_formatChoice;

			wxCheckBox* m_boundCheck;

		}; // ToolbarPanel
	}
}

#endif // _DEDITOR_AUTOMATIC_MERGE_TOOLBAR_PANEL_H_