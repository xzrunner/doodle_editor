#ifndef _FEDITOR_MOTOX_MOTORBIKE_H_
#define _FEDITOR_MOTOX_MOTORBIKE_H_
#include <Fruits2D/Fruits2D.h>

class b2World;
class b2WheelJoint;
struct b2Filter;

namespace FEDITOR
{
	class Sprite;
	class Layer;
	class ActorMotionAdapter;

	namespace MOTOX
	{
		struct DriveControl;
		struct ActorSettings;

		class Motorbike
		{
		public:
			Motorbike(b2World* world, Layer* layer);
			~Motorbike();

			void loadFromAdapterFile(const ActorMotionAdapter& adapter);
			void setCollisionFilter(const b2Filter& filter);

			void driving(const DriveControl& control, ActorSettings& settings);

			Sprite* getBody();

		private:
			void clear();

 			void loadPartsFromAdapterFile(const ActorMotionAdapter& adapter);
 			void loadJointsFromAdapterFile();

		private:
			b2World* m_world;
			Layer* m_layer;

			Sprite *m_frontWheel, *m_backWheel, *m_body;
			b2WheelJoint *m_jointFront, *m_jointBack;

			friend class Actor;

		}; // Motorbike

		inline Sprite* Motorbike::getBody()
		{
			return m_body;
		}
	}
}

#endif // _FEDITOR_MOTOX_MOTORBIKE_H_