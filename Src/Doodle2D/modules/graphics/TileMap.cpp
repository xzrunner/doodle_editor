#include "TileMap.h"

#include "common/Log.h"

#include <GLES/gl.h>
#include <setjmp.h>

#include "libraries/rapidxml.hpp"

namespace rapidxml 
{
	static jmp_buf sJmpBuffer;
	void parse_error_handler(const char* pWhat, void* pWhere) 
	{
		d2d::Log::error("Error while parsing TMX file.");
		d2d::Log::error(pWhat);
		longjmp(sJmpBuffer, 0);
	}
}

using namespace d2d;

#ifdef D2D_WINDOWS
TileMap::TileMap(const std::string& pPath, Texture* pTexture, Vector* pLocation)
	: m_resource(pPath), m_vertexComponents(5)
{
	m_location = pLocation;

	m_texture = pTexture;
	m_vertexBuffer = m_indexBuffer = 0;
	m_vertexCount = m_indexCount = 0;

	m_height = m_width = 0;
	m_tileHeight = m_tileWidth = 0;
	m_tileCount = m_tileXCount = 0;
}
#elif defined D2D_ANDROID_NATIVE
TileMap::TileMap(android_app* pApplication, const std::string& pPath,
								 Texture* pTexture, Vector* pLocation)
	: m_resource(pApplication, pPath), m_vertexComponents(5)
{
	m_location = pLocation;

	m_texture = pTexture;
	m_vertexBuffer = m_indexBuffer = 0;
	m_vertexCount = m_indexCount = 0;

	m_height = m_width = 0;
	m_tileHeight = m_tileWidth = 0;
	m_tileCount = m_tileXCount = 0;
}
#elif defined D2D_ANDROID_JNI
TileMap::TileMap(const std::string& pPath, Texture* pTexture, Vector* pLocation)
	: m_resource(pPath), m_vertexComponents(5)
{
	m_location = pLocation;

	m_texture = pTexture;
	m_vertexBuffer = m_indexBuffer = 0;
	m_vertexCount = m_indexCount = 0;

	m_height = m_width = 0;
	m_tileHeight = m_tileWidth = 0;
	m_tileCount = m_tileXCount = 0;
}
#endif

status TileMap::load()
{
	GLenum lErrorResult;
	uint8_t* lVertexBuffer = NULL, *lIndexBuffer = NULL;
	uint32_t lVertexBufferSize, lIndexBufferSize;

	// Loads tiles and creates temporary vertex/index buffers.
	int32_t* lTiles = loadFile();
	if (lTiles == NULL) goto ERROR;
	loadVertices(lTiles, &lVertexBuffer, &lVertexBufferSize);
	if (lVertexBuffer == NULL) goto ERROR;
	loadIndexes(&lIndexBuffer,  &lIndexBufferSize);
	if (lIndexBuffer == NULL) goto ERROR;

	// Generates new buffer names.
	glGenBuffers(1, &m_vertexBuffer);
	glGenBuffers(1, &m_indexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);

	// Loads buffers into OpenGL.
	glBufferData(GL_ARRAY_BUFFER, lVertexBufferSize * sizeof(GLfloat), lVertexBuffer, GL_STATIC_DRAW);
	lErrorResult = glGetError();
	if (lErrorResult != GL_NO_ERROR) goto ERROR;

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, lIndexBufferSize * sizeof(GLushort), lIndexBuffer, GL_STATIC_DRAW);
	lErrorResult = glGetError();
	if (lErrorResult != GL_NO_ERROR) goto ERROR;

	// Unbinds buffers.
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	delete[] lTiles; delete[] lVertexBuffer;
	delete[] lIndexBuffer;
	return STATUS_OK;

ERROR:
	Log::error("Error loading tilemap");
	unload();
	delete[] lTiles; delete[] lVertexBuffer;
	delete[] lIndexBuffer;
	return STATUS_KO;
}

void TileMap::unload()
{
	m_height     = 0, m_width      = 0;
	m_tileHeight = 0, m_tileWidth  = 0;
	m_tileCount  = 0, m_tileXCount = 0;
	if (m_vertexBuffer != 0) 
	{
		glDeleteBuffers(1, &m_vertexBuffer);
		m_vertexBuffer = 0; m_vertexCount = 0;
	}
	if (m_indexBuffer != 0) 
	{
		glDeleteBuffers(1, &m_indexBuffer);
		m_indexBuffer = 0; m_indexCount = 0;
	}
}

void TileMap::draw()
{
	int32_t lVertexSize     = m_vertexComponents * sizeof(GLfloat);
	GLvoid* lVertexOffset   = (GLvoid*) 0;
	GLvoid* lTexCoordOffset = (GLvoid*) (sizeof(GLfloat) * 3);
	m_texture->bind();

	glPushMatrix();
	glTranslatef((GLfloat)(int32_t(m_location->x + 0.5f)), (GLfloat)(int32_t(m_location->y + 0.5f)), 0.0f);

	// Draws using hardware buffers
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);
	glVertexPointer(3, GL_FLOAT, lVertexSize, lVertexOffset);
	glTexCoordPointer(2, GL_FLOAT, lVertexSize, lTexCoordOffset);
	glDrawElements(GL_TRIANGLES, m_indexCount, GL_UNSIGNED_SHORT, 0 * sizeof(GLushort));
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glPopMatrix();
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);

	m_texture->unbind();
}

