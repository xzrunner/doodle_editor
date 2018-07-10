#ifndef _DEDITOR_MOTOX_TILE_EDIT_CMPT_H_
#define _DEDITOR_MOTOX_TILE_EDIT_CMPT_H_

#include <wxGUI/wxGUI.h>

namespace deditor
{
	namespace motox
	{
		class StagePanel;
		class LibraryCombinationList;
		class LibraryTemplateList;

		class TileEditCMPT : public wxgui::AbstractEditCMPT
		{
		public:
			TileEditCMPT(wxWindow* parent, const wxString& name,
				wxgui::LibraryPanel* libraryPanel,
				wxgui::PropertySettingPanel* propertyPanel, 
				StagePanel* editPanel);
			virtual ~TileEditCMPT();

			wxgui::LayersMgrWidget* getLayersMgr() {
				return m_layersMgr; 
			}

		protected:
			virtual wxSizer* initLayout();

		private:
			StagePanel* m_editPanel;

			wxgui::LayersMgrWidget* m_layersMgr;

		}; // TileEditCMPT
	}
}

#endif // _DEDITOR_MOTOX_TILE_EDIT_CMPT_H_