#ifndef _FEDITOR_SIMULATE_CLOTH_TRIANGLE_H_
#define _FEDITOR_SIMULATE_CLOTH_TRIANGLE_H_
#include <Fruits2D/Fruits2D.h>

class b2Body;

namespace FEDITOR
{
	namespace SIMULATE_CLOTH
	{
		struct Node
		{
			b2Body* body;
			f2Vec2 texCoords;
			bool isTop;
		}; // Node

		struct Triangle
		{
			Node* nodes[3];
		}; // Triangle
	}
}

#endif // _FEDITOR_SIMULATE_CLOTH_TRIANGLE_H_