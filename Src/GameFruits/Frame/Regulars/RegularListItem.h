#ifndef _GAME_FRUITS_REGULAR_LIST_ITEM_H_
#define _GAME_FRUITS_REGULAR_LIST_ITEM_H_
#include "CollapsiblePane.h"
#include <wx/listctrl.h>

namespace GAME_FRUITS
{
	class RegularListItem : public wxListItem
	{
	public:
		RegularListItem(const wxString& name);

		void createPanel(wxWindow* parent);

	protected:
		virtual wxSizer* createExtend(wxWindow* extend) = 0;

	protected:
		static const wxString TIP_DRAG_BEHAVIOR;

		static const wxSize TIP_SIZE;

	protected:
		wxString m_name;

	}; // RegularListItem
}

#endif // _GAME_FRUITS_REGULAR_LIST_ITEM_H_