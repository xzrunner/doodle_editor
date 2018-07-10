#ifndef _EASY_BUILDER_PREVIEW_PANEL_H_
#define _EASY_BUILDER_PREVIEW_PANEL_H_

#include <wxGUI/wxGUI.h>

namespace ebuilder
{
	class LibraryPanel;

	namespace preview
	{
		class Canvas;
		class Scene;

		class Panel : public wxgui::EditPanel
		{
		public:
			Panel(wxWindow* parent, LibraryPanel* libraryPanel);
			virtual ~Panel();

			Canvas* getCanvas() {
				return m_canvas;
			}

			Scene* getScene() const;
			void setScene(Scene* scene);

		private:
			class MouseActionOP : public wxgui::AbstractEditOP
			{
			public:
				MouseActionOP(Panel* panel);

				virtual bool onMouseLeftDown(int x, int y);
				virtual bool onMouseLeftUp(int x, int y);

			private:
				Panel* m_panel;

			}; // MouseActionOP

		private:
			Canvas* m_canvas;

			Scene* m_scene;

		}; // Panel
	}
}

#endif // _EASY_BUILDER_PREVIEW_PANEL_H_