#ifndef _DEDITOR_HILL_CLIMB_TILE_FILE_ADAPTER_H_
#define _DEDITOR_HILL_CLIMB_TILE_FILE_ADAPTER_H_

#include <wxGUI/wxGUI.h>

namespace deditor
{
	namespace hill_climb
	{
		class TileFileAdapter
		{
		public:
			~TileFileAdapter();

			void resolve(const wxString& filepath);

		public:
			std::vector<wxgui::ISprite*> m_sprites;

		}; // TileFileAdapter
	}
}

#endif // _DEDITOR_HILL_CLIMB_TILE_FILE_ADAPTER_H_