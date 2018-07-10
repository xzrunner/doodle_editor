#ifndef _MOTOX_LEVEL_H_
#define _MOTOX_LEVEL_H_

#include <Doodle2D/doodle2d.h>

#ifdef D2D_ANDROID_NATIVE
class android_app;
#endif

namespace motox
{
	class ContactListener;
	class Background;
	class TrackChains;
	class GroundSurface;
	class SceneTiles;
	class SceneObstacles3;

	class Level
	{
	public:
		Level(d2d::Context* pContext, int scene, int level,
			ContactListener& contactListener);
		~Level();

		void load();
		void update(const d2d::Vector& center);
		void draw() const;

		d2d::Vector getActorStartPos() const;

	private:
		void loadGround();

	private:
		d2d::Context* m_pContext;

		int m_scene, m_level;

		ContactListener& m_contactListener;

		Background* m_background;
		TrackChains* m_track;
		GroundSurface* m_surface;
		SceneTiles* m_tiles;
		SceneObstacles3* m_obstacles;

	}; // Level
}

#endif // _MOTOX_LEVEL_H_