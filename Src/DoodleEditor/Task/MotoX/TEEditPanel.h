#ifndef _DEDITOR_MOTOX_TEMPLATE_EDIT_PANEL_H_
#define _DEDITOR_MOTOX_TEMPLATE_EDIT_PANEL_H_

#include <wxGUI/wxGUI.h>

namespace deditor
{
	namespace motox
	{
		class LibraryTemplateItem;

		class TEEditPanel : public wxgui::EditPanel, public wxgui::SpritesPanelImpl
		{
		public:
			TEEditPanel(wxWindow* parent, wxgui::LibraryPanel* libraryPanel,
				LibraryTemplateItem* templateItem);
			virtual ~TEEditPanel();

			const wxgui::LibraryPanel* getLibraryPanel() const { 
				return m_libraryPanel; 
			}

			void setItemName(const wxString& filename);

		private:
			void load();
			void store();

		private:
			wxgui::LibraryPanel* m_libraryPanel;

			LibraryTemplateItem* m_templateItem;

		}; // TEEditPanel
	}
}

#endif // _DEDITOR_MOTOX_TEMPLATE_EDIT_PANEL_H_