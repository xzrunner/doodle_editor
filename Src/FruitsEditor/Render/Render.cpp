#include "Render.h"
#include "../Dataset/Layer.h"
#include "../Dataset/Sprite.h"
#include "../Dataset/PointShape.h"
#include "../Dataset/ChainShape.h"
#include "../Dataset/TriangleShape.h"
#include "../Dataset/Texture.h"
#include "../Dataset/TextureRegion.h"
#include "../Dataset/SelectionSet.h"
#include "Fruits2D/Dataset/AABB.h"
#include "Fruits2D/Dataset/OBB.h"

#include <Windows.h>
#include <GL/GL.h>

using namespace FEDITOR;

void Render::drawLayers(const std::vector<Layer*>& layers)
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	for (size_t i = 0, n = layers.size(); i < n; ++i)
	{
		Layer* layer = layers[i];
		const f2Vec2& offset = layer->getOffset();

		glPushMatrix();
		glTranslatef(offset.x, offset.y, 1.0f);
			drawLayer(layer);
		glPopMatrix();
	}

	glDisable(GL_BLEND);
}

void Render::drawSelection(const SelectionSet& selection)
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	const std::set<Sprite*>& sprites = selection.getAll();
	std::set<Sprite*>::const_iterator itr = sprites.begin();
	for ( ; itr != sprites.end(); ++itr)
		drawSelection(*itr);

	glDisable(GL_BLEND);
}

void Render::drawLayer(const Layer* layer)
{
	if (!layer->isVisible()) return;

	const std::vector<Sprite*>& sprites = layer->getAllSprites();
	if (layer->m_style.m_bShapeMask)
	{
		glClearStencil(0);
		glEnable(GL_STENCIL_TEST);

		glClear(GL_STENCIL_BUFFER_BIT);

		glStencilFunc(GL_NEVER, 0x0, 0x0);
		glStencilOp(GL_INCR, GL_INCR, GL_INCR);

		for (size_t i = 0, n = sprites.size(); i < n; ++i)
			drawSpriteShape(sprites[i], layer->m_style, e_triangle);

		glStencilFunc(GL_NOTEQUAL, 0x0, 0x1);
		glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);

		for (size_t i = 0, n = sprites.size(); i < n; ++i)
			drawSpriteTexture(sprites[i]);

		glDisable(GL_STENCIL_TEST);

		for (size_t i = 0, n = sprites.size(); i < n; ++i)
			drawSpriteShape(sprites[i], layer->m_style, e_chain);
		for (size_t i = 0, n = sprites.size(); i < n; ++i)
			drawSpriteShape(sprites[i], layer->m_style, e_point);
	}
	else
	{
		for (size_t i = 0, n = sprites.size(); i < n; ++i)
			drawSprite(sprites[i], layer->m_style);
	}
}

void Render::drawSprite(const Sprite* sprite, const LayerRenderStyle& style)
{
	glPushMatrix();
	glTranslatef(sprite->getPosition().x, sprite->getPosition().y, 1.0f);
	glRotatef(sprite->getAngle() * TRANS_RAD_TO_DEG, 0, 0, 1);
	glScalef(sprite->getXScale(), sprite->getYScale(), 1.0f);
		drawTextures(sprite->getAllTextureRegions());
		if (style.m_bDrawShape) 
			drawShapes(sprite->getAllShapes(), style);
	glPopMatrix();

	if (style.m_bDrawAABB) drawAABB(sprite->getBounding());
}

void Render::drawSpriteShape(const Sprite* sprite, const LayerRenderStyle& style, int typeFilter/* = -1*/)
{
	glPushMatrix();
	glTranslatef(sprite->getPosition().x, sprite->getPosition().y, 1.0f);
	glRotatef(sprite->getAngle() * TRANS_RAD_TO_DEG, 0, 0, 1);
	glScalef(sprite->getXScale(), sprite->getYScale(), 1.0f);
		drawShapes(sprite->getAllShapes(), style, typeFilter);
	glPopMatrix();
}

