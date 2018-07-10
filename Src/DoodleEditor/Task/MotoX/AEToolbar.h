#ifndef _DEDITOR_MOTOX_ACTOR_EDIT_TOOLBAR_H_
#define _DEDITOR_MOTOX_ACTOR_EDIT_TOOLBAR_H_

#include <wxGUI/wxGUI.h>

namespace deditor
{
	namespace motox
	{
		class AEEditPanel;

		class AEToolbar : public wxgui::ToolbarPanel
		{
		public:
			AEToolbar(wxWindow* parent, AEEditPanel* editPanel,
				wxgui::LibraryPanel* libraryPanel,
				wxgui::PropertySettingPanel* propertyPanel);

		protected:
			virtual wxSizer* initLayout();

		private:
			wxSizer* initIOPanel();

			void onOpen(wxCommandEvent& event);
			void onSave(wxCommandEvent& event);
			void onBinaryPackage(wxCommandEvent& event);

		private:
 			wxgui::LibraryPanel* m_libraryPanel;

		}; // AEToolbar
	}
}

#endif // _DEDITOR_MOTOX_ACTOR_EDIT_TOOLBAR_H_