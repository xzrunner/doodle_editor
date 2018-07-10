#ifndef _FEDITOR_MOTOX_ACTOR_H_
#define _FEDITOR_MOTOX_ACTOR_H_
#include <Fruits2D/Fruits2D.h>
#include "ActorSettings.h"

class b2World;
struct b2Filter;

namespace FEDITOR
{
	class Layer;

	namespace MOTOX
	{
		class Motorbike;
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
			Actor(b2World* world, Layer* layer, const std::string& file);
			~Actor();

			void driving();

			void setValue(int type, float val);

			void translate(const f2Vec2& offset);

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
			ActorSettings m_settings;

			Motorbike* m_bike;
			Player* m_player;

		}; // Actor
	}
}

#endif // _FEDITOR_MOTOX_ACTOR_H_