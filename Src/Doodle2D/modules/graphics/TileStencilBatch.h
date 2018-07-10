#ifndef _D2D_TILE_STENCIL_BATCH_H_
#define _D2D_TILE_STENCIL_BATCH_H_

#include "TextureInfo.h"

#include "common/types.h"
#include "common/Vector.h"

#include <vector>

namespace d2d
{
	class Texture;
	class VertexBuffer;

	class TileStencilBatch
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
		TileStencilBatch(Texture* texture, int stencilSize, int textureSize, int usage);
		virtual ~TileStencilBatch();

		void add(const std::vector<Vector>& vertices, const std::vector<unsigned short>& indices,
			int texID, const Vector& leftLow, const std::vector<unsigned int>& mesh);

		void onDraw() const;

	private:
		void createBuffer(int stencilSize, int textureSize, int usage);

		void initTextureInfo();

		void addStencil(const std::vector<Vector>& vertices, const std::vector<unsigned short>& indices);
		void addTexture(int texID, const Vector& leftLow, const std::vector<unsigned int>& mesh);

		void drawStencil() const;
		void drawTexture() const;

	private:
		Texture* m_texture;

		TextureInfo m_texInfo;

		VertexBuffer* m_stencilVertices;
		VertexBuffer* m_stencilIndices;

		VertexBuffer* m_textureVertices;
		VertexBuffer* m_textureIndices;

		int m_stencilVerticesCount, m_stencilIndicesCount;
		int m_textureVerticesCount, m_textureIndicesCount;

	}; // TileStencilBatch
}

#endif // _D2D_TILE_STENCIL_BATCH_H_