int32_t* TileMap::loadFile()
{
	using namespace rapidxml;
	xml_document<> lXmlDocument;
	xml_node<>* lXmlMap, *lXmlTileset, *lXmlLayer;
	xml_node<>* lXmlTile, *lXmlData;
	xml_attribute<>* lXmlTileWidth, *lXmlTileHeight;
	xml_attribute<>* lXmlWidth, *lXmlHeight, *lXmlGID;
	char* lFileBuffer = NULL; int32_t* lTiles = NULL;
	if (m_resource.open() != STATUS_OK) goto ERROR;
	{
		int32_t lLength = m_resource.getLength();
		if (lLength <= 0) goto ERROR;
		const void* lFileBufferTmp = m_resource.bufferize();
		if (lFileBufferTmp == NULL) goto ERROR;
		lFileBuffer = new char[m_resource.getLength() + 1];
		memcpy(lFileBuffer, lFileBufferTmp,m_resource.getLength());
		lFileBuffer[m_resource.getLength()] = '\0';
		m_resource.close();
	}

	// Parses the document. Jumps back here if an error occurs
	try {
		lXmlDocument.parse<parse_default>(lFileBuffer);
	} catch (/*rapidxml::parse_error& parseException*/...) {
		d2d::Log::error("Error while parsing TMX file.");
//		d2d::Log::error(parseException.what());
		goto ERROR;
	}

// 	// Parses the document. Jumps back here if an error occurs
// 	if (setjmp(sJmpBuffer)) goto ERROR;
// 	lXmlDocument.parse<parse_default>(lFileBuffer);

	// Reads XML tags.
	lXmlMap = lXmlDocument.first_node("map");
	if (lXmlMap == NULL) goto ERROR;
	lXmlTileset = lXmlMap->first_node("tileset");
	if (lXmlTileset == NULL) goto ERROR;
	lXmlTileWidth = lXmlTileset->first_attribute("tilewidth");
	if (lXmlTileWidth == NULL) goto ERROR;
	lXmlTileHeight = lXmlTileset->first_attribute("tileheight");
	if (lXmlTileHeight == NULL) goto ERROR;
	lXmlLayer = lXmlMap->first_node("layer");
	if (lXmlLayer == NULL) goto ERROR;
	lXmlWidth = lXmlLayer->first_attribute("width");
	if (lXmlWidth == NULL) goto ERROR;
	lXmlHeight = lXmlLayer->first_attribute("height");
	if (lXmlHeight == NULL) goto ERROR;
	lXmlData = lXmlLayer->first_node("data");
	if (lXmlData == NULL) goto ERROR;

	m_width      = atoi(lXmlWidth->value());
	m_height     = atoi(lXmlHeight->value());
	m_tileWidth  = atoi(lXmlTileWidth->value());
	m_tileHeight = atoi(lXmlTileHeight->value());
	if ((m_width <= 0) || (m_height <= 0) || (m_tileWidth <= 0) || (m_tileHeight <= 0)) goto ERROR;
	m_tileXCount = m_texture->getWidth()/m_tileWidth;
	m_tileCount = m_texture->getHeight()/m_tileHeight * m_tileXCount;
	lTiles = new int32_t[m_width * m_height];
	lXmlTile = lXmlData->first_node("tile");
	for (int32_t lY = m_height - 1; lY >= 0; --lY) 
	{
		for (int32_t lX = 0; lX < m_width; ++lX) 
		{
			if (lXmlTile == NULL) goto ERROR;
			lXmlGID = lXmlTile->first_attribute("gid");
			lTiles[lX + (lY * m_width)] = atoi(lXmlGID->value())-1;
			if (lTiles[lX + (lY * m_width)] < 0) goto ERROR;
			lXmlTile = lXmlTile->next_sibling("tile");
		}
	}
	delete[] lFileBuffer;
	return lTiles;

ERROR:
	m_resource.close();
	delete[] lFileBuffer; delete[] lTiles;
	m_height = 0;     m_width = 0;
	m_tileHeight = 0; m_tileWidth = 0;
	return NULL;
}

