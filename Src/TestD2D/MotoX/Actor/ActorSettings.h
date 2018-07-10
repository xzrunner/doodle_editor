#ifndef _MOTOX_ACTOR_SETTINGS_H_
#define _MOTOX_ACTOR_SETTINGS_H_

#include "Tools/defs.h"

namespace motox
{
	struct ActorSettings
	{
		float maxSpeed;
		float accSpeed;
		float currSpeed;
		float lastTime;

		float angularImpulse;

		ActorSettings();
		
	}; // ActorSettings

	inline ActorSettings::ActorSettings()
	{
		maxSpeed = g_speed;
		accSpeed = g_acceleration;
		currSpeed = 0;
		lastTime = 0;
		
		angularImpulse = g_playerTorque;
	}
}

#endif // _MOTOX_ACTOR_SETTINGS_H_