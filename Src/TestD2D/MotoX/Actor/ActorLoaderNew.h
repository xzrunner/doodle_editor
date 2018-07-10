#ifndef _MOTOX_ACTOR_LOADER_NEW_H_
#define _MOTOX_ACTOR_LOADER_NEW_H_

#include "ActorDefs.h"

#include "Tools/Joint.h"

#include <Doodle2D/doodle2d.h>

namespace motox
{
	class Actor;
	class Motorbike;
	class Player;

	class ActorLoaderNew
	{
	public:
#ifdef D2D_WINDOWS
		ActorLoaderNew(Actor* actor);
#elif defined D2D_ANDROID_NATIVE
		ActorLoaderNew(Actor* actor, android_app* pApplication);
#elif defined D2D_ANDROID_JNI
		ActorLoaderNew(Actor* actor);
#endif

	private:
		void load(const std::string& filepath);

		void loadMergedAndBounding(byte*& ptr);
		void loadPlayerInfo(byte*& ptr);
		void loadMotorbikeInfo(byte*& ptr);

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
		Actor* m_actor;

		b2World* m_world;

		Motorbike* m_bike;
		Player* m_player;

		d2d::Vector m_locations[PLAYER_PARTS_COUNT];
		float m_angles[PLAYER_PARTS_COUNT];

		JointDef m_playerJointDefs[JOINTS_TYPE_COUNT];
		d2d::Vector m_anchors[JOINTS_TYPE_COUNT];

#ifdef D2D_ANDROID_NATIVE
		android_app* m_pApplication;
#endif
	}; // ActorLoaderNew
}

#endif // _MOTOX_ACTOR_LOADER_NEW_H_