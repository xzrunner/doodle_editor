//#ifndef _MOTOX_ACTOR_LOADER_H_
//#define _MOTOX_ACTOR_LOADER_H_
//
//#include <Doodle2D/doodle2d.h>
//
//namespace motox
//{
//	class Actor;
//	class Motorbike;
//	class Player;
//
//	class ActorLoader
//	{
//	public:
//#ifdef D2D_WINDOWS
//		ActorLoader(Actor* actor);
//#elif defined D2D_ANDROID_NATIVE
//		ActorLoader(Actor* actor, android_app* pApplication);
//#elif defined D2D_ANDROID_JNI
//		ActorLoader(Actor* actor);
//#endif
//
//	private:
//		void load(const std::string& filepath);
//
//		void loadGraphicsAndBodies(byte** ptr);
//		void loadMotionParams(byte** ptr);
//
//		void setCollisionFilter();
//
//		void createMorotbikeJoints();
//		void createPlayerJoints(byte** ptr);
//
//		void createTireTeeth(b2Body* body, float radius);
//
//	private:
//		static const uint16_t DEFAULT_CATEGOTY		= 0x0001;
//		static const uint16_t MOTO_CATEGORY			= 0x0002;
//		static const uint16_t PLAYER_CATEGORY		= 0x0004;
//
//		static const uint16_t DEFAULT_MASK			= 0xFFFF;
//		static const uint16_t MOTO_MASK				= 0xFFFF ^ PLAYER_CATEGORY;
//		static const uint16_t PLAYER_MASK			= 0xFFFF ^ MOTO_CATEGORY;
//
//		static const int16_t MOTO_GROUP				= 1;
//		static const int16_t PLAYER_GROUP			= -1;
//
//	private:
//		Actor* m_actor;
//
//		b2World* m_world;
//
//		Motorbike* m_bike;
//		Player* m_player;
//
//#ifdef D2D_ANDROID_NATIVE
//		android_app* m_pApplication;
//#endif
//	}; // ActorLoader
//}
//
//#endif // _MOTOX_ACTOR_LOADER_H_