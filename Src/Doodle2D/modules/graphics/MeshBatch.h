#ifndef _D2D_MESH_BATCH_H_
#define _D2D_MESH_BATCH_H_

#include "common/types.h"

#include <vector>

namespace d2d
{
	class Texture;
	class Quad;
	class Mesh;
	class VertexBuffer;
	class GraphicsSprite;

	class MeshBatch
	{
	public:
		enum UsageHint
		{
			USAGE_DYNAMIC = 1,
			USAGE_STATIC,
			USAGE_STREAM,
			USAGE_MAX_ENUM
		};

	public:
		MeshBatch(Texture* texture, int size, int usage);
		virtual ~MeshBatch();

		int add(const GraphicsSprite& sprite, int index = -1);
		int add(const Mesh& mesh, float x, float y, float angle, 
			float scale, int index = -1);

		void* lock();
		void unlock();

		void onDraw() const;

		void setEndIndex(int iNext) { m_next = iNext; }

	private:
		void createBuffer(int size, int usage);

		int add(const Quad& quad, float x, float y, float angle, 
			float scale, int index = -1);
		void add(const Vertex& v, int index);
		void add(const std::vector<Vertex>& vertices, int index);

	private:
		Texture* m_texture;

		int m_size;
		int m_next;

		VertexBuffer* m_vertices;

	}; // MeshBatch
}

#endif // _D2D_MESH_BATCH_H_