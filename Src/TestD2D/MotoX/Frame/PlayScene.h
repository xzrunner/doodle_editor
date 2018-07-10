#ifndef _MOTOX_PLAY_SCENE_H_
#define _MOTOX_PLAY_SCENE_H_

#include "Level/Level.h"
#include "Actor/Actor.h"
#include "Frame/ContactListener.h"

namespace motox
{
	class PlayScene : public d2d::Scene
	{
	public:
		PlayScene(d2d::Game* game, d2d::Context* pContext,
			int scene, int level);
		virtual ~PlayScene();

		virtual void load();
		virtual void draw() const;
		virtual void update();

#ifdef D2D_WINDOWS
		void onKey(int action, int keyCode);
#endif

	private:
		void initDebugDraw();

		bool updateInput();

		void logFrameRate();

	private:
		Level m_level;
		Actor m_actor;

		// Operating
		bool m_keyState[4];

		d2d::b2GLESRender* m_debugDraw;

		ContactListener m_contactListener;

	}; // PlayScene
}

#endif // _MOTOX_PLAY_SCENE_H_