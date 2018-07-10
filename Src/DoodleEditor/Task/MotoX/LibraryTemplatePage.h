#ifndef _DEDITOR_MOTOX_LIBRARY_TEMPLATE_PAGE_H_
#define _DEDITOR_MOTOX_LIBRARY_TEMPLATE_PAGE_H_

#include <wxGUI/wxGUI.h>

namespace deditor
{
	namespace motox
	{
		class LibraryTemplatePage : public wxgui::ILibraryPage
		{
		public:
			LibraryTemplatePage(wxWindow* parent);

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

		}; // LibraryTemplatePage
	}
}

#endif // _DEDITOR_MOTOX_LIBRARY_TEMPLATE_PAGE_H_