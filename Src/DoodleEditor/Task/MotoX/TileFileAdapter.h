#ifndef _DEDITOR_MOTOX_TILE_FILE_ADAPTER_H_
#define _DEDITOR_MOTOX_TILE_FILE_ADAPTER_H_

#include <wxGUI/wxGUI.h>

namespace deditor
{
	namespace motox
	{
		class TileFileAdapter
		{
		public:
			enum Type
			{
				e_image = 0,
				e_physics,
				e_physics_reverse,
				e_physics_static,
				e_physics_reverse_static,
			};

		public:
			TileFileAdapter();
			TileFileAdapter(b2World* world, b2World* worldReverse);
			~TileFileAdapter();

			void resolve(const wxString& filepath);

		public:
			struct Layer
			{
				wxString name;
				std::vector<wxgui::ISprite*> sprites;

				~Layer() {
					for (size_t i = 0, n = sprites.size(); i < n; ++i)
						sprites[i]->release();
					sprites.clear();
				}
			};

		private:
			struct SpriteDef
			{
				f2Vec2 pos;
				float angle;
				float scale;
				int type;
				bool xMirror, yMirror;
			};

		private:
			void resolveShapeSprite(const std::string& filename, 
				const SpriteDef& def, wxgui::ISprite*& sprite);
			void resolveImageSprite(const std::string& filename, 
				const SpriteDef& def, wxgui::ISprite*& sprite);

		public:
			std::vector<Layer*> m_layers;

		private:
			b2World *m_world, *m_worldReverse;

		}; // TileFileAdapter
	}
}

#endif // _DEDITOR_MOTOX_TILE_FILE_ADAPTER_H_