#ifndef _GAME_FRUITS_VIEW_LIBRARY_GAME_PAGE_H_
#define _GAME_FRUITS_VIEW_LIBRARY_GAME_PAGE_H_
#include <wx/wx.h>

namespace GAME_FRUITS
{
	namespace VIEW
	{
		namespace LIBRARY
		{
			class GamePage : public wxPanel
			{
			public:
				GamePage(wxWindow* parent);

				void setName(const wxString& name);

			private:
				void initLayout();

			private:
				wxTextCtrl* m_name;

			}; // GamePage 
		}
	}
}

#endif // _GAME_FRUITS_VIEW_LIBRARY_GAME_PAGE_H_