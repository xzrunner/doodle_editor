#ifndef _MOTOX_MOTORBIKE_H_
#define _MOTOX_MOTORBIKE_H_

#include <Doodle2D/doodle2d.h>
#include <Box2D/Box2D.h>

namespace motox
{
	class Sprite;
	struct DriveControl;
	struct ActorSettings;

	class Motorbike
	{
	public:
		Motorbike(d2d::Context* pContext);
		~Motorbike();

		void update();

		void driving(const DriveControl& control, ActorSettings& settings);

	private:
		void clear();

		void updateDamping();

	private:
		d2d::Context* m_pContext;

		Sprite *m_backWheel, *m_frontWheel, *m_body,
			*m_backDamping, *m_frontDamping;

		b2WheelJoint* m_frontJoint;
		b2WheelJoint* m_backJoint;
//		b2RevoluteJoint* m_backJoint;
		b2Joint *m_joint3, *m_joint4;

		// frontDamping - body
		float m_frontDelta;
		d2d::Vector m_frontOffset; 
		// backDamping - body
		d2d::Vector m_backDampingLocal;
		d2d::Vector m_backBodyLocal;

		friend class Actor;
		friend class ActorLoaderNew;

	}; // Motorbike
}

#endif // _MOTOX_MOTORBIKE_H_