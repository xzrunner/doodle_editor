#include "PackageFileIO.h"
#include "FileIO.h"

using namespace deditor;
using namespace deditor::polygon_edit;

PackageFileIO::PackageFileIO(const automatic_merge::FileAdapter& merged,
							 float gridWidth)
	: m_merged(merged)
	, m_gridWidth(gridWidth)
	, m_leftmost(FLOAT_MAX)
	, m_rightmost(-FLOAT_MAX)
{
}

PackageFileIO::~PackageFileIO()
{
	for_each(m_grids.begin(), m_grids.end(), DeletePointerFunctor<Grid>());
	m_grids.clear();
}

void PackageFileIO::storeToFile(const wxString& filepath,
								const std::vector<wxgui::Layer*>& layers)
{
	initAllDataRegion(layers);
	initGridsShapes(layers);
	initGridTriangles();

	std::ofstream fout(filepath.fn_str(), std::ios::out | std::ios::binary);
	storeToFile(fout);
	fout.close();
}

void PackageFileIO::loadFromFile(const wxString& filepath,
								 std::vector<wxgui::Layer*>& layers)
{
	std::ifstream fin(filepath.fn_str(), std::ios::in | std::ios::binary);

	fin.read(reinterpret_cast<char*>(&m_leftmost), sizeof(float));
	fin.read(reinterpret_cast<char*>(&m_gridWidth), sizeof(float));

	size_t gridSize = 0;
	fin.read(reinterpret_cast<char*>(&gridSize), sizeof(size_t));
	m_grids.reserve(gridSize);
	for (size_t i = 0; i < gridSize; ++i)
	{
		Grid* grid = new Grid;

		size_t colorSize = 0;
		fin.read(reinterpret_cast<char*>(&colorSize), sizeof(size_t));
		grid->colorBlocks.reserve(colorSize);
		for (size_t j = 0; j < colorSize; ++j)
		{
			ColorBlock* block = new ColorBlock;
			block->load(fin);
			grid->colorBlocks.push_back(block);
		}

		size_t textureSize = 0;
		fin.read(reinterpret_cast<char*>(&textureSize), sizeof(size_t));
		grid->textureBlocks.reserve(textureSize);
		for (size_t j = 0; j < textureSize; ++j)
		{
			TextureBlock* block = new TextureBlock;
			block->load(fin);
			grid->textureBlocks.push_back(block);
		}

		m_grids.push_back(grid);
	}

	fin.close();

	loadToStagePanel(layers);
}

void PackageFileIO::storeToTextFile(const wxString& filepath,
									const std::vector<wxgui::Layer*>& layers)
{
	std::vector<wxgui::Layer*> layersFliterd = layers;

	std::vector<wxgui::PolygonShape*> polys;
	FileIO::filterPolygonLayer(layersFliterd);
	for (size_t i = 0, n = layersFliterd.size(); i < n; ++i)
	{
		const std::vector<wxgui::IShape*>& shapes = layersFliterd[i]->getShapes();
		for (size_t j = 0, m = shapes.size(); j < m; ++j)
		{
			wxgui::PolygonShape* poly = dynamic_cast<wxgui::PolygonShape*>(shapes[j]);
			if (poly && poly->m_fillingType == wxgui::PolygonShape::e_Texture)
				polys.push_back(poly);
		}
	}

	std::ofstream fout(filepath.fn_str());

	int triCount = 0;
	for (size_t i = 0, n = polys.size(); i < n; ++i)
		triCount += polys[i]->m_fillingVertices.size() / 3;
	fout << triCount << '\n';

	for (size_t i = 0, n = polys.size(); i < n; ++i)
	{
		wxgui::PolygonShape* poly = polys[i];
		for (size_t j = 0, m = poly->m_fillingVertices.size(); j < m; ++j)
			fout << poly->m_fillingVertices[j] << " ";
	}
	fout << '\n';
	for (size_t i = 0, n = polys.size(); i < n; ++i)
	{
		wxgui::PolygonShape* poly = polys[i];
		for (size_t j = 0, m = poly->m_fillingTexCoords.size(); j < m; ++j)
			fout << poly->m_fillingTexCoords[j] << " ";
	}

	fout.close();
}

void PackageFileIO::initAllDataRegion(std::vector<wxgui::Layer*> layers)
{
	m_leftmost = FLOAT_MAX;
	m_rightmost = -FLOAT_MAX;

	for (size_t i = 0, n = layers.size(); i < n; ++i)
	{
		const std::vector<wxgui::IShape*>& shapes = layers[i]->getShapes();
		for (size_t j = 0, m = shapes.size(); j < m; ++j)
		{
			const f2AABB& aabb = shapes[j]->getAABB();
			if (aabb.xMin < m_leftmost) m_leftmost = aabb.xMin;
			if (aabb.xMax > m_rightmost) m_rightmost = aabb.xMax;
		}
	}
}

