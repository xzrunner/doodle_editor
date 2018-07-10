#include "GroundSurface.h"

#include "Tools/defs.h"

using namespace motox;

GroundSurface::GroundSurface(d2d::Context* pContext,
							 int scene, int level)
	: m_loader(pContext, scene, level)
	, m_textures(pContext)
{
}

void GroundSurface::draw() const
{
	m_colors.draw();
	m_textures.draw();
}

void GroundSurface::update(const d2d::Vector& center)
{
	int left = static_cast<int>((center.x - (d2d::SCREEN_WIDTH >> 1) - m_loader.m_leftmost) / m_loader.m_gridWidth);
	left = std::min(std::max(left, 0), (int) (m_loader.m_grids.size() - 1));

	int right = static_cast<int>((center.x + (d2d::SCREEN_WIDTH >> 1) - m_loader.m_leftmost) / m_loader.m_gridWidth);
	right = std::max(std::min(right, (int) (m_loader.m_grids.size() - 1)), 0);

	m_colors.update(left, right, m_loader);
	m_textures.update(left, right, m_loader);
}

//////////////////////////////////////////////////////////////////////////
// class GroundSurface::ColorBlockData
//////////////////////////////////////////////////////////////////////////

GroundSurface::ColorBlockData::
ColorBlockData()
	: m_leftGridID(-1), m_rightGridID(-1)
	, m_indicesSize(0)
{
}

void GroundSurface::ColorBlockData::
draw() const
{
	if (m_indicesSize == 0) return;

 	glBindTexture(GL_TEXTURE_2D, NULL);
// 	glDisableClientState(GL_TEXTURE_COORD_ARRAY);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);

	glVertexPointer(2, GL_FLOAT, 0, m_vertices);
	glColorPointer(4, GL_UNSIGNED_BYTE, 0, m_colors);

	glDrawElements(GL_TRIANGLES, m_indicesSize, GL_UNSIGNED_SHORT, m_indices);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
}

void GroundSurface::ColorBlockData::
update(int left, int right, const GroundSurfaceLoader& loader)
{
	assert(left <= right);
	while (left < (int)(loader.m_grids.size()))
	{
		if (loader.m_grids[left]->colorBlocks.empty())
		{
			++left;
			if (left > right) break;
		}
		else
			break;
	}
	while (right >= 0)
	{
		if (loader.m_grids[right]->colorBlocks.empty())
		{
			--right;
			if (right < left) break;
		}
		else
			break;
	}
	if (left > right)
	{
		m_indicesSize = 0;
		m_leftGridID = m_rightGridID = -1;
		return;
	}

	if (left == loader.m_grids.size() || right == -1) return;
	if (left == m_leftGridID && right == m_rightGridID) return;

	size_t verticesBase = 0;
	size_t indicesBase = 0;
	for (int i = left; i <= right; ++i)
	{
		GroundSurfaceLoader::Grid* grid = loader.m_grids[i];
		for (size_t j = 0, m = grid->colorBlocks.size(); j < m; ++j)
		{
			GroundSurfaceLoader::ColorBlock* block = grid->colorBlocks[j];
			if (verticesBase + block->vertices.size() > VERTICES_SIZE
				|| indicesBase + block->indices.size() > VERTICES_SIZE * 3)
			{
				assert(0);
				break;
			}
			memcpy(&m_vertices[verticesBase * 2], &block->vertices[0], sizeof(float) * 2 * block->vertices.size());
			for (size_t i = 0, n = block->vertices.size(); i < n; ++i)
				memcpy(&m_colors[(verticesBase + i) * 4], &block->color.r, 4);
			for (size_t i = 0, n = block->indices.size(); i < n; ++i)
				m_indices[indicesBase + i] = block->indices[i] + verticesBase;
			verticesBase += block->vertices.size();
			indicesBase += block->indices.size();
		}
	}

	m_indicesSize = indicesBase;

 	m_leftGridID = left;
 	m_rightGridID = right;
}

//////////////////////////////////////////////////////////////////////////
// class GroundSurface::TextureBlockData
//////////////////////////////////////////////////////////////////////////

GroundSurface::TextureBlockData::
TextureBlockData(d2d::Context* pContext)
	: m_texInfo(false)
	, m_leftGridID(-1), m_rightGridID(-1)
	, m_verticesSize(0)
{
	initTextureInfo(pContext);
}

