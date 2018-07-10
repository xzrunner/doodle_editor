#ifndef _MOTOX_MAINSCENE_H_
#define _MOTOX_MAINSCENE_H_

#include <Doodle2D/doodle2d.h>

namespace motox
{
	class MainScene : public d2d::Scene
	{
	public:
		MainScene(d2d::Game* game, d2d::Context* pContext);

		virtual void load();

	}; // MainScene
}

#endif // _MOTOX_MAINSCENE_H_