void PackageFileIO::initGridsShapes(std::vector<wxgui::Layer*> layers)
{
	const size_t gridSize = std::ceil((m_rightmost - m_leftmost) / m_gridWidth);
	for (size_t i = 0; i < gridSize; ++i)
		m_grids.push_back(new Grid);

	for (size_t i = 0, n = layers.size(); i < n; ++i)
	{
		const std::vector<wxgui::IShape*>& shapes = layers[i]->getShapes();
		for (size_t j = 0, m = shapes.size(); j < m; ++j)
		{
			const f2AABB& aabb = shapes[j]->getAABB();
			const int iStart = (aabb.xMin - m_leftmost) / m_gridWidth,
				iEnd = (aabb.xMax - m_leftmost) / m_gridWidth;
			for (size_t k = iStart; k <= iEnd; ++k)
				m_grids[k]->shapes.push_back(shapes[j]);
		}
	}
}

void PackageFileIO::initGridTriangles()
{
	float left = m_leftmost, right = left + m_gridWidth;
	for (size_t i = 0, n = m_grids.size(); i < n; ++i)
	{
		Grid* grid = m_grids[i];
		for (size_t j = 0, m = grid->shapes.size(); j < m; ++j)
		{
			wxgui::PolygonShape* poly = dynamic_cast<wxgui::PolygonShape*>(grid->shapes[j]);

			if (poly->m_fillingType == wxgui::PolygonShape::e_Color)
			{
				ColorBlock* block = new ColorBlock;
				block->color = poly->m_fillingColor;
				filterTriangles(poly->m_fillingVertices, left, right, block->triangles);
				if (block->triangles.empty())
					delete block;
				else
					grid->colorBlocks.push_back(block);
			}
			else if (poly->m_fillingType == wxgui::PolygonShape::e_Texture)
			{
				TextureBlock* block = new TextureBlock;
				filterTriangles(poly->m_fillingVertices, poly->m_fillingTexCoords, left, right,
					block->vertices, block->texCoords);
				if (block->vertices.empty())
				{
					delete block;
				}
				else
				{
					automatic_merge::FileAdapter::Item texRegion;
					for (size_t k = 0, l = m_merged.m_data.size(); k < l; ++k)
					{
						if (m_merged.m_data[k].filepath == poly->m_fillingTexture->getFilepath())
						{
							block->id = k;
							texRegion = m_merged.m_data[k];
							break;
						}
					}
					assert(block->id != -1);

					for (size_t k = 0, l = block->texCoords.size(); k < l; ++k)
					{
						block->texCoords[k].x = (texRegion.left + texRegion.width * block->texCoords[k].x) / m_merged.m_width;
						block->texCoords[k].y = ((m_merged.m_height - texRegion.top - texRegion.height) + texRegion.height * block->texCoords[k].y) / m_merged.m_height;
					}

					grid->textureBlocks.push_back(block);
				}
			}
		}

		left = right;
		right += m_gridWidth;
	}
}

void PackageFileIO::filterTriangles(const std::vector<f2Vec2>& src, float left, float right, 
									std::vector<f2Vec2>& dst)
{
	int index = 0;
	for (size_t i = 0, n = src.size() / 3; i < n; ++i)
	{
 		//bool bValid = false;
 		//for (size_t j = index; j < index + 3; ++j)
 		//{
 		//	const f2Vec2& p = src[j];
 		//	if (p.x > left && p.x < right)
 		//	{
 		//		bValid = true;
 		//		break;
 		//	}
 		//}

		bool bValid = true;
		for (size_t j = index; j < index + 3; ++j)
		{
			const f2Vec2& p = src[j];
			if (p.x < left || p.x > right)
			{
				bValid = false;
				break;
			}
		}

		if (!bValid)
		{
			const float center = (src[index].x + src[index+1].x + src[index+2].x) / 3;
			if (center > left && center < right)
				bValid = true;
		}
		
		if (bValid)
		{
			for (size_t j = index; j < index + 3; ++j)
				dst.push_back(src[j]);
		}

		index += 3;
	}
}

