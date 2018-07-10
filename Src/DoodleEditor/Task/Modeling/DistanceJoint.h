#ifndef _DEDITOR_MODELING_DISTANCE_JOINT_H_
#define _DEDITOR_MODELING_DISTANCE_JOINT_H_

#include "JointData.h"

namespace deditor
{
	namespace modeling
	{
		class DistanceJoint : public JointData
		{
		public:
			DistanceJoint(BodyData* b0, BodyData* b1);

			virtual bool isContain(const f2Vec2& pos) const;

			virtual void draw(DrawType type) const;

			f2Vec2 getWorldAnchorA() const;
			f2Vec2 getWorldAnchorB() const;

			void setLocalAnchorA(const f2Vec2& world);
			void setLocalAnchorB(const f2Vec2& world);

		private:
			void drawAnchor(const f2Vec2& pos, DrawType type) const;

			void drawConnection(const f2Vec2& worldAnchorA, const f2Vec2& worldAnchorB,
				DrawType type) const;

		public:
			f2Vec2 localAnchorA;
			f2Vec2 localAnchorB;

			float length;

			float frequencyHz;
			float dampingRatio;

		}; // DistanceJoint
	}
}

#endif // _DEDITOR_MODELING_DISTANCE_JOINT_H_