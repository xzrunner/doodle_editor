#ifndef _DEDITOR_POLYGON_EDIT_PACKAGE_FILE_IO_H_
#define _DEDITOR_POLYGON_EDIT_PACKAGE_FILE_IO_H_

#include "Task/AutomaticMerge/FileAdapter.h"

namespace deditor
{
	namespace polygon_edit
	{
		class PackageFileIO
		{
		public:
			PackageFileIO(const automatic_merge::FileAdapter& merged, 
				float gridWidth);
			~PackageFileIO();

			void storeToFile(const wxString& filepath, 
				const std::vector<wxgui::Layer*>& layers);
			void loadFromFile(const wxString& filepath,
				std::vector<wxgui::Layer*>& layers);

			void storeToTextFile(const wxString& filepath,
				const std::vector<wxgui::Layer*>& layers);

		private:
			struct Layer;

			void initAllDataRegion(std::vector<wxgui::Layer*> layers);
			void initGridsShapes(std::vector<wxgui::Layer*> layers);
			void initGridTriangles();
			void filterTriangles(const std::vector<f2Vec2>& src, float left, float right, 
				std::vector<f2Vec2>& dst);
			void filterTriangles(const std::vector<f2Vec2>& srcTris, const std::vector<f2Vec2>& srcTexCoords, 
				float left, float right, std::vector<f2Vec2>& dstTris, std::vector<f2Vec2>& dstTexCoords);
			void storeToFile(std::ofstream& fout);

			void loadToStagePanel(std::vector<wxgui::Layer*>& layers);

		private:
			struct Utility
			{
				static void transToIndices(const std::vector<f2Vec2>& src, 
					std::vector<f2Vec2>& dst, std::vector<int>& indices); 

				static void storeIndicesData(std::ofstream& fout, const std::vector<f2Vec2>& vertices, 
					const std::vector<int>& indices);
				static void loadIndicesData(std::ifstream& fin, std::vector<f2Vec2>& vertices, 
					std::vector<int>& indices);

				static void storeIndicesDataCompress(std::ofstream& fout, const std::vector<f2Vec2>& vertices, 
					const std::vector<int>& indices);

				static void storeIndicesDataCompressOffset(std::ofstream& fout, const std::vector<f2Vec2>& vertices, 
					const std::vector<int>& indices);
			};

			struct ColorBlock
			{
				f2Colorf color;
				std::vector<f2Vec2> triangles;

				void store(std::ofstream& fout);
				void load(std::ifstream& fin);

			private:
				static void transToVertexIndices(const std::vector<f2Vec2>& src, 
					std::vector<f2Vec2>& dst, std::vector<int>& dstIndices);
			};

			struct TextureBlock
			{
				unsigned int id;
				std::vector<f2Vec2> vertices;
				std::vector<f2Vec2> texCoords;

				TextureBlock() : id(-1) {}

				void store(std::ofstream& fout);
				void load(std::ifstream& fin);
			};

			struct Grid
			{
				std::vector<wxgui::IShape*> shapes;

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
			const automatic_merge::FileAdapter& m_merged;

			float m_gridWidth;
			float m_leftmost, m_rightmost;
			std::vector<Grid*> m_grids;

		}; // PackageFileIO
	}
}

#endif // _DEDITOR_POLYGON_EDIT_PACKAGE_FILE_IO_H_