void PackageFileIO::filterTriangles(const std::vector<f2Vec2>& srcTris, const std::vector<f2Vec2>& srcTexCoords, 
									float left, float right, std::vector<f2Vec2>& dstTris, std::vector<f2Vec2>& dstTexCoords)
{
	int index = 0;
	for (size_t i = 0, n = srcTris.size() / 3; i < n; ++i)
	{
		bool bValid = false;
		for (size_t j = index; j < index + 3; ++j)
		{
			const f2Vec2& p = srcTris[j];
			if (p.x > left && p.x < right)
			{
				bValid = true;
				break;
			}
		}
		if (!bValid)
		{
			const float center = (srcTris[index].x + srcTris[index+1].x + srcTris[index+2].x) / 3;
			if (center > left && center < right)
				bValid = true;
		}

		if (bValid)
		{
			for (size_t j = index; j < index + 3; ++j)
				dstTris.push_back(srcTris[j]);
			for (size_t j = index; j < index + 3; ++j)
				dstTexCoords.push_back(srcTexCoords[j]);
		}

		index += 3;
	}
}

void PackageFileIO::storeToFile(std::ofstream& fout)
{
	fout.write(reinterpret_cast<const char*>(&m_leftmost), sizeof(float));
	fout.write(reinterpret_cast<const char*>(&m_gridWidth), sizeof(float));

	size_t gridSize = m_grids.size();
	fout.write(reinterpret_cast<const char*>(&gridSize), sizeof(size_t));
	for (size_t i = 0; i < gridSize; ++i)
	{
		Grid* grid = m_grids[i];

		size_t colorSize = grid->colorBlocks.size();
		fout.write(reinterpret_cast<const char*>(&colorSize), sizeof(size_t));
		for (size_t j = 0; j < colorSize; ++j)
			grid->colorBlocks[j]->store(fout);

		size_t textureSize = grid->textureBlocks.size();
		fout.write(reinterpret_cast<const char*>(&textureSize), sizeof(size_t));
		for (size_t j = 0; j < textureSize; ++j)
			grid->textureBlocks[j]->store(fout);
	}
}

void PackageFileIO::loadToStagePanel(std::vector<wxgui::Layer*>& layers)
{
	wxgui::Layer* layer = new wxgui::Layer;

	for (size_t i = 0, n = m_grids.size(); i < n; ++i)
	{
		Grid* grid = m_grids[i];

		for (size_t j = 0, m = grid->colorBlocks.size(); j < m; ++j)
		{
			ColorBlock* block = grid->colorBlocks[j];

			wxgui::PolygonShape* poly = new wxgui::PolygonShape(std::vector<f2Vec2>());
			poly->m_fillingType = wxgui::PolygonShape::e_Color;
			poly->m_fillingColor = block->color;
			poly->m_fillingVertices = block->triangles;
			layer->insert(poly);
		}

		for (size_t j = 0, m = grid->textureBlocks.size(); j < m; ++j)
		{
			TextureBlock* block = grid->textureBlocks[j];

			wxgui::PolygonShape* poly = new wxgui::PolygonShape(std::vector<f2Vec2>());
			poly->m_fillingType = wxgui::PolygonShape::e_Texture;
			poly->m_fillingTexture = static_cast<wxgui::ImageSymbol*>(wxgui::SymbolMgr::Instance()->getSymbol(m_merged.m_data[block->id].filepath));
			poly->m_fillingVertices = block->vertices;
			poly->m_fillingTexCoords = block->texCoords;
			layer->insert(poly);
		}
	}
 
	layers.push_back(layer);
}

//////////////////////////////////////////////////////////////////////////
// class PackageFileIO::Utility
//////////////////////////////////////////////////////////////////////////

void PackageFileIO::Utility::
transToIndices(const std::vector<f2Vec2>& src, std::vector<f2Vec2>& dst, 
			   std::vector<int>& indices)
{
	std::map<f2Vec2, int, PosCmp> mapPosIndex;
	for (size_t i = 0, n = src.size(); i < n; ++i)
		mapPosIndex.insert(std::make_pair(src[i], 0));

	dst.clear();
	dst.reserve(mapPosIndex.size());
	std::map<f2Vec2, int, PosCmp>::iterator itr = mapPosIndex.begin();
	for (int i = 0; itr != mapPosIndex.end(); ++itr, ++i)
	{
		dst.push_back(itr->first);
		itr->second = i;
	}

	indices.clear();
	indices.reserve(src.size());
	for (size_t i = 0, n = src.size(); i < n; ++i)
	{
		std::map<f2Vec2, int, PosCmp>::iterator itr = mapPosIndex.find(src[i]);
		assert(itr != mapPosIndex.end());
		indices.push_back(itr->second);
	}
}

