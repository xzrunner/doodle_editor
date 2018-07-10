#include "ImageSprite.h"
#include "IBody.h"
#include "BodyFactory.h"

#include "Tools/FileNameParser.h"
#include "Tools/FilenameTools.h"

#include <Box2D/Box2D.h>

using namespace wxgui;

ImageSprite::ImageSprite()
	: m_symbol(NULL)
{
}

ImageSprite::ImageSprite(const ImageSprite& sprite)
	: ISprite(sprite)
	, m_symbol(sprite.m_symbol)
{
}

ImageSprite::ImageSprite(ImageSymbol* symbol)
	: m_symbol(symbol)
{
	buildBounding();
}

ImageSprite* ImageSprite::clone()
{
	return new ImageSprite(*this);
}

const ImageSymbol& ImageSprite::getSymbol() const
{
	return *m_symbol;
}

void ImageSprite::setSymbol(ISymbol* symbol)
{
	ImageSymbol* image = dynamic_cast<ImageSymbol*>(symbol);
	if (image) m_symbol = image;
}

void ImageSprite::loadBodyFromFile()
{
	wxString path = FilenameTools::getFilePathExceptExtension(m_symbol->getFilepath());
	wxString polygonPath = path + "_" + FileNameParser::getFileTag(FileNameParser::e_polyline) + ".txt";
	wxString circlePath = path + "_" + FileNameParser::getFileTag(FileNameParser::e_circle) + ".txt";
	if (FilenameTools::isExist(polygonPath))
	{
		if (m_body) delete m_body;
		m_body = BodyFactory::createBody(polygonPath, m_scale);
	}
	else if (FilenameTools::isExist(circlePath))
	{
		if (m_body) delete m_body;
		m_body = BodyFactory::createBody(circlePath, m_scale);
	}
	m_body->getBody()->SetTransform(b2Vec2(m_pos.x / BOX2D_SCALE_FACTOR, m_pos.y / BOX2D_SCALE_FACTOR), m_angle);
}

void ImageSprite::buildBounding(float* texCoords)
{
	if (!m_symbol) return;

	const int width = m_symbol->getWidth(),
		height = m_symbol->getHeight();

	delete m_bounding;
	m_bounding = BVFactory::createBV(e_obb);

	f2AABB aabb;
	aabb.xMin = width * (texCoords[0] - 0.5f);
	aabb.xMax = width * (texCoords[2] - 0.5f);
	aabb.yMin = height * (texCoords[1] - 0.5f);
	aabb.yMax = height * (texCoords[3] - 0.5f);

	f2Vec2 center(aabb.xCenter(), aabb.yCenter());
	float hWidth = (aabb.xMax - aabb.xMin) * 0.5f * m_scale,
		hHeight = (aabb.yMax - aabb.yMin) * 0.5f * m_scale;
	aabb.xMin = -hWidth;
	aabb.xMax = hWidth;
	aabb.yMin = -hHeight;
	aabb.yMax = hHeight;

	f2Vec2 offset = f2Math::rotateVector(center, m_angle);
	aabb.translate(m_pos + offset);
	m_bounding->initFromAABB(aabb);
	m_bounding->rotate(m_angle);
}

void ImageSprite::buildBounding()
{
	if (!m_symbol) return;

	const float hWidth = m_symbol->getWidth() * 0.5f * m_scale,
		hHeight = m_symbol->getHeight() * 0.5f * m_scale;

	delete m_bounding;
	m_bounding = BVFactory::createBV(e_obb);
	f2AABB aabb;
	aabb.xMin = -hWidth;
	aabb.xMax = hWidth;
	aabb.yMin = -hHeight;
	aabb.yMax = hHeight;
	aabb.translate(m_pos);
	m_bounding->initFromAABB(aabb);
	m_bounding->rotate(m_angle);
}