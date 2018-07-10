#include "Math.h"

#include <Triangle/triangle.cpp>

using namespace wxgui;

void Math::mergeTwoChains(const ChainShape& src0, const ChainShape& src1,
						  std::vector<f2Vec2>& dst)
{
	const std::vector<f2Vec2>& s0 = src0.getVertices();
	const std::vector<f2Vec2>& s1 = src1.getVertices();

	dst.clear();
	dst.reserve(s0.size() + s1.size());

	float d[4];
	d[0] = f2Math::getDistanceSquare(s0.back(), s1.front());
	d[1] = f2Math::getDistanceSquare(s0.back(), s1.back());
	d[2] = f2Math::getDistanceSquare(s0.front(), s1.front());
	d[3] = f2Math::getDistanceSquare(s0.front(), s1.back());
	float nearest = FLOAT_MAX;
	for (size_t i = 0; i < 4; ++i)
		if (d[i] < nearest)
			nearest = d[i];

	if (nearest == d[0])
	{
		copy(s0.begin(), s0.end(), back_inserter(dst));
		copy(s1.begin(), s1.end(), back_inserter(dst));
	}
	else if (nearest == d[1])
	{
		copy(s0.begin(), s0.end(), back_inserter(dst));
		copy(s1.rbegin(), s1.rend(), back_inserter(dst));
	}
	else if (nearest == d[2])
	{
		copy(s0.rbegin(), s0.rend(), back_inserter(dst));
		copy(s1.begin(), s1.end(), back_inserter(dst));
	}
	else if (nearest == d[3])
	{
		copy(s1.begin(), s1.end(), back_inserter(dst));
		copy(s0.begin(), s0.end(), back_inserter(dst));
	}
}

void Math::mergeMultiChains(const std::vector<ChainShape*>& src, std::vector<f2Vec2>& dst)
{
	if (src.size() == 0)
	{
		return;
	}
	else if (src.size() == 1)
	{
		copy(src[0]->getVertices().begin(), src[0]->getVertices().end(), back_inserter(dst));
		return;
	}
	else if (src.size() == 2)
	{
		mergeTwoChains(*src[0], *src[1], dst);
		return;
	}

	std::vector<ChainShape*> buffer;
	buffer.reserve(src.size());
	for (size_t i = 0, n = src.size(); i < n; ++i)
	{
		src[i]->retain();
		buffer.push_back(src[i]);
	}

	while (buffer.size() > 2)
	{
		int i0, i1;
		findNearestPair(buffer, i0, i1);

		std::vector<f2Vec2> merged;
		mergeTwoChains(*buffer[i0], *buffer[i1], merged);
		
		buffer[i0]->release();
		buffer[i1]->release();

		buffer.erase(buffer.begin() + i0);
		if (i1 < i0)
			buffer.erase(buffer.begin() + i1);
		else
			buffer.erase(buffer.begin() + i1 - 1);

		buffer.push_back(new ChainShape(merged, false));
	}

	assert(buffer.size() == 2);

	mergeTwoChains(*buffer[0], *buffer[1], dst);
	buffer[0]->release();
	buffer[1]->release();
}

void Math::removeDuplicatePoints(const std::vector<f2Vec2>& src, std::vector<f2Vec2>& dst)
{
	if (src.size() > 1)
	{
		dst.reserve(src.size());

		f2Vec2 last = src[0];
		dst.push_back(last);
		for (size_t i = 1; i < src.size(); ++i)
		{
			if (f2Math::getDistance(src[i], last) > 1.0f)
			{
 				last = src[i];
 				dst.push_back(last);			
			}
		}
	}
	else
	{
		dst = src;
	}
}

