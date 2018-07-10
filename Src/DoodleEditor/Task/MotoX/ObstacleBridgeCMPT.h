#ifndef _DEDITOR_MOTOX_OBSTACLE_BRIDGE_CMPT_H_
#define _DEDITOR_MOTOX_OBSTACLE_BRIDGE_CMPT_H_

#include <wxGUI/wxGUI.h>

namespace deditor
{
	namespace motox
	{
		class StagePanel;

		class ObstacleBridgeCMPT : public wxgui::AbstractEditCMPT
		{
		public:
			ObstacleBridgeCMPT(wxWindow* parent, const wxString& name,
				StagePanel* editPanel);

			wxgui::ImageSymbol* getTileSymbol() { return m_tile; }

		protected:
			virtual wxSizer* initLayout();

		private:
			void onLoadTileSymbol(wxCommandEvent& event);

		private:
			StagePanel* m_editPanel;

			wxgui::ImageSymbol* m_tile;

			wxTextCtrl* m_currFilenameCtrl;

		}; // ObstacleBridgeCMPT
	}
}

#endif // _DEDITOR_MOTOX_OBSTACLE_BRIDGE_CMPT_H_