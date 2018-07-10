#include "DouglasPeucker.h"
#include "Tools/f2Math.h"

using namespace F2D;

void DouglasPeucker::implement(const std::vector<f2Vec2>& line, float precision, std::vector<f2Vec2>& dst)
{
	dst.clear();

	std::vector<bool> flag(line.size(), false);
	pointsReduction(line, precision, flag, 0, line.size() - 1);
	for (size_t i = 0, n = line.size(); i < n; ++i)
		if (flag[i]) dst.push_back(line[i]);
}

void DouglasPeucker::pointsReduction(const std::vector<f2Vec2>& line, float precision, std::vector<bool>& flag,
									 size_t begin, size_t end)
{
	if ( begin > end )
		return;

	if ( begin == end )
	{
		flag[begin] = true;
		return;
	}

	if ( end - begin < 2 )
	{
		flag[begin] = true;
		flag[end] = true;
		return;
	}

	size_t savedPointIndex = 0;
	float max = - FLOAT_MAX;
	for (size_t i = begin + 1; i < end; ++i)
	{
		float dis = f2Math::getDisPointToSegment(line[i], line[begin], line[end]);
		if (dis > max)
		{
			max = dis;
			savedPointIndex = i;
		}
	}

	if (max < precision)
	{
		flag[begin] = true;
		flag[end] = true;
	}
	else
	{
		pointsReduction(line, precision, flag, begin, savedPointIndex);
		pointsReduction(line, precision, flag, savedPointIndex, end);
	}
}