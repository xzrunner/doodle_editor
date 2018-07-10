#ifndef _F2D_SGI_H_
#define _F2D_SGI_H_

#include "Tools/Tools.h"
#include "Tools/f2Types.h"

namespace F2D
{
	class SGI
	{
	public:

		static void implement(const std::vector<f2Vec2>& src,
			std::vector<std::vector<f2Vec2> >& dst);

	private:
		struct Edge;

		struct Triangle
		{
			bool bUsed;

			f2Vec2 nodes[3];

			// [0] v0-v1, [1] v1-v2, [2] v2-v0
			Edge* edges[3];

			Triangle() {
				bUsed = false;
				edges[0] = edges[1] = edges[2] = NULL;
			}
		};

		struct Edge
		{
			f2Vec2 start, end;

			Triangle *left, *right;

			Edge() {
				left = right = NULL;
			}
		};

	private:
		static void insertEdge(std::vector<Edge*>& edges, Triangle* tri,
			int index);

		static void traversal(Triangle* tri, std::vector<f2Vec2>& strip, int level = 0);

		static int getDegree(Triangle* tri, int level);

		static Triangle* getMinDegreeTri(const std::vector<Triangle*>& tris);

	}; // SGI
}

#endif // _F2D_SGI_H_