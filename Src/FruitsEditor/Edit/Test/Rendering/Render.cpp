#include "Render.h"
#include "Blackboard.h"
#include "Edit/AbstractView.h"
#include "Dataset/Sprite.h"
#include "Dataset/Texture.h"
#include "Dataset/TextureRegion.h"

#include <GL/GLee.h>

// #include <windows.h>
// #include <GL/wglew.h>

using namespace FEDITOR;
using namespace FEDITOR::TEST_RENDERING;

Blackboard* Render::m_bb = NULL;

void Render::immediateMode(const std::vector<Sprite*>& sprites, AbstractView* view)
{
	if (m_bb->m_isTransparent == 1)
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}
	else 
	{
		glDisable(GL_BLEND);

// 		glDisable(GL_DEPTH_TEST);
// 		glDisable(GL_ALPHA_TEST);
	}

	for (size_t i = 0, n = sprites.size(); i < n; ++i)
	{
		Sprite* sprite = sprites[i];
		glPushMatrix();
		glTranslatef(sprite->getPosition().x, sprite->getPosition().y, 1.0f);
		const std::vector<TextureRegion*>& textures = sprite->getAllTextureRegions();
		for (size_t j = 0, m = textures.size(); j < m; ++j)
		{
			glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

			TextureRegion* region = textures[j];
			Texture* texture = TexturesMgr::Instance()->getItem(region->filename);
			glBindTexture(GL_TEXTURE_2D, texture->getTexID());
			glBegin(GL_TRIANGLES);
			for (size_t k = 0; k < 3; ++k)
			{
				glTexCoord2f(region->srcRegion[k].x, region->srcRegion[k].y); 
				glVertex3f(region->dstRegion[k].x, region->dstRegion[k].y, -1);
			}
			glEnd();
			glBindTexture(GL_TEXTURE_2D, NULL);
		}
		glPopMatrix();
	}

	if (m_bb->m_isTransparent == 1)
		glDisable(GL_BLEND);
}

void Render::bindOneTime(const std::vector<Sprite*>& sprites, AbstractView* view)
{
	if (m_bb->m_isTransparent == 1)
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}
	else
	{
		glDisable(GL_BLEND);
	}

	if (!sprites.empty())
	{
		TextureRegion* region = sprites[0]->getAllTextureRegions()[0];
		Texture* texture = TexturesMgr::Instance()->getItem(region->filename);
		glBindTexture(GL_TEXTURE_2D, texture->getTexID());
	}

	for (size_t i = 0, n = sprites.size(); i < n; ++i)
	{
		Sprite* sprite = sprites[i];
		glPushMatrix();
		glTranslatef(sprite->getPosition().x, sprite->getPosition().y, 1.0f);
		const std::vector<TextureRegion*>& textures = sprite->getAllTextureRegions();
		for (size_t j = 0, m = textures.size(); j < m; ++j)
		{
			glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

			TextureRegion* region = textures[j];
//			Texture* texture = TexturesMgr::Instance()->getItem(region->filename);
//			glBindTexture(GL_TEXTURE_2D, texture->getTexID());
			glBegin(GL_TRIANGLES);
			for (size_t k = 0; k < 3; ++k)
			{
				glTexCoord2f(region->srcRegion[k].x, region->srcRegion[k].y); 
				glVertex3f(region->dstRegion[k].x, region->dstRegion[k].y, -1);
			}
			glEnd();
//			glBindTexture(GL_TEXTURE_2D, NULL);
		}
		glPopMatrix();
	}

	if (m_bb->m_isTransparent == 1)
		glDisable(GL_BLEND);
}

