#ifndef _DEDITOR_HILL_CLIMB_TRACK_SURFACE_CMPT_H_
#define _DEDITOR_HILL_CLIMB_TRACK_SURFACE_CMPT_H_

#include <wxGUI/wxGUI.h>

namespace deditor
{
	namespace hill_climb
	{
		class StagePanel;
		class TrackSurfaceData;

		class TrackSurfaceCMPT : public wxgui::AbstractEditCMPT
		{
		public:
			TrackSurfaceCMPT(wxWindow* parent, const wxString& name,
				StagePanel* editPanel);

		protected:
			virtual wxSizer* initLayout();

		private:
			void onLoadTexture(wxCommandEvent& event); 
			void onStoreText(wxCommandEvent& event);

			void storeToTextFile(const wxString& filepath) const;

			void createTrackTexture(wxgui::Image* image);
			void createTrackTexture(const std::vector<f2Vec2>& ctlpos, TrackSurfaceData& result);
			void createTrackTexture(const std::vector<f2Vec2>& ctlpos, TrackSurfaceData& result, float rOffset);

		private:
			wxSlider* m_offsetSlider;

		}; // TrackSurfaceCMPT
	}
}

#endif // _DEDITOR_HILL_CLIMB_TRACK_SURFACE_CMPT_H_