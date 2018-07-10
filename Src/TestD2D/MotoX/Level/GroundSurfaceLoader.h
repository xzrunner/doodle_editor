#ifndef _MOTOX_GROUND_SURFACE_LOADER_H_
#define _MOTOX_GROUND_SURFACE_LOADER_H_

#include <Doodle2D/doodle2d.h>

namespace motox
{
	class GroundSurfaceLoader
	{
	public:
		GroundSurfaceLoader(d2d::Context* pContext, 
			int scene, int level);
		~GroundSurfaceLoader();

	private:
		struct ColorBlock;
		struct TextureBlock;

		void loadFromFile(const std::string& filename);

		ColorBlock* loadColorBlock(byte*& ptr);
		TextureBlock* loadTextureBlock(byte*& ptr);

		void loadVerticeIndices(byte*& ptr, std::vector<d2d::Vector>& vertices,
			std::vector<unsigned short>& indices);

		void clear();

	private:
		struct ColorBlock
		{
			d2d::Color color;
			std::vector<d2d::Vector> vertices;
			std::vector<unsigned short> indices;
		};

		struct TextureBlock
		{
			unsigned int id;
			std::vector<d2d::Vector> vertices;
			std::vector<d2d::Vector> texCoords;
		};

		struct Grid
		{
			std::vector<ColorBlock*> colorBlocks;
			std::vector<TextureBlock*> textureBlocks;

			~Grid() {
				for_each(colorBlocks.begin(), colorBlocks.end(), DeletePointerFunctor<ColorBlock>());
				colorBlocks.clear();
				for_each(textureBlocks.begin(), textureBlocks.end(), DeletePointerFunctor<TextureBlock>());
				textureBlocks.clear();
			}
		};

	private:
		float m_gridWidth;
		float m_leftmost;
		std::vector<Grid*> m_grids; 

#ifdef D2D_ANDROID_NATIVE
		android_app* m_pApplication;
#endif

		friend class GroundSurface;

	}; // GroundSurfaceLoader
}

#endif // _MOTOX_GROUND_SURFACE_LOADER_H_