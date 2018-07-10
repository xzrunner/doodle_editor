#include "CosineSmooth.h"

using namespace F2D;

void CosineSmooth::implement(const std::vector<f2Vec2>& src, float samplingWidth, 
							 std::vector<f2Vec2>& dst)
{
	dst.clear();

	if (src.size() < 2) return;

	for (size_t i = 0, n = src.size() - 1; i < n; ++i)
	{
		const f2Vec2& p0 = src[i],
			p1 = src[i+1];
		const size_t samplingCount = static_cast<size_t>(std::floor(std::abs(p1.x - p0.x) / samplingWidth));
		const float dx = (p1.x - p0.x) / samplingCount;
		const float da = PI / samplingCount;
		const float yMid = (p0.y + p1.y) * 0.5f;
		const float ampl = (p0.y - p1.y) * 0.5f;
		dst.push_back(p0);
		for (size_t j = 1; j < samplingCount; ++j)
		{
			f2Vec2 pt;
			pt.x = p0.x + j * dx;
			pt.y = yMid + ampl * cos(da * j);
			dst.push_back(pt);
		}
	}
	dst.push_back(src.back());
}