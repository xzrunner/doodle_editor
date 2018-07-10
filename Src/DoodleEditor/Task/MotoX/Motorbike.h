#ifndef _DEDITOR_MOTOX_MOTORBIKE_H_
#define _DEDITOR_MOTOX_MOTORBIKE_H_

#include <wxGUI/wxGUI.h>
#include <Box2D/Box2D.h>

namespace deditor
{
	namespace motox
	{
		class LibraryActorItem;
		struct DriveControl;
		struct ActorSettings;

		class Motorbike
		{
		public:
			Motorbike(b2World* world);
			~Motorbike();

			void loadParts(const LibraryActorItem& params);
			void loadJoints(const LibraryActorItem& params);
			void setCollisionFilter(const b2Filter& filter);

			void driving(const DriveControl& control, ActorSettings& settings);

		private:
			void clear();

		private:
			b2World* m_world;

			wxgui::ISprite *m_frontWheel, *m_backWheel, *m_body;
			b2WheelJoint *m_jointFront, *m_jointBack;

			bool m_bActive;

			friend class Actor;

		}; // Motorbike
	}
}

#endif // _DEDITOR_MOTOX_MOTORBIKE_H_