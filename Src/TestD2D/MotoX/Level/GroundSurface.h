#ifndef _MOTOX_GROUND_SURFACE_H_
#define _MOTOX_GROUND_SURFACE_H_

#include "GroundSurfaceLoader.h"

namespace motox
{
	class GroundSurface
	{
	public:
		GroundSurface(d2d::Context* pContext,
			int scene, int level);

		void draw() const;
		void update(const d2d::Vector& center);

	private:
		class ColorBlockData
		{
		public:
			ColorBlockData();

			void draw() const;
			void update(int left, int right, const GroundSurfaceLoader& loader);

		private:
			static const int VERTICES_SIZE = 800;

		private:
			size_t m_leftGridID, m_rightGridID;

			float m_vertices[VERTICES_SIZE * 2];
			byte m_colors[VERTICES_SIZE * 4];
			unsigned short m_indices[VERTICES_SIZE * 3];

			size_t m_indicesSize;

		}; // ColorBlockData

		class TextureBlockData
		{
		public:
			TextureBlockData(d2d::Context* pContext);

			void draw() const;
			void update(int left, int right, const GroundSurfaceLoader& loader);

		private:
			void initTextureInfo(d2d::Context* pContext);

		private:
			static const int VERTICES_SIZE = 1000;

		private:
			d2d::TextureInfo m_texInfo;

			size_t m_leftGridID, m_rightGridID;

			float m_vertices[VERTICES_SIZE * 2];
			float m_texCoords[VERTICES_SIZE * 2];

			size_t m_verticesSize;

		}; // TextureBlockData

		//class TileStencilData
		//{
		//public:
		//	TileStencilData(d2d::Context* pContext);
		//	~TileStencilData();

		//	void draw() const;
		//	void update(int left, int right, const GroundSurfaceLoader& loader);

		//private:
		//	void initTextureInfo(d2d::Context* pContext);

		//private:
		//	struct TextureInfo;

		//	class Layer
		//	{
		//	public:
		//		Layer(const TileStencilData::TextureInfo& texInfo);

		//		void draw() const;
		//		void update(int index, int left, int right, const GroundSurfaceLoader& loader);

		//	private:
		//		void drawStencil() const;
		//		void drawTexture() const;
		//		
		//	private:
		//		static const int STENCIL_VERTICES_SIZE = 400;
		//		static const int TEXTURE_VERTICES_SIZE = 200;

		//	private:
		//		const TileStencilData::TextureInfo& m_texInfo;

		//		size_t m_leftGridID, m_rightGridID;

		//		float m_stencilVertices[STENCIL_VERTICES_SIZE * 2];
		//		unsigned short m_stencilIndices[STENCIL_VERTICES_SIZE * 3];

		//		float m_textureVertices[TEXTURE_VERTICES_SIZE * 2];
		//		float m_textureTexCoords[TEXTURE_VERTICES_SIZE * 2];
		//		unsigned short m_textureIndices[TEXTURE_VERTICES_SIZE * 4];

		//		size_t m_stencilIndicesSize, m_textureIndicesSize;

		//	}; // Layer

		//private:
		//	struct TextureRegion
		//	{
		//		int left;
		//		int top;
		//		int width;
		//		int height;

		//		TextureRegion(int l, int t, int w, int h) 
		//			: left(l), top(t), width(w), height(h) {}
		//	};

		//	struct TextureInfo
		//	{
		//		d2d::Texture* texture;

		//		int totWidth, totHeight;
		//		std::vector<TextureRegion> texRegions;
		//	};

		//private:
		//	TextureInfo m_texInfo;

		//	std::vector<Layer*> m_layers;

		////	d2d::TileStencilBatch* m_tileStencilBatch;

		//}; // TileStencilData

	private:
		GroundSurfaceLoader m_loader;

		ColorBlockData m_colors;
		TextureBlockData m_textures;

	}; // GroundSurface
}

#endif // _MOTOX_GROUND_SURFACE_H_