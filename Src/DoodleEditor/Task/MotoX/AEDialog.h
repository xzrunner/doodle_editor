#ifndef _DEDITOR_MOTOX_ACTOR_EDIT_DIALOG_H_
#define _DEDITOR_MOTOX_ACTOR_EDIT_DIALOG_H_

#include <wxGUI/wxGUI.h>

namespace deditor
{
	namespace motox
	{
		class LibraryActorItem;
		class AEEditPanel;

		class AEDialog : public wxDialog
		{
		public:
			AEDialog(wxWindow* parent, LibraryActorItem* params,
				wxgui::PropertySettingPanel* propertyPanel);
			virtual ~AEDialog();

		private:
			void onSize(wxSizeEvent& event);

			void initLayout();

		private:
			LibraryActorItem* m_params;

			AEEditPanel* m_editPanel;

			wxgui::PropertySettingPanel* m_propertyPanel;

			DECLARE_EVENT_TABLE()

		}; // AEDialog
	}
}

#endif // _DEDITOR_MOTOX_ACTOR_EDIT_DIALOG_H_