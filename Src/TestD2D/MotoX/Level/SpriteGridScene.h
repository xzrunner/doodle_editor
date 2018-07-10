#ifndef _MOTOX_SPRITE_GRID_SCENE_H_
#define _MOTOX_SPRITE_GRID_SCENE_H_

#include "SpriteGridLoader.h"

namespace motox
{
	class SpriteGridScene
	{
	public:
		static void updateGridRegionSingleLayer(const d2d::Vector& center, 
			const SpriteGridLoader& loader, int& left, int& right);

		static void updateGridRegionMultiLayers(const d2d::Vector& center, 
			const SpriteGridLoader& loader, int& left, int& right);

	private:
		static void combine(const SpriteGridLoader::Grids& internal, 
			const SpriteGridLoader::Grids& intersect, int& left, int& right);

	}; // SpriteGridScene
}

#endif // _MOTOX_SPRITE_GRID_SCENE_H_