void Render::drawSpriteTexture(const Sprite* sprite)
{
	glPushMatrix();
	glTranslatef(sprite->getPosition().x, sprite->getPosition().y, 1.0f);
	glRotatef(sprite->getAngle() * TRANS_RAD_TO_DEG, 0, 0, 1);
	glScalef(sprite->getXScale(), sprite->getYScale(), 1.0f);
		drawTextures(sprite->getAllTextureRegions());
	glPopMatrix();
}

void Render::drawShapes(const std::vector<Shape*>& shapes, const LayerRenderStyle& style, int typeFilter/* = -1*/)
{
	for (size_t i = 0, n = shapes.size(); i < n; ++i)
	{
		Shape* ps = shapes[i];
		if (typeFilter != -1 && ps->getType() != typeFilter) continue;

		switch (ps->getType())
		{
		case e_point:
			{
				const PointShape* pps = static_cast<PointShape*>(ps);
				assert(pps);
				std::vector<f2Vec2> pos;
				pos.push_back(pps->m_pos);
				drawPoints(pos, style.m_pointStyle.size, style.m_pointStyle.color);
			}
			break;
		case e_chain:
			{
				const ChainShape* pcs = static_cast<ChainShape*>(ps);
				assert(pcs);
				drawPolyline(pcs->m_vertices, style.m_chainStyle.size, style.m_chainStyle.color, pcs->m_isLoop);
				if (style.m_bDrawCtlPos)
					drawPoints(pcs->m_vertices, style.m_ctlposStyle.size, style.m_ctlposStyle.color);
			}
			break;
		case e_triangle:
			{
				const TriangleShape* pts = static_cast<TriangleShape*>(ps);
				assert(pts);
				drawTriangle(pts->m_pos, style.m_triangleStyle.color);
			}
			break;
		default:
			throw new IllegalArgumentException("Render::drawSprite: error type. ");
		}
	}
}

void Render::drawTextures(const std::vector<TextureRegion*>& textures)
{
	for (size_t i = 0, n = textures.size(); i < n; ++i)
	{
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

		TextureRegion* region = textures[i];
		Texture* texture = TexturesMgr::Instance()->getItem(region->filename);
		glBindTexture(GL_TEXTURE_2D, texture->getTexID());
		glBegin(GL_TRIANGLES);
		for (size_t i = 0; i < 3; ++i)
		{
			glTexCoord2f(region->srcRegion[i].x, region->srcRegion[i].y); 
			glVertex3f(region->dstRegion[i].x, region->dstRegion[i].y, -1);
		}
		glEnd();
		glBindTexture(GL_TEXTURE_2D, NULL);
	}
}

void Render::drawAABB(F2D::AbstractBV* bounding)
{
	AABB* aabb = dynamic_cast<AABB*>(bounding);
	if (aabb) 
	{
		drawAABB(aabb->getAABB());
		return;
	}

	OBB* obb = dynamic_cast<OBB*>(bounding);
	if (obb) 
	{
		const float x = obb->getAABB().xCenter(),
			y = obb->getAABB().yCenter();

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		glPushMatrix();
		glTranslatef(x, y, 1.0f);
		glRotatef(obb->getAngle() * TRANS_RAD_TO_DEG, 0, 0, 1);
		glTranslatef(-x, -y, 1.0f);
			//obb->translate(f2Vec2(-x, -y));
			drawAABB(obb->getAABB());
			//obb->translate(f2Vec2(x, y));
		glPopMatrix();
		return;
	}
}

void Render::drawSelection(const Sprite* sprite)
{
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

	glPushMatrix();
	glTranslatef(sprite->getPosition().x, sprite->getPosition().y, 1.0f);
	glRotatef(sprite->getAngle() * TRANS_RAD_TO_DEG, 0, 0, 1);
		glPushMatrix();
		glScalef(sprite->getXScale(), sprite->getYScale(), 1.0f);
			drawTexturesSelected(sprite->getAllTextureRegions());
		glPopMatrix();
		drawShapesSelected(sprite->getAllShapes());
	glPopMatrix();
}