void Math::triangulatePolygon(const std::vector<f2Vec2>& polygon, std::vector<f2Vec2>& result, 
							  TriangulateType type/* = e_Constrained*/)
{
	struct triangulateio in, out;

	in.numberofpoints = polygon.size();
	in.numberofpointattributes = 0;
	in.pointlist = (REAL *) malloc(in.numberofpoints * 2 * sizeof(REAL));
	in.pointmarkerlist = (int *) NULL;
	int index = 0;
	for (size_t i = 0; i < in.numberofpoints; ++i)
	{
		in.pointlist[index++] = polygon[i].x;
		in.pointlist[index++] = polygon[i].y;
	}

	in.numberofsegments = in.numberofpoints;
	in.segmentlist = (int *) malloc(in.numberofsegments * 2 * sizeof(int));
	index = 0;
	for (size_t i = 0; i < in.numberofsegments - 1; ++i)
	{
		in.segmentlist[index++] = i;
		in.segmentlist[index++] = i + 1;
	}
	in.segmentlist[index++] = in.numberofsegments - 1;
	in.segmentlist[index++] = 0;

	in.segmentmarkerlist = (int *) NULL;

	in.numberofholes = 0;
	in.numberofregions = 0;

	out.pointlist = (REAL *) NULL;
	out.pointattributelist = (REAL *) NULL;
	out.pointmarkerlist = (int *) NULL;
	out.trianglelist = (int *) NULL;
	out.triangleattributelist = (REAL *) NULL;
	out.segmentlist = (int *) NULL;
	out.segmentmarkerlist = (int *) NULL;

	switch (type)
	{
	case e_Constrained:
		triangulate("pz", &in, &out, (struct triangulateio *) NULL);
		break;
	case e_Conforming:
		triangulate("pzD", &in, &out, (struct triangulateio *) NULL);
		break;
	case e_ConstrainedConformingAngle:
		triangulate("pzq", &in, &out, (struct triangulateio *) NULL);
		break;
	case e_ConstrainedConformingArea:
		triangulate("pza10000", &in, &out, (struct triangulateio *) NULL);
		break;
	case e_ConstrainedConformingCount:
		triangulate("pzu100", &in, &out, (struct triangulateio *) NULL);
		break;
	default:
		assert(0);
	}

	index = 0;
	for (size_t i = 0; i < out.numberoftriangles; ++i)
	{
		for (size_t j = 0; j < out.numberofcorners; ++j)
		{
			int pIndex = out.trianglelist[index++];

			f2Vec2 p;
			p.x = out.pointlist[pIndex * 2];
			p.y = out.pointlist[pIndex * 2 + 1];
			result.push_back(p);
		}
	}
}

void Math::triangulatePolygon(const std::vector<f2Vec2>& polygon, const std::vector<f2Vec2>& lines,
							  std::vector<f2Vec2>& result, TriangulateType type/* = e_Constrained*/)
{
	struct triangulateio in, out;

	in.numberofpoints = polygon.size() + lines.size();
	in.numberofpointattributes = 0;
	in.pointlist = (REAL *) malloc(in.numberofpoints * 2 * sizeof(REAL));
	in.pointmarkerlist = (int *) NULL;
	int index = 0;
	for (size_t i = 0, n = polygon.size(); i < n; ++i)
	{
		in.pointlist[index++] = polygon[i].x;
		in.pointlist[index++] = polygon[i].y;
	}
	for (size_t i = 0, n = lines.size(); i < n; ++i)
	{
		in.pointlist[index++] = lines[i].x;
		in.pointlist[index++] = lines[i].y;
	}

	in.numberofsegments = polygon.size() + lines.size() / 2;
	in.segmentlist = (int *) malloc(in.numberofsegments * 2 * sizeof(int));

	index = 0;
	for (size_t i = 0, n = polygon.size() - 1; i < n; ++i)
	{
		in.segmentlist[index++] = i;
		in.segmentlist[index++] = i + 1;
	}
	in.segmentlist[index++] = polygon.size() - 1;
	in.segmentlist[index++] = 0;

	int lineIndex = polygon.size();
	for (size_t i = 0, n = lines.size() / 2; i < n; ++i)
	{
		in.segmentlist[index++] = lineIndex++;
		in.segmentlist[index++] = lineIndex++;
	}

	in.segmentmarkerlist = (int *) NULL;

	in.numberofholes = 0;
	in.numberofregions = 0;

	out.pointlist = (REAL *) NULL;
	out.pointattributelist = (REAL *) NULL;
	out.pointmarkerlist = (int *) NULL;
	out.trianglelist = (int *) NULL;
	out.triangleattributelist = (REAL *) NULL;
	out.segmentlist = (int *) NULL;
	out.segmentmarkerlist = (int *) NULL;

	switch (type)
	{
	case e_Constrained:
		triangulate("pz", &in, &out, (struct triangulateio *) NULL);
		break;
	case e_Conforming:
		triangulate("pzD", &in, &out, (struct triangulateio *) NULL);
		break;
	case e_ConstrainedConformingAngle:
		triangulate("pzq", &in, &out, (struct triangulateio *) NULL);
		break;
	case e_ConstrainedConformingArea:
		triangulate("pza10000", &in, &out, (struct triangulateio *) NULL);
		break;
	case e_ConstrainedConformingCount:
		triangulate("pzu100", &in, &out, (struct triangulateio *) NULL);
		break;
	default:
		assert(0);
	}

	index = 0;
	for (size_t i = 0; i < out.numberoftriangles; ++i)
	{
		std::vector<f2Vec2> tri;
		for (size_t j = 0; j < out.numberofcorners; ++j)
		{
			int pIndex = out.trianglelist[index++];

			f2Vec2 p;
			p.x = out.pointlist[pIndex * 2];
			p.y = out.pointlist[pIndex * 2 + 1];
			tri.push_back(p);
		}

		f2Vec2 center = f2Math::getTriGravityCenter(tri[0], tri[1], tri[2]);
		if (f2Math::isPointInArea(center, polygon))
			copy(tri.begin(), tri.end(), back_inserter(result));
	}
}

