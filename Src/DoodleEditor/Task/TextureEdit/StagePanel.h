#ifndef _DEDITOR_TEXTURE_EDIT_STAGE_PANEL_H_
#define _DEDITOR_TEXTURE_EDIT_STAGE_PANEL_H_

#include <wxGUI/wxGUI.h>

namespace deditor
{
	namespace texture_edit
	{
		class StagePanel : public wxgui::EditPanel, public wxgui::ShapesPanelImpl,
			public wxgui::SpritesPanelImpl
		{
		public:
			StagePanel(wxWindow* parent, wxgui::LibraryPanel* libraryPanel);

			//
			// wxgui::ShapesPanelImpl interface
			//
			virtual void clear();

			void loadTexture(const wxString& filePath);
			wxgui::Image* getTexture() const {
				return m_texture;
			}

		private:
			wxgui::Image* m_texture;

		}; // StagePanel
	}
}

#endif // _DEDITOR_TEXTURE_EDIT_STAGE_PANEL_H_