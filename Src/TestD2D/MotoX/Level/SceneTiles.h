#ifndef _MOTOX_SCENE_TILES_H_
#define _MOTOX_SCENE_TILES_H_

#include "SpriteGridLoader.h"

namespace motox
{
	class SceneTiles
	{
	public:
		SceneTiles(d2d::Context* pContext,
			int scene, int level);

		void draw() const;
		void update(const d2d::Vector& center);

	private:
		void initTextureInfo(d2d::Context* pContext);

		void loadTilesInfo(const std::vector<SpriteGridLoader::Entry*>& tiles,
			size_t& verticesBase, size_t& indicesBase);

	private:
		static const int VERTICES_SIZE = 2000;

	private:
		SpriteGridLoader m_loader;

		d2d::TextureInfo m_texInfo;

		size_t m_leftGridID, m_rightGridID;

		float m_vertices[VERTICES_SIZE * 2];
		float m_texCoords[VERTICES_SIZE * 2];
		unsigned short m_indices[VERTICES_SIZE / 2 * 3];

		size_t m_indicesSize;

	}; // SceneTiles
}

#endif // _MOTOX_SCENE_TILES_H_