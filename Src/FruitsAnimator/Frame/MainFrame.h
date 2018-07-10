#ifndef _FRUITS_ANIMATOR_MAIN_FRAME_H_
#define _FRUITS_ANIMATOR_MAIN_FRAME_H_
#include <wx/wx.h>
#include "View/Utility.h"

class wxSplitterWindow;

namespace FRUITS_ANIMATOR
{
	class LibraryPanel;
	class TimeLinePanel;
	class StagePanel;

	class MainFrame : public wxFrame
	{
	public:
		MainFrame(const wxString& title);

	private:
		void onNew(wxCommandEvent& event);
		void onOpen(wxCommandEvent& event);
		void onSave(wxCommandEvent& event);
		void onSaveAs(wxCommandEvent& event);

		void onQuit(wxCommandEvent& event);
		void onAbout(wxCommandEvent& event);
// 		void onSetLanguageCN(wxCommandEvent& event);
// 		void onSetLanguageEN(wxCommandEvent& event);
		void onPreview(wxCommandEvent& event);

		void initMenuBar();
		wxMenu* initFileBar();
		wxMenu* initViewBar();
		wxMenu* initHelpBar();

		void initWorkingFrame();

		void clear();
		void refresh();

		void setCurrFilename();

	private:
		static const float SASH_GRAVITY_HOR;
		static const float SASH_GRAVITY_VERT;

		enum
		{
			Menu_LanguageSetting,
			Menu_LanguageChinese,
			Menu_LanguageEnglish,
			Menu_Preview
		};

		static LanguageEntry entries[];

	private:
		LibraryPanel* m_libraryPanel;
		TimeLinePanel* m_timeLinePanel;
		StagePanel* m_stagePanel;

		std::string m_currFilename;

		DECLARE_EVENT_TABLE()

	}; // MainFrame
}

#endif // _FRUITS_ANIMATOR_MAIN_FRAME_H_