void PackageFileIO::Utility::
storeIndicesData(std::ofstream& fout, const std::vector<f2Vec2>& vertices, 
				 const std::vector<int>& indices)
{
	size_t verticesSize = vertices.size();
	if (verticesSize >= 256)
		throw std::exception("PackageFileIO::Utility::storeIndicesData verticesSize over 256");
	fout.write(reinterpret_cast<const char*>(&verticesSize), sizeof(byte));
	for (size_t i = 0, n = vertices.size(); i < n; ++i)
	{
		fout.write(reinterpret_cast<const char*>(&vertices[i].x), sizeof(float));
		fout.write(reinterpret_cast<const char*>(&vertices[i].y), sizeof(float));
	}

	size_t indicesSize = indices.size();
	fout.write(reinterpret_cast<const char*>(&indicesSize), sizeof(size_t));
	for (size_t i = 0, n = indices.size(); i < n; ++i)
		fout.write(reinterpret_cast<const char*>(&indices[i]), sizeof(byte));
}

void PackageFileIO::Utility::
loadIndicesData(std::ifstream& fin, std::vector<f2Vec2>& vertices, 
				std::vector<int>& indices)
{
	size_t verticesSize;
	fin.read(reinterpret_cast<char*>(&verticesSize), sizeof(byte));
	vertices.clear();
	vertices.reserve(verticesSize);
	for (size_t i = 0; i < verticesSize; ++i)
	{
		f2Vec2 pos;
		fin.read(reinterpret_cast<char*>(&pos.x), sizeof(float));
		fin.read(reinterpret_cast<char*>(&pos.y), sizeof(float));
		vertices.push_back(pos);
	}

	size_t indicesSize;
	fin.read(reinterpret_cast<char*>(&indicesSize), sizeof(size_t));
	indices.clear();
	indices.reserve(indicesSize);
	for (size_t i = 0; i < indicesSize; ++i)
	{
		int index = 0;
		fin.read(reinterpret_cast<char*>(&index), sizeof(byte));
		indices.push_back(index);
	}
}

void PackageFileIO::Utility::
storeIndicesDataCompress(std::ofstream& fout, const std::vector<f2Vec2>& vertices, 
						 const std::vector<int>& indices)
{
	size_t verticesSize = vertices.size();
	if (verticesSize >= 256)
		throw std::exception("PackageFileIO::Utility::storeIndicesData verticesSize over 256");
	fout.write(reinterpret_cast<const char*>(&verticesSize), sizeof(byte));

	float xMin = FLOAT_MAX, xMax = -FLOAT_MAX,
		yMin = FLOAT_MAX, yMax = -FLOAT_MAX;
	for (size_t i = 0, n = vertices.size(); i < n; ++i)
	{
		if (vertices[i].x < xMin) 
			xMin = vertices[i].x;
		if (vertices[i].x > xMax) 
			xMax = vertices[i].x;
		if (vertices[i].y < yMin) 
			yMin = vertices[i].y;
		if (vertices[i].y > yMax) 
			yMax = vertices[i].y;
	}
	const float dx = (xMax - xMin) / 255.0f,
		dy = (yMax - yMin) / 255.0f;
	fout.write(reinterpret_cast<const char*>(&xMin), sizeof(float));
	fout.write(reinterpret_cast<const char*>(&dx), sizeof(float));
	fout.write(reinterpret_cast<const char*>(&yMin), sizeof(float));
	fout.write(reinterpret_cast<const char*>(&dy), sizeof(float));
	for (size_t i = 0, n = vertices.size(); i < n; ++i)
	{
		const int x = (dx == 0 ? 0: (int)((vertices[i].x - xMin) / dx + 0.5f));
		assert(x >= 0 && x <= 255);
		fout.write(reinterpret_cast<const char*>(&x), sizeof(byte));

		const int y = (dy == 0 ? 0 : (int)((vertices[i].y - yMin) / dy + 0.5f));
		assert(y >= 0 && y <= 255);
		fout.write(reinterpret_cast<const char*>(&y), sizeof(byte));
	}

	size_t indicesSize = indices.size();
	fout.write(reinterpret_cast<const char*>(&indicesSize), sizeof(size_t));
	for (size_t i = 0, n = indices.size(); i < n; ++i)
		fout.write(reinterpret_cast<const char*>(&indices[i]), sizeof(byte));
}