void Render::bindOneTime_strip(const std::vector<Sprite*>& sprites, AbstractView* view)
{
	if (m_bb->m_isTransparent == 1)
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}
	else
	{
		glDisable(GL_BLEND);
	}

	Texture* texture;
	if (!sprites.empty())
	{
		TextureRegion* region = sprites[0]->getAllTextureRegions()[0];
		texture = TexturesMgr::Instance()->getItem(region->filename);
		glBindTexture(GL_TEXTURE_2D, texture->getTexID());
	}
	if (!texture) return;

	const float hw = texture->getWidth() * 0.5f,
		hh = texture->getHeight() * 0.5f;

	for (size_t i = 0, n = sprites.size(); i < n; ++i)
	{
		Sprite* sprite = sprites[i];
		glPushMatrix();
		glTranslatef(sprite->getPosition().x, sprite->getPosition().y, 1.0f);

		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
		glBegin(GL_TRIANGLE_STRIP);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-hw, -hh, -1.0f);
			glTexCoord2f(1.0f, 0.0f); glVertex3f( hw, -hh, -1.0f);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(-hw,  hh, -1.0f);
			glTexCoord2f(1.0f, 1.0f); glVertex3f( hw,  hh, -1.0f);
		glEnd();

		glPopMatrix();
	}

	if (m_bb->m_isTransparent == 1)
		glDisable(GL_BLEND);
}

void Render::bindOneTime_strip_death(const std::vector<Sprite*>& sprites, AbstractView* view)
{	
	if (m_bb->m_isTransparent == 1)
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}
	else
	{
		glDisable(GL_BLEND);
	}
	glEnable(GL_DEPTH_TEST);

	Texture* texture;
	if (!sprites.empty())
	{
		TextureRegion* region = sprites[0]->getAllTextureRegions()[0];
		texture = TexturesMgr::Instance()->getItem(region->filename);
		glBindTexture(GL_TEXTURE_2D, texture->getTexID());
	}
	if (!texture) return;

	const float hw = texture->getWidth() * 0.5f,
		hh = texture->getHeight() * 0.5f;

	for (size_t i = 0, n = sprites.size(); i < n; ++i)
	{
		Sprite* sprite = sprites[i];
		glPushMatrix();
		glTranslatef(sprite->getPosition().x, sprite->getPosition().y, 1.0f);

		const float depth = Random::getNum0To1() - 1.0f;

		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
		glBegin(GL_TRIANGLE_STRIP);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-hw, -hh, depth);
			glTexCoord2f(1.0f, 0.0f); glVertex3f( hw, -hh, depth);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(-hw,  hh, depth);
			glTexCoord2f(1.0f, 1.0f); glVertex3f( hw,  hh, depth);
		glEnd();

		glPopMatrix();
	}

	glDisable(GL_DEPTH_TEST);
	if (m_bb->m_isTransparent == 1)
		glDisable(GL_BLEND);
}

void Render::drawArrays(const std::vector<Sprite*>& sprites, AbstractView* view)
{
	Texture* texture = NULL;
	if (!sprites.empty())
	{
		TextureRegion* region = sprites[0]->getAllTextureRegions()[0];
		texture = TexturesMgr::Instance()->getItem(region->filename);
		glBindTexture(GL_TEXTURE_2D, texture->getTexID());
	}
	if (!texture) return;

	if (m_bb->m_isTransparent == 1)
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}
	else
	{
		glDisable(GL_BLEND);
	}

	const float hw = texture->getWidth() * 0.5f,
		hh = texture->getHeight() * 0.5f;

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	static GLfloat* vertices = NULL;
	if (!vertices)
	{
		int size = 2 * 3 * 2 * sprites.size();
		vertices = (GLfloat*) malloc(size * sizeof(GLfloat));
		memset(vertices, 0, size * sizeof(GLfloat));
		size_t index = 0;
		for (size_t i = 0, n = sprites.size(); i < n; ++i)
		{
			const f2Vec2& pos = sprites[i]->getPosition();
			vertices[index++] = pos.x - hw;
			vertices[index++] = pos.y + hh;
			vertices[index++] = pos.x - hw;
			vertices[index++] = pos.y - hh;
			vertices[index++] = pos.x + hw;
			vertices[index++] = pos.y - hh;
			vertices[index++] = pos.x + hw;
			vertices[index++] = pos.y - hh;
			vertices[index++] = pos.x + hw;
			vertices[index++] = pos.y + hh;
			vertices[index++] = pos.x - hw;
			vertices[index++] = pos.y + hh;
		}
	}

	static GLfloat* texCoords = NULL;
	if (!texCoords)
	{
		int size = 2 * 3 * 2 * sprites.size();
		texCoords = (GLfloat*) malloc(size * sizeof(GLfloat));
		memset(texCoords, 0, size * sizeof(GLfloat));
		size_t index = 0;
		for (size_t i = 0, n = sprites.size(); i < n; ++i)
		{
			const f2Vec2& pos = sprites[i]->getPosition();
			texCoords[index++] = 0.0f;
			texCoords[index++] = 1.0f;
			texCoords[index++] = 0.0f;
			texCoords[index++] = 0.0f;
			texCoords[index++] = 1.0f;
			texCoords[index++] = 0.0f;
			texCoords[index++] = 1.0f;
			texCoords[index++] = 0.0f;
			texCoords[index++] = 1.0f;
			texCoords[index++] = 1.0f;
			texCoords[index++] = 0.0f;
			texCoords[index++] = 1.0f;
		}
	}

	glVertexPointer(2, GL_FLOAT, 0, vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, texCoords);

	glDrawArrays(GL_TRIANGLES, 0, sprites.size() * 6);

	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);

	if (m_bb->m_isTransparent == 1)
		glDisable(GL_BLEND);
}

