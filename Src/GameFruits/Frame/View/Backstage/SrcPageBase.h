#ifndef _GAME_FRUITS_VIEW_BACKSTAGE_SRC_PAGE_BASE_H_
#define _GAME_FRUITS_VIEW_BACKSTAGE_SRC_PAGE_BASE_H_
#include <wx/wx.h>
#include <wx/listctrl.h>
#include <wx/dnd.h>

namespace GAME_FRUITS
{
	namespace VIEW
	{
		namespace BACKSTAGE
		{
			class SrcPageBase : public wxListCtrl
			{
			public:
				SrcPageBase(wxWindow* parent);

			protected:
				virtual void initFunctions() = 0;

			}; // SrcPageBase

			inline SrcPageBase::SrcPageBase(wxWindow* parent)
				: wxListCtrl(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_LIST)
			{
				SetBackgroundColour(wxColour("#dfdfdf"));
			}
		}
	}
}

#endif // _GAME_FRUITS_VIEW_BACKSTAGE_SRC_PAGE_BASE_H_