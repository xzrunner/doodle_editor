#include "ActorMotionAdapter.h"

using namespace FEDITOR;

void ActorMotionAdapter::load(const std::string& filename)
{
	std::ifstream fin(filename.c_str());

	const size_t partsCount = MOTOX::PLAYER_PARTS_COUNT + MOTOX::MOTORBIKE_PARTS_COUNT;
	for (size_t i = 0, n = partsCount; i < n; ++i)
	{
		Part part;
		fin >> part.filename >> part.pos >> part.angle;
		m_parts.push_back(part);
	}

	const size_t jointsCount = MOTOX::JOINTS_TYPE_COUNT;
	for (size_t i = 0, n = jointsCount; i < n; ++i)
	{
		Joint joint;
		fin >> joint.params >> joint.anchor;
		m_joints.push_back(joint);
	}

	fin.close();
}