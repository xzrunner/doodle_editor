#ifndef _WX_GUI_MATH_H_
#define _WX_GUI_MATH_H_

#include "Dataset/ChainShape.h"

namespace wxgui
{
	class Math
	{
	public:

		static void mergeTwoChains(const ChainShape& src0, const ChainShape& src1,
			std::vector<f2Vec2>& dst);

		static void mergeMultiChains(const std::vector<ChainShape*>& src, std::vector<f2Vec2>& dst);

		static void removeDuplicatePoints(const std::vector<f2Vec2>& src, std::vector<f2Vec2>& dst);

		enum TriangulateType
		{
			e_Constrained,
			e_Conforming,
			e_ConstrainedConformingAngle,
			e_ConstrainedConformingArea,
			e_ConstrainedConformingCount
		};
		static void triangulatePolygon(const std::vector<f2Vec2>& polygon, std::vector<f2Vec2>& result, 
			TriangulateType type = e_Constrained);
		static void triangulatePolygon(const std::vector<f2Vec2>& polygon, const std::vector<f2Vec2>& lines,
			std::vector<f2Vec2>& result, TriangulateType type = e_Constrained);
		static void triangulatePolygon(const std::vector<f2Vec2>& polygon, const std::vector<f2Vec2>& lines,
			const std::vector<std::vector<f2Vec2> >& loops, std::vector<f2Vec2>& result, TriangulateType type = e_Constrained);

		static void triangulateStrips(const std::vector<f2Vec2>& triangulates, 
			std::vector<std::vector<f2Vec2> >& strips);

		// 1 2
		// 0 3
		static void computeQuadNodes(const f2Vec2& center, float angle, 
			float scale, float width, float height, f2Vec2 quad[4]);

	private:
		// for mergeMultiChains
		static void findNearestPair(const std::vector<ChainShape*>& chains, int& index0, int& index1);
		static float getDistanceOfChains(const ChainShape& chain0, const ChainShape& chain1);

	}; // Math
}

#endif // _WX_GUI_MATH_H_