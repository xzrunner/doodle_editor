#ifndef _DEDITOR_MOTOX_OBSTACLE_SOFT_DATA_H_
#define _DEDITOR_MOTOX_OBSTACLE_SOFT_DATA_H_

#include "IObstacleData.h"

#include <wxGUI/wxGUI.h>

namespace deditor
{
	namespace motox
	{
		struct SoftDataDef
		{
			int width, height;
			int edge;

			float frequencyHz;
			float dampingRatio;

			float nodeHalfEdge;

		}; // SoftDataDef

		class SoftData : public IObstacleData
		{
		public:
			SoftData(b2World* world);
			virtual ~SoftData();

			virtual void build(const SoftDataDef& def, const f2Vec2& center) = 0;

		protected:
			void clear();

		protected:
			struct Node
			{
				b2Body* body;
				f2Vec2 texCoords;

				f2Vec2 getPosition() const;
			};

		protected:
			b2World* m_world;

			std::vector<Node*> m_nodes;

			std::vector<b2Joint*> m_joints;

		}; // SoftData

		class SoftPolyData : public SoftData
		{
		public:
			SoftPolyData(b2World* world);

			virtual void build(const SoftDataDef& def, const f2Vec2& center);

			virtual void assemblyVertexArray(std::vector<f2Vec2>& vertices, 
				std::vector<f2Vec2>& texCoords);

		private:
			size_t m_row, m_col;

		}; // SoftPolyData

		class SoftCircleData : public SoftData
		{
		public:
			SoftCircleData(b2World* world);

			virtual void build(const SoftDataDef& def, const f2Vec2& center);

			virtual void assemblyVertexArray(std::vector<f2Vec2>& vertices, 
				std::vector<f2Vec2>& texCoords);

		private:
			size_t m_count;

			float m_texScale;

		}; // SoftCircleData
	}
}

#endif // _DEDITOR_MOTOX_OBSTACLE_SOFT_DATA_H_