void Render::drawTexturesSelected(const std::vector<TextureRegion*>& textures)
{
	for (size_t i = 0, n = textures.size(); i < n; ++i)
	{
		TextureRegion* region = textures[i];
		Texture* texture = TexturesMgr::Instance()->getItem(region->filename);
		glBegin(GL_TRIANGLES);
		for (size_t i = 0; i < 3; ++i)
		{
			glColor4f(1.0f, 0.0f, 0.0f, 0.5f); 
			glVertex3f(region->dstRegion[i].x, region->dstRegion[i].y, -1);
		}
		glEnd();
	}
}

void Render::drawShapesSelected(const std::vector<Shape*>& shapes)
{
	for (size_t i = 0, n = shapes.size(); i < n; ++i)
	{
		Shape* ps = shapes[i];
		switch (ps->getType())
		{
		case e_point:
			{
				const PointShape* pps = static_cast<PointShape*>(ps);
				assert(pps);
				std::vector<f2Vec2> pos;
				pos.push_back(pps->m_pos);
				drawPoints(pos, 7, f2Colorf(1, 0, 0));
			}
			break;
		case e_chain:
			{
				const ChainShape* pcs = static_cast<ChainShape*>(ps);
				assert(pcs);
				drawPolyline(pcs->m_vertices, 5, f2Colorf(0, 1, 0), pcs->m_isLoop);
			}
			break;
		case e_triangle:
			{
				const TriangleShape* pts = static_cast<TriangleShape*>(ps);
				assert(pts);
				drawTriangle(pts->m_pos, f2Colorf(0.5f, 0, 0));
			}
			break;
		default:
			throw new IllegalArgumentException("Render::drawSprite: error type. ");
		}
	}
}

void Render::drawPoints(const std::vector<f2Vec2>& points, float size, f2Colorf color)
{
	if (points.empty()) return;

	glPointSize(size);
	glBegin(GL_POINTS);
	for (size_t i = 0, n = points.size(); i < n; ++i)
	{
		glColor3f(color.r, color.g, color.b);
		glVertex3f(points[i].x, points[i].y, -1.0f);
	}
	glEnd();
	glPointSize(1.0f);
}

void Render::drawPolyline(const std::vector<f2Vec2>& line, float width, f2Colorf color, bool isLoop/* = false*/)
{
	if (line.size() < 2) return;

	glLineWidth(width);
	if (isLoop)
	{
		glBegin(GL_LINE_LOOP);
		for (size_t i = 0, n = line.size(); i < n; ++i)
		{
			glColor3f(color.r, color.g, color.b);
			glVertex3f(line[i].x, line[i].y, -1.0f);
		} 
		glEnd();
	}
	else
	{
		glBegin(GL_LINE_STRIP);
		for (size_t i = 0, n = line.size(); i < n; ++i)
		{
			glColor3f(color.r, color.g, color.b);
			glVertex3f(line[i].x, line[i].y, -1.0f);
		} 
		glEnd();
	}
	glLineWidth(1.0f);
}

void Render::drawTriangle(const f2Vec2 pos[3], f2Colorf color)
{
	glBegin(GL_TRIANGLES);
	for (size_t i = 0; i < 3; ++i)
	{
		glColor4f(color.r, color.g, color.b, color.a);
		glVertex3f(pos[i].x, pos[i].y, -1);
	}
	glEnd();
}

void Render::drawAABB(const f2AABB& aabb)
{
	glLineWidth(1.0f);

	glBegin(GL_LINE_LOOP);
		glColor3f(1.0f, 1.0f, 0.0f); glVertex3f(aabb.xMin, aabb.yMin, -1.0f);
		glColor3f(1.0f, 1.0f, 0.0f); glVertex3f(aabb.xMax, aabb.yMin, -1.0f);
		glColor3f(1.0f, 1.0f, 0.0f); glVertex3f(aabb.xMax, aabb.yMax, -1.0f);
		glColor3f(1.0f, 1.0f, 0.0f); glVertex3f(aabb.xMin, aabb.yMax, -1.0f);
	glEnd();
}