void Render::drawElements(const std::vector<Sprite*>& sprites, AbstractView* view)
{
	Texture* texture = NULL;
	if (!sprites.empty())
	{
		TextureRegion* region = sprites[0]->getAllTextureRegions()[0];
		texture = TexturesMgr::Instance()->getItem(region->filename);
		glBindTexture(GL_TEXTURE_2D, texture->getTexID());
	}
	if (!texture) return;

	if (m_bb->m_isTransparent == 1)
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}
	else
	{
		glDisable(GL_BLEND);
	}

	const float hw = texture->getWidth() * 0.5f,
		hh = texture->getHeight() * 0.5f;

	static GLfloat* vertices = NULL;
	if (!vertices)
	{
		int size = 2 * 4 * sprites.size();
		vertices = (GLfloat*) malloc(size * sizeof(GLfloat));
		memset(vertices, 0, size * sizeof(GLfloat));
		size_t index = 0;
		for (size_t i = 0, n = sprites.size(); i < n; ++i)
		{
			const f2Vec2& pos = sprites[i]->getPosition();
			vertices[index++] = pos.x - hw;
			vertices[index++] = pos.y - hh;
			vertices[index++] = pos.x + hw;
			vertices[index++] = pos.y - hh;
			vertices[index++] = pos.x + hw;
			vertices[index++] = pos.y + hh;
			vertices[index++] = pos.x - hw;
			vertices[index++] = pos.y + hh;
		}
	}

	static GLfloat* texCoords = NULL;
	if (!texCoords)
	{
		int size = 2 * 4 * sprites.size();
		texCoords = (GLfloat*) malloc(size * sizeof(GLfloat));
		memset(texCoords, 0, size * sizeof(GLfloat));
		size_t index = 0;
		for (size_t i = 0, n = sprites.size(); i < n; ++i)
		{
			const f2Vec2& pos = sprites[i]->getPosition();
			texCoords[index++] = 0.0f;
			texCoords[index++] = 0.0f;
			texCoords[index++] = 1.0f;
			texCoords[index++] = 0.0f;
			texCoords[index++] = 1.0f;
			texCoords[index++] = 1.0f;
			texCoords[index++] = 0.0f;
			texCoords[index++] = 1.0f;
		}
	}

	static GLuint* indices = NULL;
	if (!indices)
	{
		int size = 3 * 2 * sprites.size();
		indices = (GLuint*) malloc(size * sizeof(GLuint));
		memset(indices, 0, size * sizeof(GLuint));
		size_t index = 0;
		for (size_t i = 0, n = sprites.size(); i < n; ++i)
		{
			indices[index++] = i * 4 + 0;
			indices[index++] = i * 4 + 1;
			indices[index++] = i * 4 + 2;
			indices[index++] = i * 4 + 2;
			indices[index++] = i * 4 + 3;
			indices[index++] = i * 4 + 0;
		}
	}

	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(2, GL_FLOAT, 0, vertices);

	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glTexCoordPointer(2, GL_FLOAT, 0, texCoords);

	glDrawElements(GL_TRIANGLES, sprites.size() * 6, GL_UNSIGNED_INT, indices);

	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);

	if (m_bb->m_isTransparent == 1)
		glDisable(GL_BLEND);
}

