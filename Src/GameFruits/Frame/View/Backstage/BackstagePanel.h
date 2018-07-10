#ifndef _GAME_FRUITS_VIEW_BACKSTAGE_PANEL_H_
#define _GAME_FRUITS_VIEW_BACKSTAGE_PANEL_H_
#include <wx/wx.h>

namespace GAME_FRUITS
{
	namespace VIEW
	{
		class BackstagePanel : public wxPanel
		{
		public:
			BackstagePanel(wxWindow* parent);

		private:
			void initLayout();

			void initTitle(wxSizer* sizer);
			void initSplitterWindow(wxSizer* sizer);

		private:
			static const float SASH_GRAVITY_HOR;

		}; // BackstagePanel
	}
}

#endif // _GAME_FRUITS_VIEW_BACKSTAGE_PANEL_H_