#ifndef _FEDITOR_EXTRACT_EDGE_SAME_COLOR_REGION_SELECT_H_
#define _FEDITOR_EXTRACT_EDGE_SAME_COLOR_REGION_SELECT_H_
#include <Fruits2D/Fruits2D.h>

namespace FEDITOR
{
	class Texture;
	class Layer;

	namespace EXTRACT_EDGE
	{
		class Blackboard;

		class SameColorRegionSelect
		{
		public:
			SameColorRegionSelect(const Blackboard* blackboard, const Texture& texture);

			void selectByPos();
			void selectByPos(const f2Vec2& p);

			void simplifyBoundaries();

			void addDataToLayer(Layer* layer) const;

		private:
			struct SameColorPixel
			{
				std::vector<f2Vec2> inner;
				std::vector<f2Vec2> boundary;

				void clear();
			};

			struct SameColorBoundary
			{
				std::vector<std::vector<f2Vec2> > rough;
				std::vector<std::vector<f2Vec2> > simplified;

				void clear();
			};

			void buildSameColorPixelData();

			void buildSameColorBoundaryData();
			bool createLoopByExtend(std::vector<bool>& visited, std::vector<f2Vec2>& loop, f2Vec2& prev, const f2Vec2& next) const;

		private:
			const Blackboard* m_blackboard;

			const Texture& m_texture;
			unsigned char* m_pixelData;

			f2Vec2 m_cacheLastPos;

			SameColorPixel m_midPixels;
			SameColorBoundary m_midBoundaries;

		}; // SameColorRegionSelect
	}
}

#endif // _FEDITOR_EXTRACT_EDGE_SAME_COLOR_REGION_SELECT_H_