void Render::drawElements_interleave(const std::vector<Sprite*>& sprites, AbstractView* view)
{
	Texture* texture = NULL;
	if (!sprites.empty())
	{
		TextureRegion* region = sprites[0]->getAllTextureRegions()[0];
		texture = TexturesMgr::Instance()->getItem(region->filename);
		glBindTexture(GL_TEXTURE_2D, texture->getTexID());
	}
	if (!texture) return;

	if (m_bb->m_isTransparent == 1)
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}
	else
	{
		glDisable(GL_BLEND);
	}

	const float hw = texture->getWidth() * 0.5f,
		hh = texture->getHeight() * 0.5f;

	static GLfloat* vertices = NULL;
	if (!vertices)
	{
		int size = 2 * 4 * sprites.size() + 2 * 4 * sprites.size();
		vertices = (GLfloat*) malloc(size * sizeof(GLfloat));
		memset(vertices, 0, size * sizeof(GLfloat));
		size_t index = 0;
		for (size_t i = 0, n = sprites.size(); i < n; ++i)
		{
			const f2Vec2& pos = sprites[i]->getPosition();
			vertices[index++] = pos.x - hw;
			vertices[index++] = pos.y - hh;
			vertices[index++] = 0.0f;
			vertices[index++] = 0.0f;
			vertices[index++] = pos.x + hw;
			vertices[index++] = pos.y - hh;
			vertices[index++] = 1.0f;
			vertices[index++] = 0.0f;
			vertices[index++] = pos.x + hw;
			vertices[index++] = pos.y + hh;
			vertices[index++] = 1.0f;
			vertices[index++] = 1.0f;
			vertices[index++] = pos.x - hw;
			vertices[index++] = pos.y + hh;
			vertices[index++] = 0.0f;
			vertices[index++] = 1.0f;
		}
	}

	static GLuint* indices = NULL;
	if (!indices)
	{
		int size = 3 * 2 * sprites.size();
		indices = (GLuint*) malloc(size * sizeof(GLuint));
		memset(indices, 0, size * sizeof(GLuint));
		size_t index = 0;
		for (size_t i = 0, n = sprites.size(); i < n; ++i)
		{
			indices[index++] = i * 4 + 0;
			indices[index++] = i * 4 + 1;
			indices[index++] = i * 4 + 2;
			indices[index++] = i * 4 + 2;
			indices[index++] = i * 4 + 3;
			indices[index++] = i * 4 + 0;
		}
	}

	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(2, GL_FLOAT, 4 * sizeof(GLfloat), vertices);

	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glTexCoordPointer(2, GL_FLOAT, 4 * sizeof(GLfloat), vertices + 2);

	glDrawElements(GL_TRIANGLES, sprites.size() * 6, GL_UNSIGNED_INT, indices);

	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);

	if (m_bb->m_isTransparent == 1)
		glDisable(GL_BLEND);
}

