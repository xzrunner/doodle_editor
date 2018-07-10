#ifndef _DEDITOR_SKATER_STAGE_PANEL_H_
#define _DEDITOR_SKATER_STAGE_PANEL_H_

#include <wxGUI/wxGUI.h>

namespace deditor
{
	namespace skater
	{
		class StagePanel : public wxgui::EditPanel, public wxgui::SpritesPanelImpl, 
			public wxgui::ShapesPanelImpl
		{
		public:
			StagePanel(wxWindow* parent, wxgui::LibraryPanel* libraryPanel);

			//
			// wxgui::SpritesPanelImpl interface
			//
			virtual void insertSprite(wxgui::ISprite* sprite);

			//
			// wxgui::ShapesPanelImpl interface
			//
			virtual void insertShape(wxgui::IShape* shape);

			virtual void clear();

		}; // StagePanel
	}
}

#endif // _DEDITOR_SKATER_STAGE_PANEL_H_