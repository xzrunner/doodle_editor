#ifndef _GAME_FRUITS_VIEW_STAGE_PANEL_H_
#define _GAME_FRUITS_VIEW_STAGE_PANEL_H_
#include <wx/wx.h>
#include <wx/notebook.h>

namespace GAME_FRUITS
{
	class Object;
	class InterimData;

	namespace VIEW
	{
		class StagePanel : public wxPanel
		{
		public:
			StagePanel(wxWindow* parent);

			void getInterimData(InterimData& interim) const;

		private:
			void initLayout();

			void initTitle(wxSizer* sizer);
			void initTabPages(wxSizer* sizer);

			void onPageChanging(wxNotebookEvent& event);
			void onPageChanged(wxNotebookEvent& event);

		private:
			wxNotebook* m_notebook;

			DECLARE_EVENT_TABLE()

		}; // StagePanel
	}
}

#endif // _GAME_FRUITS_VIEW_STAGE_PANEL_H_