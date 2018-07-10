//#ifndef _D2D_PHYSICS_OBJECT_H_
//#define _D2D_PHYSICS_OBJECT_H_
//
//#include "PhysicsTarget.h"
//
//#include "common/types.h"
//
//#include <boost/smart_ptr.hpp>
//#include <Box2D/Box2D.h>
//#include <vector>
//
//namespace d2d
//{
//	class PhysicsObject
//	{
//	public:
//		typedef boost::shared_ptr<PhysicsObject> ptr;
//		typedef std::vector<ptr> vec; typedef vec::iterator vec_it;
//
//	public:
//		PhysicsObject(uint16 pCategory, uint16 pMask, int32_t pDiameter, float pRestitution, b2World* pWorld);
//		PhysicsObject(uint16 pCategory, uint16 pMask, const std::vector<std::vector<Vector> >& vertices, 
//			float pRestitution, b2World* pWorld);
//
//		PhysicsTarget::ptr createTarget(float pFactor);
//
//		void initialize(float pX, float pY, float pVelocityX, float pVelocityY);
//		void update();
//
//	public:
//		bool m_collide;
//		Vector m_location;
//
//	private:
//		b2World* m_world;
//		b2Body* m_bodyObj;
//
//	}; // PhysicsObject
//}
//
//#endif // _D2D_PHYSICS_OBJECT_H_