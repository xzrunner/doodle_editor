#ifndef _F2D_DOUGLAS_PEUCKER_H_
#define _F2D_DOUGLAS_PEUCKER_H_

#include "Tools/Tools.h"
#include "Tools/f2Types.h"

namespace F2D
{
	class DouglasPeucker
	{
	public:
		static void implement(const std::vector<f2Vec2>& line, float precision, std::vector<f2Vec2>& dst);

	private:
		static void pointsReduction(const std::vector<f2Vec2>& line, float precision, std::vector<bool>& flag,
			size_t begin, size_t end);

	}; // DouglasPeucker
}

#endif // _F2D_DOUGLAS_PEUCKER_H_