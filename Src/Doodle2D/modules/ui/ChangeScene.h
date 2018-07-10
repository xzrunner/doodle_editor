#ifndef _D2D_CHANGE_SCENE_H_
#define _D2D_CHANGE_SCENE_H_

#include "Behavior.h"

namespace d2d
{
	class Game;
	class Scene;

	class ChangeScene : public Behavior
	{
	public:
		ChangeScene(Game* game, Scene* scene);

		virtual void trigger();

	private:
		Game* m_game;

		Scene* m_scene;

	}; // ChangeScene
}

#endif // _D2D_CHANGE_SCENE_H_