#ifndef _GAME_FRUITS_VIEW_LIBRARY_PANEL_H_
#define _GAME_FRUITS_VIEW_LIBRARY_PANEL_H_
#include <wx/wx.h>

namespace GAME_FRUITS
{
	namespace VIEW
	{
		class LibraryPanel : public wxPanel
		{
		public:
			LibraryPanel(wxWindow* parent);

		private:
			void initLayout();

			void initTitle(wxSizer* sizer);
			void initTabPages(wxSizer* sizer);

		}; // LibraryPanel
	}
}

#endif // _GAME_FRUITS_VIEW_LIBRARY_PANEL_H_