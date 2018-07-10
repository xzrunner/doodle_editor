#ifndef _DEDITOR_MOTOX_LIBRARY_PANEL_H_
#define _DEDITOR_MOTOX_LIBRARY_PANEL_H_

#include <wxGUI/wxGUI.h>

namespace deditor
{
	namespace motox
	{
		class LibraryTemplatePage;
		class LibraryActorPage;

		class LibraryPanel : public wxgui::LibraryPanel
		{
		public:
			static const wxString COMBINATION_LIST_NAME;
			static const wxString TEMPLATE_LIST_NAME;
			static const wxString BREAKABLE_LIST_NAME;
			static const wxString ACTOR_LIST_NAME;

		public:
			LibraryPanel(wxWindow* parent);

			void registerContext(wxgui::PropertySettingPanel* propertyPanel,
				wxgui::EditPanel* editPanel);

		private:
			LibraryTemplatePage* m_templatePage;

			LibraryActorPage* m_actorPage;

		}; // LibraryPanel
	}
}

#endif // _DEDITOR_MOTOX_LIBRARY_PANEL_H_