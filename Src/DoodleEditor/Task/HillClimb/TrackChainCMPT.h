#ifndef _DEDITOR_HILL_CLIMB_TRACK_CHAIN_CMPT_H_
#define _DEDITOR_HILL_CLIMB_TRACK_CHAIN_CMPT_H_

#include <wxGUI/wxGUI.h>

namespace deditor
{
	namespace hill_climb
	{
		class StagePanel;

		class TrackChainCMPT : public wxgui::AbstractEditCMPT
		{
		public:
			TrackChainCMPT(wxWindow* parent, const wxString& name,
				StagePanel* editPanel);

		protected:
			virtual wxSizer* initLayout();

		private:
			void onLoadPhysicsText(wxCommandEvent& event);
			void onStorePhysicsText(wxCommandEvent& event);
			void onStoreRenderText(wxCommandEvent& event);

			void loadFromPhysicsTextFile(const wxString& filepath);
			void storeToPhysicsTextFile(const wxString& filepath) const;
			void storeToRenderTextFile(const wxString& filepath) const;

		}; // TrackChainCMPT
	}
}

#endif // _DEDITOR_HILL_CLIMB_TRACK_CHAIN_CMPT_H_