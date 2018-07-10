#ifndef _DEDITOR_MEDELING_RESOLVE_TO_B2_H_
#define _DEDITOR_MEDELING_RESOLVE_TO_B2_H_

#include <wxGUI/wxGUI.h>
#include <Box2D/Box2D.h>

namespace deditor
{
	namespace modeling
	{
		class BodyData;
		class JointData;

		class ResolveToB2
		{
		public:
			static b2Body* createBody(const BodyData& data, b2World* world,
				std::map<BodyData*, b2Body*>& bodyMap);
			static b2Joint* createJoint(const JointData& data, b2World* world,
				const std::map<BodyData*, b2Body*>& bodyMap);

		}; // ResolveToB2
	}
}

#endif // _DEDITOR_MEDELING_RESOLVE_TO_B2_H_