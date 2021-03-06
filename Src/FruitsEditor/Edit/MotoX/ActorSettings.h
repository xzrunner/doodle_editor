#ifndef _FEDITOR_MOTOX_ACTOR_SETTINGS_H_
#define _FEDITOR_MOTOX_ACTOR_SETTINGS_H_

namespace FEDITOR
{
	namespace MOTOX
	{
		struct ActorSettings
		{
			float maxSpeed;
			float accSpeed;
			float currSpeed;
			long lastTime;

			float angularImpulse;

			ActorSettings();
			
		}; // ActorSettings

		inline ActorSettings::ActorSettings()
		{
			maxSpeed = 20;
			accSpeed = 10;
			currSpeed = 0;
			lastTime = 0;
			
			angularImpulse = 8;
		}
	}
}

#endif // _FEDITOR_MOTOX_ACTOR_SETTINGS_H_