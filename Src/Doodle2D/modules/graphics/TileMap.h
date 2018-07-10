#ifndef _D2D_TILE_MAP_H_
#define _D2D_TILE_MAP_H_

#include "common/config.h"
#include "common/Vector.h"
#include "Texture.h"

#ifdef D2D_ANDROID_NATIVE
#include <android_native_app_glue.h>
#endif

namespace d2d 
{
	class TileMap 
	{
	public:

#ifdef D2D_WINDOWS
		TileMap(const std::string& pPath, Texture* pTexture, Vector* pLocation);
#elif defined D2D_ANDROID_NATIVE
		TileMap(android_app* pApplication, const std::string& pPath,
			Texture* pTexture, Vector* pLocation);
#elif defined D2D_ANDROID_JNI
		TileMap(const std::string& pPath, Texture* pTexture, Vector* pLocation);
#endif

		status load();
		void unload();
		void draw();

	private:
		int32_t* loadFile();
		void loadVertices(int32_t* pTiles, uint8_t** pVertexBuffer, uint32_t* pVertexBufferSize);
		void loadIndexes(uint8_t** pIndexBuffer, uint32_t* pIndexBufferSize);

	private:
		Resource m_resource;
		Vector* m_location;

		// OpenGL resources.
		Texture* m_texture;
		GLuint m_vertexBuffer, m_indexBuffer;
		int32_t m_vertexCount, m_indexCount;
		const int32_t m_vertexComponents;

		// Tile map description.
		int32_t m_height, m_width;
		int32_t m_tileHeight, m_tileWidth;
		int32_t m_tileCount, m_tileXCount;

	}; // TileMap
}

#endif // _D2D_TILE_MAP_H_