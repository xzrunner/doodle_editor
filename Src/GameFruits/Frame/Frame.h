#ifndef _GAME_FRUITS_FRAME_H_
#define _GAME_FRUITS_FRAME_H_
#include <wx/wx.h>

class wxSplitterWindow;

namespace GAME_FRUITS
{
	class Frame : public wxFrame
	{
	public:
		Frame(const wxString& title);

	private:
		void onQuit(wxCommandEvent& event);
		void onPreview(wxCommandEvent& event);
		void onFullScreenStage(wxCommandEvent& event);
		void onAbout(wxCommandEvent& event);

		void initMenuBar();
		wxMenu* initFileBar();
		wxMenu* initViewBar();
		wxMenu* initHelpBar();

		void initWorkingFrame();

	private:
		enum
		{
			myID_MENU_PREVIEW = 1000,
			myID_MENU_FULL
		};

		static const float SASH_GRAVITY_HOR;
		static const float SASH_GRAVITY_VER;

	private:
		wxSplitterWindow* m_splitter;
		wxWindow *m_top, *m_bottom;

		DECLARE_EVENT_TABLE()

	}; // Frame
}

#endif // _GAME_FRUITS_FRAME_H_