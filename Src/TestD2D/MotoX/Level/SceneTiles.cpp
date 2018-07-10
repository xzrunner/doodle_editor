#include "SceneTiles.h"
#include "SpriteGridScene.h"

#include "Tools/defs.h"

using namespace motox;

SceneTiles::SceneTiles(d2d::Context* pContext,
					   int scene, int level)
	: m_loader(pContext, TILES_DATA_FILENAME, scene, level)
	, m_texInfo(false)
	, m_leftGridID(-1)
	, m_rightGridID(-1)
	, m_indicesSize(0)
{
	m_loader.loadFromFile(false);
	initTextureInfo(pContext);
}

void SceneTiles::draw() const
{
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	m_texInfo.getTexture()->bind();

	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(2, GL_FLOAT, 0, m_vertices);

	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glTexCoordPointer(2, GL_FLOAT, 0, m_texCoords);

	glDrawElements(GL_TRIANGLES, m_indicesSize, GL_UNSIGNED_SHORT, m_indices);

	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);

	m_texInfo.getTexture()->unbind();

	glDisable(GL_BLEND);
}

void SceneTiles::update(const d2d::Vector& center)
{
	int left = 0, right = 0;
	SpriteGridScene::updateGridRegionMultiLayers(center, m_loader, left, right);

	if (left > right) 
	{
		m_indicesSize = 0;
		m_leftGridID = m_rightGridID = -1;
		return;
	}

	if (left == m_loader.m_internals[0].size() || right == -1) return;
	if (left == m_leftGridID && right == m_rightGridID) return;

	size_t verticesBase = 0, indicesBase = 0;
	for (size_t i = 0, n = m_loader.m_internals.size(); i < n; ++i)
	{
		if (left > 1 && left - 1 < (int)(m_loader.m_intersects[i].size()))
			loadTilesInfo(m_loader.m_intersects[i][left - 1], verticesBase, indicesBase);
		for (int j = left; j <= right; ++j)
		{
			loadTilesInfo(m_loader.m_internals[i][j], verticesBase, indicesBase);
			if (j <= right && j < (int)(m_loader.m_intersects[i].size()))
				loadTilesInfo(m_loader.m_intersects[i][j], verticesBase, indicesBase);
		}
	}
	m_indicesSize = indicesBase;

	m_leftGridID = left;
	m_rightGridID = right;
}

void SceneTiles::initTextureInfo(d2d::Context* pContext)
{
#ifdef D2D_WINDOWS
	std::string imgPath = RESOURCE_ROOT + TILES_TEXTURE_FILENAME;

	std::ifstream finImg(imgPath.c_str());
	if (finImg.fail()) imgPath = TILES_TEXTURE_FILENAME;
	finImg.close();
#elif defined D2D_ANDROID_NATIVE
	std::string imgPath = TILES_TEXTURE_FILENAME;
#elif defined D2D_ANDROID_JNI
	std::string imgPath = TILES_TEXTURE_FILENAME;
#endif
	d2d::Texture* texture = pContext->m_graphicsService->registerTexture(imgPath);
	m_texInfo.setTexture(texture);
	texture->load();

#ifdef D2D_WINDOWS
	std::string infoPath = RESOURCE_ROOT + TILES_TEXTURE_INFO_FILENAME;

	std::ifstream finInfo(infoPath.c_str());
	if (finInfo.fail()) infoPath = TILES_TEXTURE_INFO_FILENAME;
	finInfo.close();

	m_texInfo.loadFromFile(infoPath);
#elif defined D2D_ANDROID_NATIVE
	std::string infoPath = TILES_TEXTURE_INFO_FILENAME;
	m_texInfo.loadFromFile(pContext->m_pApplication, infoPath);
#elif defined D2D_ANDROID_JNI
	std::string infoPath = TILES_TEXTURE_INFO_FILENAME;
	m_texInfo.loadFromFile(infoPath);
#endif
}

void SceneTiles::loadTilesInfo(const std::vector<SpriteGridLoader::Entry*>& tiles,
							   size_t& verticesBase, size_t& indicesBase)
{
	for (size_t i = 0, n = tiles.size(); i < n; ++i)
	{
		if (verticesBase + 4 > VERTICES_SIZE)
		{
			assert(0);
			break;
		}

		SpriteGridLoader::Entry* tile = tiles[i];

		const d2d::TextureInfo::Region* pRegion = m_texInfo.getRegion(tile->id);
		const float hWidth = pRegion->width * 0.5f * tile->scale,
			hHeight = pRegion->height * 0.5f * tile->scale;

		const float cosine = cos(tile->angle),
			sine = sin(tile->angle);

		d2d::Vector leftLow, rightLow, rightUp, leftUp;

		leftLow.x = cosine * (-hWidth) - sine * (-hHeight) + tile->pos.x;
		leftLow.y = sine * (-hWidth) + cosine * (-hHeight) + tile->pos.y;

		rightLow.x = cosine * hWidth - sine * (-hHeight) + tile->pos.x;
		rightLow.y = sine * hWidth + cosine * (-hHeight) + tile->pos.y;

		rightUp.x = cosine * hWidth - sine * hHeight + tile->pos.x;
		rightUp.y = sine * hWidth + cosine * hHeight + tile->pos.y;

		leftUp.x = leftLow.x + (rightUp.x - rightLow.x);
		leftUp.y = rightUp.y - (rightLow.y - leftLow.y);

		float tleft = (float) pRegion->left / m_texInfo.getWidth(),
			tlow = (float) (m_texInfo.getHeight() - pRegion->top - pRegion->height) / m_texInfo.getHeight(),
			tright = (float) (pRegion->left + pRegion->width) / m_texInfo.getWidth(),
			tup = (float) (m_texInfo.getHeight() - pRegion->top) / m_texInfo.getHeight();

		if (tile->type & SpriteGridLoader::SPRITE_X_MIRROR)
			std::swap(tleft, tright);
		if (tile->type & SpriteGridLoader::SPRITE_Y_MIRROR)
			std::swap(tlow, tup);

		size_t base = verticesBase * 2;
		// left-low
		m_vertices[base] = leftLow.x;
		m_texCoords[base] = tleft;
		++base;
		m_vertices[base] = leftLow.y;
		m_texCoords[base] = tlow;
		++base;
		// right-low
		m_vertices[base] = rightLow.x;
		m_texCoords[base] = tright;
		++base;
		m_vertices[base] = rightLow.y;
		m_texCoords[base] = tlow;
		++base;
		// right-up
		m_vertices[base] = rightUp.x;
		m_texCoords[base] = tright;
		++base;
		m_vertices[base] = rightUp.y;
		m_texCoords[base] = tup;
		++base;
		// left-up
		m_vertices[base] = leftUp.x;
		m_texCoords[base] = tleft;
		++base;
		m_vertices[base] = leftUp.y;
		m_texCoords[base] = tup;
		++base;

		m_indices[indicesBase++] = verticesBase + 0;
		m_indices[indicesBase++] = verticesBase + 1;
		m_indices[indicesBase++] = verticesBase + 2;

		m_indices[indicesBase++] = verticesBase + 0;
		m_indices[indicesBase++] = verticesBase + 2;
		m_indices[indicesBase++] = verticesBase + 3;

		verticesBase += 4;
	}
}