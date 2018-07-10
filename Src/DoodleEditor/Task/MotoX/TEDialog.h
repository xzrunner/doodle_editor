#ifndef _DEDITOR_MOTOX_TEMPLATE_EDIT_DIALOG_H_
#define _DEDITOR_MOTOX_TEMPLATE_EDIT_DIALOG_H_

#include <wxGUI/wxGUI.h>

namespace deditor
{
	namespace motox
	{
		class LibraryTemplateItem;

		class TEDialog : public wxDialog
		{
		public:
			TEDialog(wxWindow* parent, LibraryTemplateItem* templateItem,
				wxgui::PropertySettingPanel* propertyPanel);

		private:
			void onSize(wxSizeEvent& event);

			void initLayout(LibraryTemplateItem* templateItem);

		private:
			wxgui::PropertySettingPanel* m_propertyPanel;

			DECLARE_EVENT_TABLE()

		}; // TEDialog
	}
}

#endif // _DEDITOR_MOTOX_TEMPLATE_EDIT_DIALOG_H_