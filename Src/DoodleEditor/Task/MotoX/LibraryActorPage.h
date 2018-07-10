#ifndef _DEDITOR_MOTOX_LIBRARY_ACTOR_PAGE_H_
#define _DEDITOR_MOTOX_LIBRARY_ACTOR_PAGE_H_

#include <wxGUI/wxGUI.h>

namespace deditor
{
	namespace motox
	{
		class LibraryActorPage : public wxgui::ILibraryPage
		{
		public:
			LibraryActorPage(wxWindow* parent);

			virtual bool isHandleSymbol(wxgui::ISymbol* symbol) const;

			void registerContext(wxgui::PropertySettingPanel* propertyPanel,
				wxgui::EditPanel* editPanel);

		protected:
			virtual void initLayout(bool draggable = true);

			virtual void onAddPress(wxCommandEvent& event);

		private:
			void onNewBtnPress(wxCommandEvent& event);

		private:
			wxgui::EditPanel* m_editPanel;

			wxgui::PropertySettingPanel* m_propertyPanel;

		}; // LibraryActorPage
	}
}

#endif // _DEDITOR_MOTOX_LIBRARY_ACTOR_PAGE_H_