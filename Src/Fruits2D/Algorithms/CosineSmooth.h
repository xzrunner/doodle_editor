#ifndef _F2D_COSINE_SMOOTH_H_
#define _F2D_COSINE_SMOOTH_H_

#include "Tools/Tools.h"
#include "Tools/f2Types.h"

namespace F2D
{
	class CosineSmooth
	{
	public:
		static void implement(const std::vector<f2Vec2>& src, float samplingWidth,
			std::vector<f2Vec2>& dst);

	}; // CosineSmooth
}

#endif // _F2D_COSINE_SMOOTH_H_