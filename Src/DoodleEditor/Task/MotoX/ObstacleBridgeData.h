#ifndef _DEDITOR_MOTOX_OBSTACLE_BRIDGE_DATA_H_
#define _DEDITOR_MOTOX_OBSTACLE_BRIDGE_DATA_H_

#include "IObstacleData.h"

#include <wxGUI/wxGUI.h>

namespace deditor
{
	namespace motox
	{
		class BridgeData : public IObstacleData
		{
		public:
			BridgeData(b2World* world, b2Body* ground, wxgui::ImageSymbol* symbol);
			~BridgeData();

			virtual void assemblyVertexArray(std::vector<f2Vec2>& vertices, 
				std::vector<f2Vec2>& texCoords);

			void build(const f2Vec2& start, const f2Vec2& end);

		private:
			void clear();

		private:
			static const float OVERLAP_RATIO;

		private:
			b2World* m_world;
			b2Body* m_ground;

			float m_tileWidth, m_tileHeight;

			std::vector<b2Body*> m_bodies;
			std::vector<b2RevoluteJoint*> m_joints;

		}; // BridgeData
	}
}

#endif // _DEDITOR_MOTOX_OBSTACLE_BRIDGE_DATA_H_