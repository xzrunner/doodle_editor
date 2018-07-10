#ifndef _DEDITOR_MOTOX_TILE_IO_CMPT_H_
#define _DEDITOR_MOTOX_TILE_IO_CMPT_H_

#include <wxGUI/wxGUI.h>

namespace deditor
{
	namespace motox
	{
		class Sprite;
		class StagePanel;
		class TileFileAdapter;

		class TileIOCMPT : public wxgui::AbstractEditCMPT
		{
		public:
			TileIOCMPT(wxWindow* parent, const wxString& name,
				StagePanel* editPanel, wxgui::LibraryPanel* libraryPanel);

			static void loadToEditpanel(StagePanel* editPanel, 
				const wxString& filepath);

		protected:
			virtual wxSizer* initLayout();

		private:
			void onLoadText(wxCommandEvent& event);
			void onStoreText(wxCommandEvent& event);
			void onLoadPolygonFillings(wxCommandEvent& event);

			void loadFromTextFile(const wxString& filepath);
			void storeToTextFile(const wxString& filepath) const;
			void loadPolygonFillings(const wxString& filepath);

			void storeToTextFile(std::ofstream& fout, wxgui::ISprite* sprite) const;

			static void loadToEditpanel(StagePanel* editPanel, 
				const TileFileAdapter& adapter);

		private:
			StagePanel* m_editPanel;
			wxgui::LibraryPanel* m_libraryPanel;

			wxCheckBox* m_loadPhysicsCtrl;

			wxTextCtrl* m_currFilenameCtrl;

		}; // TileIOCMPT
	}
}

#endif // _DEDITOR_MOTOX_TILE_IO_CMPT_H_