void TileMap::loadVertices(int32_t* pTiles, uint8_t** pVertexBuffer, uint32_t* pVertexBufferSize)
{
	m_vertexCount = m_height * m_width * 4;
	*pVertexBufferSize = m_vertexCount * m_vertexComponents;
	GLfloat* lVBuffer = new GLfloat[*pVertexBufferSize];
	*pVertexBuffer = reinterpret_cast<uint8_t*>(lVBuffer);
	int32_t lRowStride = m_width * 2;
	GLfloat lTexelWidth = 1.0f / m_texture->getWidth();
	GLfloat lTexelHeight = 1.0f / m_texture->getHeight();
	int32_t i;
	for (int32_t tileY = 0; tileY < m_height; ++tileY) 
	{
		for (int32_t tileX = 0; tileX < m_width; ++tileX) 
		{
			// Finds current tile index (0 for 1st tile, 1...).
			int32_t lTileSprite = pTiles[tileY * m_width + tileX] % m_tileCount;
			int32_t lTileSpriteX = (lTileSprite % m_tileXCount) * m_tileWidth;
			int32_t lTileSpriteY = (lTileSprite / m_tileXCount) * m_tileHeight;

			// Values to compute vertex offsets in the buffer.
			int32_t lOffsetX1 = tileX * 2;
			int32_t lOffsetX2 = tileX * 2 + 1;
			int32_t lOffsetY1 = (tileY * 2) * (m_width * 2);
			int32_t lOffsetY2 = (tileY * 2 + 1) * (m_width * 2);

			// Vertex positions in the scene.
			GLfloat lPosX1 = (GLfloat)(tileX * m_tileWidth);
			GLfloat lPosX2 = (GLfloat)((tileX + 1) * m_tileWidth);
			GLfloat lPosY1 = (GLfloat)(tileY * m_tileHeight);
			GLfloat lPosY2 = (GLfloat)((tileY + 1) * m_tileHeight);

			// Tile UV coordinates (coordinates origin needs to be
			// translated from top-left to bottom-left origin).
			GLfloat lU1 = (lTileSpriteX) * lTexelWidth;
			GLfloat lU2 = lU1 + (m_tileWidth * lTexelWidth);
			GLfloat lV2 = 1.0f - (lTileSpriteY) * lTexelHeight;
			GLfloat lV1 = lV2 - (m_tileHeight * lTexelHeight);

			// Small shift to limit edge artifacts (1/4 of texel).
			lU1 += lTexelWidth/4.0f;  lU2 -= lTexelWidth/4.0f;
			lV1 += lTexelHeight/4.0f; lV2 -= lTexelHeight/4.0f;

			// 4 vertices per tile in the vertex buffer.
			i = m_vertexComponents * (lOffsetY1 + lOffsetX1);
			lVBuffer[i++] = lPosX1; lVBuffer[i++] = lPosY1;
			lVBuffer[i++] = 0.0f;
			lVBuffer[i++] = lU1;    lVBuffer[i++] = lV1;
			i = m_vertexComponents * (lOffsetY1 + lOffsetX2);
			lVBuffer[i++] = lPosX2; lVBuffer[i++] = lPosY1;
			lVBuffer[i++] = 0.0f;
			lVBuffer[i++] = lU2;    lVBuffer[i++] = lV1;
			i = m_vertexComponents * (lOffsetY2 + lOffsetX1);
			lVBuffer[i++] = lPosX1; lVBuffer[i++] = lPosY2;
			lVBuffer[i++] = 0.0f;
			lVBuffer[i++] = lU1;    lVBuffer[i++] = lV2;
			i = m_vertexComponents * (lOffsetY2 + lOffsetX2);
			lVBuffer[i++] = lPosX2; lVBuffer[i++] = lPosY2;
			lVBuffer[i++] = 0.0f;
			lVBuffer[i++] = lU2;    lVBuffer[i++] = lV2;
		}
	}
}

void TileMap::loadIndexes(uint8_t** pIndexBuffer, uint32_t* pIndexBufferSize)
{
	m_indexCount =  m_height * m_width * 6;
	*pIndexBufferSize = m_indexCount;
	GLushort* lIBuffer = new GLushort[*pIndexBufferSize];
	*pIndexBuffer  = reinterpret_cast<uint8_t*>(lIBuffer);
	int32_t lRowStride = m_width * 2;
	int32_t i = 0;
	for (int32_t tileY = 0; tileY < m_height; tileY++) 
	{
		int32_t lIndexY = tileY * 2;
		for (int32_t tileX = 0; tileX < m_width; tileX++) 
		{
			int32_t lIndexX = tileX * 2;

			// Values to compute vertex offsets in the buffer.
			GLshort lVertIndexY1 = lIndexY * lRowStride;
			GLshort lVertIndexY2 = (lIndexY + 1) * lRowStride;
			GLshort lVertIndexX1 = lIndexX;
			GLshort lVertIndexX2 = lIndexX + 1;

			// 2 triangles per tile in the index buffer.
			lIBuffer[i++] = lVertIndexY1 + lVertIndexX1;
			lIBuffer[i++] = lVertIndexY1 + lVertIndexX2;
			lIBuffer[i++] = lVertIndexY2 + lVertIndexX1;
			lIBuffer[i++] = lVertIndexY2 + lVertIndexX1;
			lIBuffer[i++] = lVertIndexY1 + lVertIndexX2;
			lIBuffer[i++] = lVertIndexY2 + lVertIndexX2;
		}
	}
}
