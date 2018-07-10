#ifndef _FEDITOR_MOTOX_LEVEL_SPRITES_ADAPTER_H_
#define _FEDITOR_MOTOX_LEVEL_SPRITES_ADAPTER_H_
#include "TextFileAdapter.h"

namespace FEDITOR
{
	class MotoXLevelSpritesAdapter : public TextFileAdapter
	{
	public:
		~MotoXLevelSpritesAdapter();

		virtual void load(const std::string& filename);

	public:
		struct Sprite
		{
			std::string filename;
			f2Vec2 position;
			float angle;
			float xScale, yScale;
			int worldID;

			void load(std::ifstream& fin);

		}; // Sprite

		struct Layer
		{
			std::vector<Sprite*> sprites;

			~Layer();

			void load(std::ifstream& fin);

		}; // Layer

	public:
		std::vector<Layer*> m_layers;

	}; // TextFileAdapter
}

#endif // _FEDITOR_MOTOX_LEVEL_SPRITES_ADAPTER_H_