void Render::drawRangeElements(const std::vector<Sprite*>& sprites, AbstractView* view)
{
	Texture* texture = NULL;
	if (!sprites.empty())
	{
		TextureRegion* region = sprites[0]->getAllTextureRegions()[0];
		texture = TexturesMgr::Instance()->getItem(region->filename);
		glBindTexture(GL_TEXTURE_2D, texture->getTexID());
	}
	if (!texture) return;

	if (m_bb->m_isTransparent == 1)
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}
	else
	{
		glDisable(GL_BLEND);
	}

	const float hw = texture->getWidth() * 0.5f,
		hh = texture->getHeight() * 0.5f;

	static GLfloat* vertices = NULL;
	if (!vertices)
	{
		int size = 2 * 4 * sprites.size();
		vertices = (GLfloat*) malloc(size * sizeof(GLfloat));
		memset(vertices, 0, size * sizeof(GLfloat));
		size_t index = 0;
		for (size_t i = 0, n = sprites.size(); i < n; ++i)
		{
			const f2Vec2& pos = sprites[i]->getPosition();
			vertices[index++] = pos.x - hw;
			vertices[index++] = pos.y - hh;
			vertices[index++] = pos.x + hw;
			vertices[index++] = pos.y - hh;
			vertices[index++] = pos.x + hw;
			vertices[index++] = pos.y + hh;
			vertices[index++] = pos.x - hw;
			vertices[index++] = pos.y + hh;
		}
	}

	static GLfloat* texCoords = NULL;
	if (!texCoords)
	{
		int size = 2 * 4 * sprites.size();
		texCoords = (GLfloat*) malloc(size * sizeof(GLfloat));
		memset(texCoords, 0, size * sizeof(GLfloat));
		size_t index = 0;
		for (size_t i = 0, n = sprites.size(); i < n; ++i)
		{
			const f2Vec2& pos = sprites[i]->getPosition();
			texCoords[index++] = 0.0f;
			texCoords[index++] = 0.0f;
			texCoords[index++] = 1.0f;
			texCoords[index++] = 0.0f;
			texCoords[index++] = 1.0f;
			texCoords[index++] = 1.0f;
			texCoords[index++] = 0.0f;
			texCoords[index++] = 1.0f;
		}
	}

	static GLuint* indices = NULL;
	if (!indices)
	{
		int size = 3 * 2 * sprites.size();
		indices = (GLuint*) malloc(size * sizeof(GLuint));
		memset(indices, 0, size * sizeof(GLuint));
		size_t index = 0;
		for (size_t i = 0, n = sprites.size(); i < n; ++i)
		{
			indices[index++] = i * 4 + 0;
			indices[index++] = i * 4 + 1;
			indices[index++] = i * 4 + 2;
			indices[index++] = i * 4 + 2;
			indices[index++] = i * 4 + 3;
			indices[index++] = i * 4 + 0;
		}
	}

	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(2, GL_FLOAT, 0, vertices);

	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glTexCoordPointer(2, GL_FLOAT, 0, texCoords);

 	glDrawElements(GL_TRIANGLES, sprites.size() * 6, GL_UNSIGNED_INT, indices);

	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);

	if (m_bb->m_isTransparent == 1)
		glDisable(GL_BLEND);
}

void Render::displayList(const std::vector<Sprite*>& sprites, AbstractView* view)
{
	static GLuint id = 0;
	if (!id)
	{
		setVSync(0);

		id = glGenLists(1);
		if (!id) return;

		Texture* texture = NULL;
		if (!sprites.empty())
		{
			TextureRegion* region = sprites[0]->getAllTextureRegions()[0];
			texture = TexturesMgr::Instance()->getItem(region->filename);
			glBindTexture(GL_TEXTURE_2D, texture->getTexID());
		}
		if (!texture) return;

		const float hw = texture->getWidth() * 0.5f,
			hh = texture->getHeight() * 0.5f;

		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);

		static GLfloat* vertices = NULL;
		if (!vertices)
		{
			int size = 2 * 3 * 2 * sprites.size();
			vertices = (GLfloat*) malloc(size * sizeof(GLfloat));
			memset(vertices, 0, size * sizeof(GLfloat));
			size_t index = 0;
			for (size_t i = 0, n = sprites.size(); i < n; ++i)
			{
				const f2Vec2& pos = sprites[i]->getPosition();
				vertices[index++] = pos.x - hw;
				vertices[index++] = pos.y + hh;
				vertices[index++] = pos.x - hw;
				vertices[index++] = pos.y - hh;
				vertices[index++] = pos.x + hw;
				vertices[index++] = pos.y - hh;
				vertices[index++] = pos.x + hw;
				vertices[index++] = pos.y - hh;
				vertices[index++] = pos.x + hw;
				vertices[index++] = pos.y + hh;
				vertices[index++] = pos.x - hw;
				vertices[index++] = pos.y + hh;
			}
		}

		static GLfloat* texCoords = NULL;
		if (!texCoords)
		{
			int size = 2 * 3 * 2 * sprites.size();
			texCoords = (GLfloat*) malloc(size * sizeof(GLfloat));
			memset(texCoords, 0, size * sizeof(GLfloat));
			size_t index = 0;
			for (size_t i = 0, n = sprites.size(); i < n; ++i)
			{
				const f2Vec2& pos = sprites[i]->getPosition();
				texCoords[index++] = 0.0f;
				texCoords[index++] = 1.0f;
				texCoords[index++] = 0.0f;
				texCoords[index++] = 0.0f;
				texCoords[index++] = 1.0f;
				texCoords[index++] = 0.0f;
				texCoords[index++] = 1.0f;
				texCoords[index++] = 0.0f;
				texCoords[index++] = 1.0f;
				texCoords[index++] = 1.0f;
				texCoords[index++] = 0.0f;
				texCoords[index++] = 1.0f;
			}
		}

		glVertexPointer(2, GL_FLOAT, 0, vertices);
		glTexCoordPointer(2, GL_FLOAT, 0, texCoords);

		glNewList(id, GL_COMPILE);
		glDrawArrays(GL_TRIANGLES, 0, sprites.size() * 6);
		glEndList();

		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);
	}

	if (m_bb->m_isTransparent == 1)
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}
	else 
	{
		glDisable(GL_BLEND);
	}

	glCallList(id);

	if (m_bb->m_isTransparent == 1)
		glDisable(GL_BLEND);
}

