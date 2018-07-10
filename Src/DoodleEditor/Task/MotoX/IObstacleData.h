#ifndef _DEDITOR_MOTOX_INTERFACE_OBSTACLE_DATA_H_
#define _DEDITOR_MOTOX_INTERFACE_OBSTACLE_DATA_H_

#include <Fruits2D/Fruits2D.h>

namespace deditor
{
	namespace motox
	{
		class IObstacleData
		{
		public:
			virtual ~IObstacleData() {}

			virtual void assemblyVertexArray(std::vector<f2Vec2>& vertices, 
				std::vector<f2Vec2>& texCoords) = 0;

		}; // IObstacleData
	}
}

#endif // _DEDITOR_MOTOX_INTERFACE_OBSTACLE_DATA_H_