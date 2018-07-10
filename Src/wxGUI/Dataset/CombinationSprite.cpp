#include "CombinationSprite.h"
#include "IBody.h"
#include "BodyFactory.h"

#include "Tools/FileNameParser.h"
#include "Tools/FilenameTools.h"

#include <Box2D/Box2D.h>

using namespace wxgui;

CombinationSprite::CombinationSprite()
{
}

CombinationSprite::CombinationSprite(const CombinationSprite& sprite)
	: ISprite(sprite)
	, m_symbol(sprite.m_symbol)
{
}

CombinationSprite::CombinationSprite(CombinationSymbol* symbol)
	: m_symbol(symbol)
{
	buildBounding();
}

CombinationSprite::~CombinationSprite()
{
}

CombinationSprite* CombinationSprite::clone()
{
	return new CombinationSprite(*this);
}

const CombinationSymbol& CombinationSprite::getSymbol() const
{
	return *m_symbol;
}

void CombinationSprite::setSymbol(ISymbol* symbol)
{
	CombinationSymbol* combination = dynamic_cast<CombinationSymbol*>(symbol);
	if (combination) m_symbol = combination;
}

void CombinationSprite::loadBodyFromFile()
{
	if (!m_symbol) return;

	std::vector<wxgui::FixtureDataInfo> fixtures;
	const std::vector<ISprite*>& sprites = m_symbol->getChildren();
	for (size_t i = 0, n = sprites.size(); i < n; ++i)
	{
		ISprite* sprite = sprites[i];

		wxgui::FixtureDataInfo fixture;

		if (FileNameParser::isType(sprite->getSymbol().getFilepath(), FileNameParser::e_mesh))
		{
			fixture.filepath = sprite->getSymbol().getFilepath();
		}
		else
		{
			wxString path = FilenameTools::getFilePathExceptExtension(sprite->getSymbol().getFilepath());
			wxString polygonPath = path + "_" + FileNameParser::getFileTag(FileNameParser::e_polyline) + ".txt";
			wxString circlePath = path + "_" + FileNameParser::getFileTag(FileNameParser::e_circle) + ".txt";
			if (FilenameTools::isExist(polygonPath))
				fixture.filepath = polygonPath;
			else if (FilenameTools::isExist(circlePath))
				fixture.filepath = circlePath;
		}

		fixture.pos = sprite->getPosition();
		fixture.angle = sprite->getAngle();
		fixture.scale = sprite->getScale();

		fixtures.push_back(fixture);
	}

	if (!fixtures.empty())
	{
		if (m_body) delete m_body;
		m_body = BodyFactory::createBody(fixtures, m_scale);
		m_body->getBody()->SetTransform(b2Vec2(m_pos.x / BOX2D_SCALE_FACTOR, m_pos.y / BOX2D_SCALE_FACTOR), m_angle);
	}
}

void CombinationSprite::buildBounding()
{
	delete m_bounding;
	m_bounding = BVFactory::createBV(e_obb);

	if (m_symbol)
	{
		f2AABB aabb = m_symbol->getBounding();

		aabb *= m_scale;
		aabb.translate(m_pos);
		m_bounding->initFromAABB(aabb);
		m_bounding->rotate(m_angle);
	}
}