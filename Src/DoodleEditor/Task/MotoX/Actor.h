#ifndef _DEDITOR_MOTOX_ACTOR_H_
#define _DEDITOR_MOTOX_ACTOR_H_

#include "ActorSettings.h"

#include <wxGUI/wxGUI.h>
#include <Box2D/Box2D.h>

namespace deditor
{
	namespace motox
	{
		class LibraryActorItem;
//		class Motorbike;
		class MotorbikeNew;
		class Player;

		class Actor
		{
		public:
			enum
			{
				e_SetWheelFriction,
				e_SetMotoDensity,
				e_SetPlayerDensity,
				e_SetSpeed,
				e_SetAcc,
				e_SetTorque,
				e_SetDamping,
				e_SetHz,
				e_SetMaxMotorTorque
			};

		public:
			Actor(b2World* world, const LibraryActorItem& params);
			~Actor();

			void load();

			void driving(bool* keyState);
			void update();

			void setValue(int type, float val);

			void setLocation(const f2Vec2& pos);

			void onDraw() const;

			f2Vec2 getCenterPos() const;

			static void getCollisionFilterSetting(b2Filter& motoFilter, 
				b2Filter& playerCollFilter, b2Filter& playerNoCollFilter);

		private:
			void setCollisionFilter();

		private:
			static const uint16_t DEFAULT_CATEGOTY		= 0x0001;
			static const uint16_t MOTO_CATEGORY			= 0x0002;
			static const uint16_t PLAYER_CATEGORY		= 0x0004;

			static const uint16_t DEFAULT_MASK			= 0xFFFF;
			static const uint16_t MOTO_MASK				= 0xFFFF ^ PLAYER_CATEGORY;
			static const uint16_t PLAYER_MASK			= 0xFFFF ^ MOTO_CATEGORY;

			static const int16_t MOTO_GROUP				= 1;
			static const int16_t PLAYER_GROUP			= -1;

		private:
			const LibraryActorItem& m_params;

			ActorSettings m_settings;

//			Motorbike* m_bike;
			MotorbikeNew* m_bike;
			Player* m_player;

		}; // Actor
	}
}

#endif // _DEDITOR_MOTOX_ACTOR_H_