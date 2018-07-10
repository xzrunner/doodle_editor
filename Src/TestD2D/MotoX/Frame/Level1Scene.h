#ifndef _MOTOX_LEVEL1SCENE_H_
#define _MOTOX_LEVEL1SCENE_H_

#include <Doodle2D/doodle2d.h>

namespace motox
{
	class Level1Scene : public d2d::Scene
	{
	public:
		Level1Scene(d2d::Game* game, d2d::Context* pContext);

		virtual void load();

	}; // Level1Scene
}

#endif // _MOTOX_LEVEL1SCENE_H_