void GroundSurface::TextureBlockData::
draw() const
{
	if (m_verticesSize == 0) return;

	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

	m_texInfo.getTexture()->bind();

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glVertexPointer(2, GL_FLOAT, 0, m_vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, m_texCoords);

	glDrawArrays(GL_TRIANGLES, 0, m_verticesSize);

	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);

	m_texInfo.getTexture()->unbind();
}

void GroundSurface::TextureBlockData::
update(int left, int right, const GroundSurfaceLoader& loader)
{
	assert(left <= right);
	while (left < (int)(loader.m_grids.size()))
	{
		if (loader.m_grids[left]->textureBlocks.empty())
		{
			++left;
			if (left > right) break;
		}
		else
			break;
	}
	while (right >= 0)
	{
		if (loader.m_grids[right]->textureBlocks.empty())
		{
			--right;
			if (right < left) break;
		}
		else
			break;
	}
	if (left > right)
	{
		m_verticesSize = 0;
		m_leftGridID = m_rightGridID = -1;
		return;
	}

	if (left == loader.m_grids.size() || right == -1) return;
	if (left == m_leftGridID && right == m_rightGridID) return;

	size_t verticesBase = 0;
	for (int i = left; i <= right; ++i)
	{
		GroundSurfaceLoader::Grid* grid = loader.m_grids[i];
		for (size_t j = 0, m = grid->textureBlocks.size(); j < m; ++j)
		{
			GroundSurfaceLoader::TextureBlock* block = grid->textureBlocks[j];
			if (verticesBase + block->vertices.size() > VERTICES_SIZE)
			{
				assert(0);
				break;
			}
			memcpy(&m_vertices[verticesBase * 2], &block->vertices[0], sizeof(float) * 2 * block->vertices.size());
			memcpy(&m_texCoords[verticesBase * 2], &block->texCoords[0], sizeof(float) * 2 * block->texCoords.size());
			verticesBase += block->vertices.size();
		}
	}

	m_verticesSize = verticesBase;

	m_leftGridID = left;
	m_rightGridID = right;
}

void GroundSurface::TextureBlockData::
initTextureInfo(d2d::Context* pContext)
{
#ifdef D2D_WINDOWS
	std::string path = RESOURCE_ROOT + GROUND_TEXTURE_FILENAME;

	std::ifstream fin(path.c_str());
	if (fin.fail()) path = GROUND_TEXTURE_FILENAME;
	fin.close();
#elif defined D2D_ANDROID_NATIVE
	std::string path = GROUND_TEXTURE_FILENAME;
#elif defined D2D_ANDROID_JNI
	std::string path = GROUND_TEXTURE_FILENAME;
#endif
	d2d::Texture* texture = pContext->m_graphicsService->registerTexture(path);
	m_texInfo.setTexture(texture);
	texture->load();

	m_texInfo.setSizer(256, 256);

	m_texInfo.addRegion(0, 128, 128, 128);
	m_texInfo.addRegion(128, 128, 128, 128);
	m_texInfo.addRegion(0, 0, 128, 128);
	m_texInfo.addRegion(128, 0, 128, 128);
}

