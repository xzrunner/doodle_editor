#ifndef _DEDITOR_MOTOX_OBSTACLE_SOFT_CMPT_H_
#define _DEDITOR_MOTOX_OBSTACLE_SOFT_CMPT_H_

#include <wxGUI/wxGUI.h>

namespace deditor
{
	namespace motox
	{
		class StagePanel;

		class ObstacleSoftCMPT : public wxgui::AbstractEditCMPT
		{
		public:
			struct SoftSettings
			{
				enum Type
				{
					e_poly,
					e_circle
				};

				Type shape;

				int edge;
				float frequencyHz;
				float dampingRatio;
			};

		public:
			ObstacleSoftCMPT(wxWindow* parent, const wxString& name,
				StagePanel* editPanel, wxgui::LibraryPanel* libraryPanel);

			void getSettings(SoftSettings& settings) const;

		protected:
			virtual wxSizer* initLayout();

		private:
			StagePanel* m_editPanel;

			wxRadioBox* m_shapeChoice;

			wxSpinCtrl* m_edgeCtrl;
			wxSpinCtrl* m_frequencyHzCtrl;
			wxSpinCtrl* m_dampingRatioCtrl;

		}; // ObstacleSoftCMPT
	}
}

#endif // _DEDITOR_MOTOX_OBSTACLE_SOFT_CMPT_H_