void Math::triangulatePolygon(const std::vector<f2Vec2>& polygon, const std::vector<f2Vec2>& lines,
							  const std::vector<std::vector<f2Vec2> >& loops, std::vector<f2Vec2>& result, TriangulateType type/* = e_Constrained*/)
{
	struct triangulateio in, out;

	size_t loopSize = 0;
	for (size_t i = 0, n = loops.size(); i < n; ++i)
		loopSize += loops[i].size();

	in.numberofpoints = polygon.size() + lines.size() + loopSize;
	in.numberofpointattributes = 0;
	in.pointlist = (REAL *) malloc(in.numberofpoints * 2 * sizeof(REAL));
	in.pointmarkerlist = (int *) NULL;
	int index = 0;
	for (size_t i = 0, n = polygon.size(); i < n; ++i)
	{
		in.pointlist[index++] = polygon[i].x;
		in.pointlist[index++] = polygon[i].y;
	}
	for (size_t i = 0, n = lines.size(); i < n; ++i)
	{
		in.pointlist[index++] = lines[i].x;
		in.pointlist[index++] = lines[i].y;
	}
	for (size_t i = 0, n = loops.size(); i < n; ++i)
	{
		for (size_t j = 0, m = loops[i].size(); j < m; ++j)
		{
			in.pointlist[index++] = loops[i][j].x;
			in.pointlist[index++] = loops[i][j].y;
		}
	}

	in.numberofsegments = polygon.size() + lines.size() / 2 + loopSize;
	in.segmentlist = (int *) malloc(in.numberofsegments * 2 * sizeof(int));

	index = 0;
	for (size_t i = 0, n = polygon.size() - 1; i < n; ++i)
	{
		in.segmentlist[index++] = i;
		in.segmentlist[index++] = i + 1;
	}
	in.segmentlist[index++] = polygon.size() - 1;
	in.segmentlist[index++] = 0;

	int lineIndex = polygon.size();
	for (size_t i = 0, n = lines.size() / 2; i < n; ++i)
	{
		in.segmentlist[index++] = lineIndex++;
		in.segmentlist[index++] = lineIndex++;
	}

	int loopIndex = polygon.size() + lines.size();
	for (size_t i = 0, n = loops.size(); i < n; ++i)
	{
		int start = loopIndex;
		for (size_t j = 0, m = loops[i].size() - 1; j < m; ++j)
		{
			in.segmentlist[index++] = loopIndex;
			in.segmentlist[index++] = loopIndex + 1;
			++loopIndex;
		}
		in.segmentlist[index++] = loopIndex;
		in.segmentlist[index++] = start;
		++loopIndex;
	}

	in.segmentmarkerlist = (int *) NULL;

	in.numberofholes = 0;
	in.numberofregions = 0;

	out.pointlist = (REAL *) NULL;
	out.pointattributelist = (REAL *) NULL;
	out.pointmarkerlist = (int *) NULL;
	out.trianglelist = (int *) NULL;
	out.triangleattributelist = (REAL *) NULL;
	out.segmentlist = (int *) NULL;
	out.segmentmarkerlist = (int *) NULL;

	switch (type)
	{
	case e_Constrained:
		triangulate("pz", &in, &out, (struct triangulateio *) NULL);
		break;
	case e_Conforming:
		triangulate("pzD", &in, &out, (struct triangulateio *) NULL);
		break;
	case e_ConstrainedConformingAngle:
		triangulate("pzq", &in, &out, (struct triangulateio *) NULL);
		break;
	case e_ConstrainedConformingArea:
		triangulate("pza10000", &in, &out, (struct triangulateio *) NULL);
		break;
	case e_ConstrainedConformingCount:
		triangulate("pzu100", &in, &out, (struct triangulateio *) NULL);
		break;
	default:
		assert(0);
	}

	index = 0;
	for (size_t i = 0; i < out.numberoftriangles; ++i)
	{
		std::vector<f2Vec2> tri;
		for (size_t j = 0; j < out.numberofcorners; ++j)
		{
			int pIndex = out.trianglelist[index++];

			f2Vec2 p;
			p.x = out.pointlist[pIndex * 2];
			p.y = out.pointlist[pIndex * 2 + 1];
			tri.push_back(p);
		}

		f2Vec2 center = f2Math::getTriGravityCenter(tri[0], tri[1], tri[2]);
		if (f2Math::isPointInArea(center, polygon))
			copy(tri.begin(), tri.end(), back_inserter(result));
	}
}

