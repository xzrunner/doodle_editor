#ifndef _GAME_FRUITS_VIEW_LIBRARY_PAGE_BASE_H_
#define _GAME_FRUITS_VIEW_LIBRARY_PAGE_BASE_H_
#include <wx/wx.h>
#include <Fruits2D/Fruits2D.h>

class wxListCtrl;

namespace GAME_FRUITS
{
	namespace VIEW
	{
		class LibraryPageBase : public wxWindow
		{
		public:
			LibraryPageBase(wxWindow* parent);

			void registerListener(wxChoice* lsn);

		protected:
			void updateListeners();

		private:
			void initLayout();

			void getAllItemsText(std::vector<wxString>& items) const;
			void update(wxChoice* list, const std::vector<wxString>& items);

		protected:
			wxButton *m_add, *m_del;
 
			wxListCtrl* m_listCtrl;

			std::vector<wxChoice*> m_listeners;

		}; // LibraryPageBase
	}
}

#endif // _GAME_FRUITS_VIEW_LIBRARY_PAGE_BASE_H_