#ifndef _DEDITOR_MOTOX_TEMPLATE_EDIT_TOOLBAR_H_
#define _DEDITOR_MOTOX_TEMPLATE_EDIT_TOOLBAR_H_

#include <wxGUI/wxGUI.h>

namespace deditor
{
	namespace motox
	{
		class TEEditPanel;

		class TEToolbar : public wxgui::ToolbarPanel
		{
		public:
			TEToolbar(wxWindow* parent, TEEditPanel* editPanel, 
				wxgui::LibraryPanel* libraryPanel,
				wxgui::PropertySettingPanel* propertyPanel);

		protected:
			virtual wxSizer* initLayout();

		private:
			void onLoadText(wxCommandEvent& event);
			void onStoreText(wxCommandEvent& event);

			void loadFromTextFile(const wxString& filepath);
			void storeToTextFile(const wxString& filepath) const;

		private:
			class PasteTileCMPT : public wxgui::AbstractEditCMPT
			{
			public:
				PasteTileCMPT(wxWindow* parent, const wxString& name,
					TEEditPanel* editPanel, wxgui::LibraryPanel* libraryPanel);

			protected:
				virtual wxSizer* initLayout();

			}; // PasteTileCMPT

		private:
			TEEditPanel* m_editPanel;
			wxgui::LibraryPanel* m_libraryPanel;

			wxTextCtrl* m_currFilenameCtrl;

		}; // TEToolbar
	}
}

#endif // _DEDITOR_MOTOX_TEMPLATE_EDIT_TOOLBAR_H_