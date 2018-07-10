#ifndef _MOTOX_BREAKABLE_SPRITE_H_
#define _MOTOX_BREAKABLE_SPRITE_H_

#include "CombinationSprite.h"

namespace motox
{
	class ObstaclesInfoLoader;

	class BreakableSprite : public CombinationSprite
	{
	public:
		BreakableSprite(b2World* world, const d2d::TextureInfo& texInfo,
			ObstaclesInfoLoader& obstaclesInfo, int meshCombinationID);
		virtual ~BreakableSprite();

		void breakToPieces(const d2d::Vector& pos, std::vector<IObstacleSprite*>& pieces);

		void setBreakType(bool canBreakToCommon) {
			m_canBreakToCommon = canBreakToCommon;
		}

	private:
		void breakToCommon(std::vector<IObstacleSprite*>& pieces);
		void breakToMeshes(const d2d::Vector& pos, std::vector<IObstacleSprite*>& pieces);

		IObstacleSprite* combineMeshes(const std::vector<Part*>& pieces);

		void initPartPhysics(IObstacleSprite* part, const d2d::Vector& offset, 
			float delta, bool isPiece) const;

	private:
		b2World* m_world;

		const d2d::TextureInfo& m_textureInfo;
		ObstaclesInfoLoader& m_obstaclesInfo;

		int m_meshCombinationID;

		bool m_canBreakToCommon;

	}; // BreakableSprite
}

#endif // _MOTOX_BREAKABLE_SPRITE_H_