typedef void (APIENTRY * PFNGLBINDBUFFERARBPROC) (GLenum target, GLuint buffer);
typedef void (APIENTRY * PFNGLDELETEBUFFERSARBPROC) (GLsizei n, const GLuint *buffers);
typedef void (APIENTRY * PFNGLGENBUFFERSARBPROC) (GLsizei n, GLuint *buffers);
typedef void (APIENTRY * PFNGLBUFFERDATAARBPROC) (GLenum target, int size, const GLvoid *data, GLenum usage);

void Render::vbo(const std::vector<Sprite*>& sprites, AbstractView* view)
{
	static GLuint verticesID = 0, texCoordsID = 0;
	static GLfloat *vertices = NULL, *texCoords = NULL;

	static bool vboSupported = false;
	static bool inited = false;
	if (!inited)
	{
		inited= true;

		// VBO Extension Function Pointers
		PFNGLGENBUFFERSARBPROC glGenBuffersARB = NULL;					// VBO Name Generation Procedure
		PFNGLBINDBUFFERARBPROC glBindBufferARB = NULL;					// VBO Bind Procedure
		PFNGLBUFFERDATAARBPROC glBufferDataARB = NULL;					// VBO Data Loading Procedure
		PFNGLDELETEBUFFERSARBPROC glDeleteBuffersARB = NULL;			// VBO Deletion Procedure

		if(isExtensionSupported("GL_ARB_vertex_buffer_object"))
		{
			vboSupported = true;

			// Get Pointers To The GL Functions
			glGenBuffersARB = (PFNGLGENBUFFERSARBPROC) wglGetProcAddress("glGenBuffersARB");
			glBindBufferARB = (PFNGLBINDBUFFERARBPROC) wglGetProcAddress("glBindBufferARB");
			glBufferDataARB = (PFNGLBUFFERDATAARBPROC) wglGetProcAddress("glBufferDataARB");
			glDeleteBuffersARB = (PFNGLDELETEBUFFERSARBPROC) wglGetProcAddress("glDeleteBuffersARB");
			// Load Vertex Data Into The Graphics Card Memory
			Texture* texture = NULL;
			if (!sprites.empty())
			{
				TextureRegion* region = sprites[0]->getAllTextureRegions()[0];
				texture = TexturesMgr::Instance()->getItem(region->filename);
				glBindTexture(GL_TEXTURE_2D, texture->getTexID());
			}
			if (!texture) return;

			const float hw = texture->getWidth() * 0.5f,
				hh = texture->getHeight() * 0.5f;

			if (!vertices)
			{
				int size = 2 * 3 * 2 * sprites.size();
				vertices = (GLfloat*) malloc(size * sizeof(GLfloat));
				memset(vertices, 0, size * sizeof(GLfloat));
				size_t index = 0;
				for (size_t i = 0, n = sprites.size(); i < n; ++i)
				{
					const f2Vec2& pos = sprites[i]->getPosition();
					vertices[index++] = pos.x - hw;
					vertices[index++] = pos.y + hh;
					vertices[index++] = pos.x - hw;
					vertices[index++] = pos.y - hh;
					vertices[index++] = pos.x + hw;
					vertices[index++] = pos.y - hh;
					vertices[index++] = pos.x + hw;
					vertices[index++] = pos.y - hh;
					vertices[index++] = pos.x + hw;
					vertices[index++] = pos.y + hh;
					vertices[index++] = pos.x - hw;
					vertices[index++] = pos.y + hh;
				}
			}

			if (!texCoords)
			{
				int size = 2 * 3 * 2 * sprites.size();
				texCoords = (GLfloat*) malloc(size * sizeof(GLfloat));
				memset(texCoords, 0, size * sizeof(GLfloat));
				size_t index = 0;
				for (size_t i = 0, n = sprites.size(); i < n; ++i)
				{
					const f2Vec2& pos = sprites[i]->getPosition();
					texCoords[index++] = 0.0f;
					texCoords[index++] = 1.0f;
					texCoords[index++] = 0.0f;
					texCoords[index++] = 0.0f;
					texCoords[index++] = 1.0f;
					texCoords[index++] = 0.0f;
					texCoords[index++] = 1.0f;
					texCoords[index++] = 0.0f;
					texCoords[index++] = 1.0f;
					texCoords[index++] = 1.0f;
					texCoords[index++] = 0.0f;
					texCoords[index++] = 1.0f;
				}
			}

			int size = 2 * 3 * 2 * sprites.size();

			glGenBuffersARB(1, &verticesID);
			glBindBufferARB(GL_ARRAY_BUFFER_ARB, verticesID);
			glBufferDataARB(GL_ARRAY_BUFFER_ARB, size * sizeof(GLfloat), vertices, GL_STATIC_DRAW_ARB);

			glGenBuffersARB(1, &texCoordsID);
			glBindBufferARB(GL_ARRAY_BUFFER_ARB, texCoordsID);
			glBufferDataARB(GL_ARRAY_BUFFER_ARB, size * sizeof(GLfloat), texCoords, GL_STATIC_DRAW_ARB);

// 			free(vertices);
// 			free(texCoords);
		}
	}

	if (m_bb->m_isTransparent == 1)
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}
	else 
	{
		glDisable(GL_BLEND);
	}

	glEnableClientState(GL_VERTEX_ARRAY);						// Enable Vertex Arrays
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);				// Enable Texture Coord Arrays

	if (vboSupported)
	{
		glBindBufferARB(GL_ARRAY_BUFFER_ARB, verticesID);
		glVertexPointer(2, GL_FLOAT, 0, (char *)NULL);
		glBindBufferARB(GL_ARRAY_BUFFER_ARB, texCoordsID);
		glTexCoordPointer(2, GL_FLOAT, 0, (char *)NULL);
	}
	else
	{
		glVertexPointer(2, GL_FLOAT, 0, vertices);
		glTexCoordPointer(2, GL_FLOAT, 0, texCoords);
	}

	glDrawArrays(GL_TRIANGLES, 0, sprites.size() * 6);

	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);

	if (m_bb->m_isTransparent == 1)
		glDisable(GL_BLEND);
}