////////////////////////////////////////////////////////////////////////////
//// class GroundSurface::TileStencilData
////////////////////////////////////////////////////////////////////////////
//
//GroundSurface::TileStencilData::
//TileStencilData(d2d::Context* pContext)
////	: m_tileStencilBatch(NULL)
//{
//	initTextureInfo(pContext);
//}
//
//GroundSurface::TileStencilData::
//~TileStencilData()
//{
//	for_each(m_layers.begin(), m_layers.end(), DeletePointerFunctor<Layer>());
//	m_layers.clear();
//
////	delete m_tileStencilBatch;
//}
//
//void GroundSurface::TileStencilData::
//draw() const
//{
// 	for (size_t i = 0, n = m_layers.size(); i < n; ++i)
//	{
////		if (i == 3) continue;
// 		m_layers[i]->draw();
//	}
//
////	m_tileStencilBatch->onDraw();
//}
//
//void GroundSurface::TileStencilData::
//update(int left, int right, const GroundSurfaceLoader& loader)
//{
// 	if (m_layers.empty())
// 	{
// 		m_layers.reserve(loader.m_grids[0]->tileStencils.size());
// 		for (size_t i = 0, n = loader.m_grids[0]->tileStencils.size(); i < n; ++i)
// 			m_layers.push_back(new Layer(m_texInfo));
// 	}
// 
// 	for (size_t i = 0, n = m_layers.size(); i < n; ++i)
// 		m_layers[i]->update(i, left, right, loader);
//
//// 	if (!m_tileStencilBatch)
//// 	{
//// 		m_tileStencilBatch = new d2d::TileStencilBatch(m_texInfo.texture, 2000, 500, d2d::SpriteBatch::USAGE_STATIC);
//// 		for (size_t i = 0, n = 3; i < n; ++i)
//// 		{
//// 			for (size_t j = 0, m = loader.m_grids[i]->tileStencils[3].size(); j < m; ++j)
//// 			{
//// 				GroundSurfaceLoader::TileStencil* tile = loader.m_grids[i]->tileStencils[3][j];
//// 				m_tileStencilBatch->add(tile->vertices, tile->indices, tile->texID, tile->leftLow, tile->mesh);
//// 			}
//// 		}
//// 	}
//}
//
//void GroundSurface::TileStencilData::
//initTextureInfo(d2d::Context* pContext)
//{
//#ifdef D2D_WINDOWS
//	std::string path = RESOURCE_ROOT + GROUND_TEXTURE_FILENAME;
//#else
//	std::string path = GROUND_TEXTURE_FILENAME;
//#endif
//	m_texInfo.texture = pContext->m_graphicsService->registerTexture(path);
//	m_texInfo.texture->load();
//
//	m_texInfo.width = m_texInfo.height = 256;
//
//	m_texInfo.regions.push_back(TextureRegion(0, 128, 128, 128));
//	m_texInfo.regions.push_back(TextureRegion(128, 128, 128, 128));
//	m_texInfo.regions.push_back(TextureRegion(0, 0, 128, 128));
//	m_texInfo.regions.push_back(TextureRegion(128, 0, 128, 128));
//}
//
////////////////////////////////////////////////////////////////////////////
//// class GroundSurface::TileStencilData::Layer
////////////////////////////////////////////////////////////////////////////
//
//GroundSurface::TileStencilData::Layer::
//Layer(const TileStencilData::TextureInfo& texInfo)
//	: m_texInfo(texInfo)
//	, m_leftGridID(-1), m_rightGridID(-1)
//	, m_stencilIndicesSize(0), m_textureIndicesSize(0)
//{
//}
//
//void GroundSurface::TileStencilData::Layer::
//draw() const
//{
//	if (m_stencilIndicesSize == 0 || m_textureIndicesSize == 0)
//		return;
//
//	glPushMatrix();
//
//  	glClearStencil(0);
//  	glEnable(GL_STENCIL_TEST);
//  
//  	glClear(GL_STENCIL_BUFFER_BIT); 
//  
//  	glStencilFunc(GL_NEVER, 0x0, 0x0);
//  	glStencilOp(GL_INCR, GL_INCR, GL_INCR);
//  
//  	drawStencil();
//  
//  	glStencilFunc(GL_NOTEQUAL, 0x0, 0x1);
//  	glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
//
//	drawTexture();
//
//	glDisable(GL_STENCIL_TEST);
//
//	glPopMatrix();
//}
//
//void GroundSurface::TileStencilData::Layer::
//update(int index, int left, int right, const GroundSurfaceLoader& loader)
//{
//	assert(left <= right);
//	while (left < loader.m_grids.size())
//	{
//		if (loader.m_grids[left]->tileStencils[index].empty())
//		{
//			++left;
//			if (left > right) break;
//		}
//		else
//			break;
//	}
//	while (right >= 0)
//	{
//		if (loader.m_grids[right]->tileStencils[index].empty())
//		{
//			--right;
//			if (right < left) break;
//		}
//		else
//			break;
//	}
//	if (left > right) 
//	{
//		m_stencilIndicesSize = m_textureIndicesSize = 0;
//		m_leftGridID = m_rightGridID = -1;
//		return;
//	}
//
//	if (left == loader.m_grids.size() || right == -1) return;
//	if (left == m_leftGridID && right == m_rightGridID) return;
//
// 	size_t stencilVerticesBase = 0, stencilIndicesBase = 0;
//	size_t textureVerticesBase = 0, textureIndicesBase = 0;
// 	for (int i = left; i <= right; ++i)
// 	{
// 		GroundSurfaceLoader::Grid* grid = loader.m_grids[i];
// 		for (size_t j = 0, m = grid->tileStencils[index].size(); j < m; ++j)
// 		{
//			GroundSurfaceLoader::TileStencil* tile = grid->tileStencils[index][j];
//
// 			memcpy(&m_stencilVertices[stencilVerticesBase * 2], &tile->vertices[0].x, sizeof(float) * 2 * tile->vertices.size());
// 			for (size_t i = 0, n = tile->indices.size(); i < n; ++i)
// 				m_stencilIndices[stencilIndicesBase + i] = tile->indices[i] + stencilVerticesBase;
// 			stencilVerticesBase += tile->vertices.size();
// 			stencilIndicesBase += tile->indices.size();
//
//			const TextureRegion& region = m_texInfo.regions[tile->texID];
//			for (size_t k = 0, l = tile->mesh.size(); k < l; ++k)
//			{
//				int pos = tile->mesh[k];
//				const float left = tile->leftLow.x + (pos & 0x0000ffff) * region.width,
//					low = tile->leftLow.y + (pos >> 16) * region.height,
//					right = left + region.width,
//					up = low + region.height;
//				const float tleft = (float) region.left / m_texInfo.width,
//					tlow = (float) (m_texInfo.height - region.top - region.height) / m_texInfo.height,
//					tright = (float) (region.left + region.width) / m_texInfo.width,
//					tup = (float) (m_texInfo.height - region.top) / m_texInfo.height;
//
//				size_t base = textureVerticesBase * 2;
//				// left-low
//				m_textureVertices[base] = left;
//				m_textureTexCoords[base] = tleft;
//				++base;
//				m_textureVertices[base] = low;
//				m_textureTexCoords[base] = tlow;
//				++base;
//				// right-low
//				m_textureVertices[base] = right;
//				m_textureTexCoords[base] = tright;
//				++base;
//				m_textureVertices[base] = low;
//				m_textureTexCoords[base] = tlow;
//				++base;
//				// right-up
//				m_textureVertices[base] = right;
//				m_textureTexCoords[base] = tright;
//				++base;
//				m_textureVertices[base] = up;
//				m_textureTexCoords[base] = tup;
//				++base;
//				// left-up
//				m_textureVertices[base] = left;
//				m_textureTexCoords[base] = tleft;
//				++base;
//				m_textureVertices[base] = up;
//				m_textureTexCoords[base] = tup;
//				++base;
//
//				m_textureIndices[textureIndicesBase++] = textureVerticesBase + 0;
//				m_textureIndices[textureIndicesBase++] = textureVerticesBase + 1;
//				m_textureIndices[textureIndicesBase++] = textureVerticesBase + 2;
//
//				m_textureIndices[textureIndicesBase++] = textureVerticesBase + 0;
//				m_textureIndices[textureIndicesBase++] = textureVerticesBase + 2;
//				m_textureIndices[textureIndicesBase++] = textureVerticesBase + 3;
//
//				textureVerticesBase += 4;
//			}
//		}
//	}
//	m_stencilIndicesSize = stencilIndicesBase;
//	m_textureIndicesSize = textureIndicesBase;
//
//	m_leftGridID = left;
//	m_rightGridID = right;
//}
//
//void GroundSurface::TileStencilData::Layer::
//drawStencil() const
//{
//	glEnableClientState(GL_VERTEX_ARRAY);
//	glVertexPointer(2, GL_FLOAT, 0, m_stencilVertices);
//
//	glDrawElements(GL_TRIANGLES, m_stencilIndicesSize, GL_UNSIGNED_SHORT, m_stencilIndices);
//
//	glDisableClientState(GL_VERTEX_ARRAY);
//}
//
//void GroundSurface::TileStencilData::Layer::
//drawTexture() const
//{
//	m_texInfo.texture->bind();
//
//	glEnableClientState(GL_VERTEX_ARRAY);
//	glVertexPointer(2, GL_FLOAT, 0, m_textureVertices);
//
//	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
//	glTexCoordPointer(2, GL_FLOAT, 0, m_textureTexCoords);
//
//	glDrawElements(GL_TRIANGLES, m_textureIndicesSize, GL_UNSIGNED_SHORT, m_textureIndices);
//
//	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
//	glDisableClientState(GL_VERTEX_ARRAY);
//
//	m_texInfo.texture->unbind();
//}