#ifndef _FEDITOR_ACTOR_MOTION_ADAPTER_H_
#define _FEDITOR_ACTOR_MOTION_ADAPTER_H_
#include "TextFileAdapter.h"
#include "../Edit/MotoX/ActorDefs.h"

namespace FEDITOR
{
	class ActorMotionAdapter
	{
	public:

		virtual void load(const std::string& filename);

	public:
		struct Part
		{
			std::string filename;
			f2Vec2 pos;
			float angle;
		}; // Part

		struct Joint
		{
			MOTOX::JointParams params;
			f2Vec2 anchor;
		};

	public:
		std::vector<Part> m_parts;
		std::vector<Joint> m_joints;

	}; // ActorMotionAdapter
}

#endif // _FEDITOR_ACTOR_MOTION_ADAPTER_H_