void Math::triangulateStrips(const std::vector<f2Vec2>& triangulates, 
							 std::vector<std::vector<f2Vec2> >& strips)
{
	F2D::SGI::implement(triangulates, strips);
}

void Math::computeQuadNodes(const f2Vec2& center, float angle, float scale, 
							float width, float height, f2Vec2 quad[4])
{
	const float hWidth = width * 0.5f * scale,
		hHeight = height * 0.5f * scale;

	float x1 = - hWidth;
	float y1 = - hHeight;
	float x2 = - hWidth;
	float y2 =   hHeight;
	float x3 =   hWidth;
	float y3 =   hHeight;

	const float cosVal = cos(angle),
		sinVal = sin(angle);

	quad[0].x = cosVal * x1 - sinVal * y1 + center.x;
	quad[0].y = sinVal * x1 + cosVal * y1 + center.y;

	quad[1].x = cosVal * x2 - sinVal * y2 + center.x;
	quad[1].y = sinVal * x2 + cosVal * y2 + center.y;

	quad[2].x = cosVal * x3 - sinVal * y3 + center.x;
	quad[2].y = sinVal * x3 + cosVal * y3 + center.y;

	quad[3].x = quad[0].x + (quad[2].x - quad[1].x);
	quad[3].y = quad[2].y - (quad[1].y - quad[0].y);
}

void Math::findNearestPair(const std::vector<ChainShape*>& chains, int& index0, int& index1)
{
	if (chains.size() == 0)
	{
		index0 = index1 = -1;
		return;
	}
	else if (chains.size() == 1)
	{
		index0 = index1 = 0;
		return;
	}
	else if (chains.size() == 2)
	{
		index0 = 0;
		index1 = 1;
		return;
	}

	float nearest = FLOAT_MAX;
	for (size_t i = 0, n = chains.size() - 1; i < n; ++i)
	{
		for (size_t j = i + 1, m = chains.size(); j < m; ++j)
		{
			const float dis = getDistanceOfChains(*chains[i], *chains[j]);
			if (dis < nearest)
			{
				nearest = dis;
				index0 = i;
				index1 = j;
			}
		}
	}
}

float Math::getDistanceOfChains(const ChainShape& chain0, const ChainShape& chain1)
{
	const std::vector<f2Vec2>& s0 = chain0.getVertices();
	const std::vector<f2Vec2>& s1 = chain1.getVertices();

	float d[4];
	d[0] = f2Math::getDistanceSquare(s0.back(), s1.front());
	d[1] = f2Math::getDistanceSquare(s0.back(), s1.back());
	d[2] = f2Math::getDistanceSquare(s0.front(), s1.front());
	d[3] = f2Math::getDistanceSquare(s0.front(), s1.back());
	float nearest = FLOAT_MAX;
	for (size_t i = 0; i < 4; ++i)
		if (d[i] < nearest)
			nearest = d[i];
 
	return nearest;
}