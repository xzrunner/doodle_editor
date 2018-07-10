//#ifndef _D2D_PHYSICS_TARGET_H_
//#define _D2D_PHYSICS_TARGET_H_
//
//#include "common/Vector.h"
//
//#include <boost/shared_ptr.hpp>
//#include <Box2D/Box2D.h>
//
//namespace d2d
//{
//	class PhysicsTarget
//	{
//	public:
//		typedef boost::shared_ptr<PhysicsTarget> ptr;
//		
//	public:
//		PhysicsTarget(b2World* pWorld, b2Body* pBodyObj, Vector& pTarget, float pFactor);
//
//		void setTarget(float pX, float pY);
//		
//	private:
//		b2MouseJoint* m_mouseJoint;
//		float m_factor; Vector& m_target;
//
//	}; // PhysicsTarget
//}
//
//#endif // _D2D_PHYSICS_TARGET_H_