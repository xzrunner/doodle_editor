#ifndef _DEDITOR_MOTOX_MOTORBIKE_NEW_H_
#define _DEDITOR_MOTOX_MOTORBIKE_NEW_H_

#include <wxGUI/wxGUI.h>
#include <Box2D/Box2D.h>

namespace deditor
{
	namespace motox
	{
		struct DriveControl;
		struct ActorSettings;

		class MotorbikeNew
		{
		public:
			MotorbikeNew(b2World* world);
			~MotorbikeNew();

			void loadFromFile(const wxString& filepath);
			void active();

			void setCollisionFilter(const b2Filter& filter);

			void driving(const DriveControl& control, ActorSettings& settings);

			void updateFrontDamping();

		private:
			void clear();

		private:
			b2World* m_world;

			wxgui::ISprite *m_frontWheel, *m_backWheel, *m_body,
				*m_frontDamping, *m_backDamping;

			b2WheelJoint* m_frontJoint;
//			b2RevoluteJoint* m_backJoint;
			b2WheelJoint* m_backJoint;

			// frontDamping - body
			float m_delta;
			f2Vec2 m_offset;

			bool m_bActive;

			friend class Actor;

		}; // MotorbikeNew
	}
}

#endif // _DEDITOR_MOTOX_MOTORBIKE_NEW_H_