void PackageFileIO::Utility::
storeIndicesDataCompressOffset(std::ofstream& fout, const std::vector<f2Vec2>& vertices, 
							   const std::vector<int>& indices)
{
	size_t verticesSize = vertices.size();
	if (verticesSize >= 256)
		throw std::exception("PackageFileIO::Utility::storeIndicesData verticesSize over 256");
	fout.write(reinterpret_cast<const char*>(&verticesSize), sizeof(byte));

	//////////////////////////////////////////////////////////////////////////

	static const int GRID_SIZE = 20;

	float xMin = FLOAT_MAX, xMax = -FLOAT_MAX,
		yMin = FLOAT_MAX, yMax = -FLOAT_MAX;
	for (size_t i = 0, n = vertices.size(); i < n; ++i)
	{
		if (vertices[i].x < xMin) 
			xMin = vertices[i].x;
		if (vertices[i].x > xMax) 
			xMax = vertices[i].x;
		if (vertices[i].y < yMin) 
			yMin = vertices[i].y;
		if (vertices[i].y > yMax) 
			yMax = vertices[i].y;
	}
	const float edge = std::min((xMax - xMin) / GRID_SIZE, (yMax - yMin) / GRID_SIZE);
	const size_t xSize = std::ceil((xMax - xMin) / edge),
		ySize = std::ceil((yMax - yMin) / edge);

	std::vector<std::vector<f2Vec2> > grids;
//	grids.resize();

	//////////////////////////////////////////////////////////////////////////

	size_t indicesSize = indices.size();
	fout.write(reinterpret_cast<const char*>(&indicesSize), sizeof(size_t));
	for (size_t i = 0, n = indices.size(); i < n; ++i)
		fout.write(reinterpret_cast<const char*>(&indices[i]), sizeof(byte));
}

//////////////////////////////////////////////////////////////////////////
// class PackageFileIO::ColorBlock
//////////////////////////////////////////////////////////////////////////

void PackageFileIO::ColorBlock::
store(std::ofstream& fout)
{
	unsigned int pcolor = color.pack();
	fout.write(reinterpret_cast<const char*>(&pcolor), sizeof(unsigned int));

	std::vector<f2Vec2> vertices;
	std::vector<int> indices;
	PackageFileIO::Utility::transToIndices(triangles, vertices, indices);

//	PackageFileIO::Utility::storeIndicesData(fout, vertices, indices);
	PackageFileIO::Utility::storeIndicesDataCompress(fout, vertices, indices);
}

void PackageFileIO::ColorBlock::
load(std::ifstream& fin)
{
	triangles.clear();

	unsigned int pcolor = 0;
	fin.read(reinterpret_cast<char*>(&pcolor), sizeof(unsigned int));
	color.unpack(pcolor);

	std::vector<f2Vec2> vertices;
	std::vector<int> indices;
	PackageFileIO::Utility::loadIndicesData(fin, vertices, indices);

	triangles.clear();
	triangles.reserve(indices.size());
	for (size_t i = 0, n = indices.size(); i < n; ++i)
		triangles.push_back(vertices[indices[i]]);
}

//////////////////////////////////////////////////////////////////////////
// class PackageFileIO::TextureBlock
//////////////////////////////////////////////////////////////////////////

void PackageFileIO::TextureBlock::
store(std::ofstream& fout)
{
	fout.write(reinterpret_cast<const char*>(&id), sizeof(unsigned int));
	{
		std::vector<f2Vec2> dst;
		std::vector<int> indices;
		PackageFileIO::Utility::transToIndices(vertices, dst, indices);
//		PackageFileIO::Utility::storeIndicesData(fout, dst, indices);
		PackageFileIO::Utility::storeIndicesDataCompress(fout, dst, indices);
	}
	{
		std::vector<f2Vec2> dst;
		std::vector<int> indices;
		PackageFileIO::Utility::transToIndices(texCoords, dst, indices);
//		PackageFileIO::Utility::storeIndicesData(fout, dst, indices);
		PackageFileIO::Utility::storeIndicesDataCompress(fout, dst, indices);
	}
}

void PackageFileIO::TextureBlock::
load(std::ifstream& fin)
{
	fin.read(reinterpret_cast<char*>(&id), sizeof(unsigned int));
	{
		std::vector<f2Vec2> points;
		std::vector<int> indices;
		PackageFileIO::Utility::loadIndicesData(fin, points, indices);

		vertices.clear();
		vertices.reserve(indices.size());
		for (size_t i = 0, n = indices.size(); i < n; ++i)
			vertices.push_back(points[indices[i]]);
	}
	{
		std::vector<f2Vec2> points;
		std::vector<int> indices;
		PackageFileIO::Utility::loadIndicesData(fin, points, indices);

		texCoords.clear();
		texCoords.reserve(indices.size());
		for (size_t i = 0, n = indices.size(); i < n; ++i)
			texCoords.push_back(points[indices[i]]);
	}
}