typedef BOOL (APIENTRY *PFNWGLSWAPINTERVALFARPROC)( int );

void Render::setVSync(int interval/*=1*/)
{
	PFNWGLSWAPINTERVALFARPROC wglSwapIntervalEXT = 0;

	const char* extensions = (char*) glGetString(GL_EXTENSIONS);

	if( strstr( extensions, "WGL_EXT_swap_control" ) == 0 )
// 		return; // Error: WGL_EXT_swap_control extension not supported on your computer.\n");
// 	else
	{
		wglSwapIntervalEXT = (PFNWGLSWAPINTERVALFARPROC)wglGetProcAddress( "wglSwapIntervalEXT" );

		if( wglSwapIntervalEXT )
			wglSwapIntervalEXT(interval);
	}
}

bool Render::isExtensionSupported(char* szTargetExtension)
{
	const unsigned char *pszExtensions = NULL;
	const unsigned char *pszStart;
	unsigned char *pszWhere, *pszTerminator;

	// Extension names should not have spaces
	pszWhere = (unsigned char *) strchr( szTargetExtension, ' ' );
	if( pszWhere || *szTargetExtension == '\0' )
		return false;

	// Get Extensions String
	pszExtensions = glGetString( GL_EXTENSIONS );

	// Search The Extensions String For An Exact Copy
	pszStart = pszExtensions;
	for(;;)
	{
		pszWhere = (unsigned char *) strstr( (const char *) pszStart, szTargetExtension );
		if( !pszWhere )
			break;
		pszTerminator = pszWhere + strlen( szTargetExtension );
		if( pszWhere == pszStart || *( pszWhere - 1 ) == ' ' )
			if( *pszTerminator == ' ' || *pszTerminator == '\0' )
				return true;
		pszStart = pszTerminator;
	}
	return false;
}