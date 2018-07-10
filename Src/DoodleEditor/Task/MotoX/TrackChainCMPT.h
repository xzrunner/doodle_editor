#ifndef _DEDITOR_MOTOX_TRACK_CHAIN_CMPT_H_
#define _DEDITOR_MOTOX_TRACK_CHAIN_CMPT_H_

#include <wxGUI/wxGUI.h>

namespace deditor
{
	namespace motox
	{
		class StagePanel;

		class TrackChainCMPT : public wxgui::AbstractEditCMPT
		{
		public:
			TrackChainCMPT(wxWindow* parent, const wxString& name,
				StagePanel* editPanel);

		protected:
			virtual wxSizer* initLayout();

		}; // TrackChainCMPT
	}
}

#endif // _DEDITOR_MOTOX_TRACK_CHAIN_CMPT_H_