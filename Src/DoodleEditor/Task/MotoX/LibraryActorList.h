#ifndef _DEDITOR_MOTOX_LIBRARY_SYMBOL_LIST_H_
#define _DEDITOR_MOTOX_LIBRARY_SYMBOL_LIST_H_

#include <wxGUI/wxGUI.h>

namespace deditor
{
	namespace motox
	{
		class LibraryActorList : public wxgui::LibraryList
		{
		public:
			LibraryActorList(wxWindow* parent);

			virtual void onListDoubleClicked(wxCommandEvent& event);

			void registerContext(wxgui::PropertySettingPanel* propertyPanel,
				wxgui::EditPanel* editPanel) {
				m_propertyPanel = propertyPanel;
				m_editPanel = editPanel;
			}

		private:
			wxgui::EditPanel* m_editPanel;

			wxgui::PropertySettingPanel* m_propertyPanel;

		}; // LibraryActorList
	}
}

#endif // _DEDITOR_MOTOX_LIBRARY_SYMBOL_LIST_H_