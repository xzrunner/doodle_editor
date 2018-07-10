#include "DrawUtils.h"
#include "BodyData.h"
#include "FixtureData.h"

using namespace deditor::modeling;

void DrawUtils::drawBody(BodyData* body, DrawType dType)
{
	f2Colorf cFace, cEdge;
	getBodyColor(body->m_type, dType, cFace, cEdge);

	wxgui::SpriteDraw::begin(body->m_sprite);
	body->draw(cFace, cEdge);
	wxgui::SpriteDraw::end(body->m_sprite);
}

void DrawUtils::drawFixture(FixtureData* fixture, DrawType dType,
							bool onlyFixture)
{
	f2Colorf cFace, cEdge;
	if (onlyFixture)
		getFixtureColor(dType, cFace, cEdge);
	else
		getBodyColor(fixture->body->m_type, dType, cFace, cEdge);

	wxgui::SpriteDraw::begin(fixture->body->m_sprite);
	fixture->draw(cFace, cEdge);
	wxgui::SpriteDraw::end(fixture->body->m_sprite);
}

void DrawUtils::getBodyColor(BodyData::Type type, DrawType dType,
							 f2Colorf& cFace, f2Colorf& cEdge)
{
	switch (type)
	{
	case BodyData::e_static:
		cFace.set(0.5f, 0.9f, 0.5f, 0.2f);
		break;
	case BodyData::e_kinematic:
		cFace.set(0.5f, 0.5f, 0.9f, 0.2f);
		break;
	case BodyData::e_dynamic:
		cFace.set(0.5f, 0.5f, 0.3f, 0.2f);
		break;
	}

	const float rScale = 1.1f,
		gScale = 1.1f,
		bScale = 0.5f;
	switch (dType)
	{
	case e_default:
		break;
	case e_mouseOn:
		cFace.r *= rScale;
		cFace.g *= gScale;
		cFace.b *= bScale;
		break;
	case e_selected:
		{
			f2Colorf c = cFace;
			c.r *= rScale;
			c.g *= gScale;
			c.b *= bScale;
			cFace = colorEnlarge(c, 1.1f);
		}
		break;
	}

	cEdge = colorEnlarge(cFace, 1.05f);
}

void DrawUtils::getFixtureColor(DrawType type, f2Colorf& cFace, f2Colorf& cEdge)
{
	cFace.set(0.6f, 0.35f, 0.6f, 0.5f);
	switch (type)
	{
	case e_mouseOn:
		cFace = colorEnlarge(cFace, 1.1f);
		break;
	case e_selected:
		cFace = colorEnlarge(cFace, 1.2f);
		break;
	}

	cEdge = colorEnlarge(cFace, 1.1f);
}

f2Colorf DrawUtils::colorEnlarge(const f2Colorf& color, float factor)
{
	f2Colorf ret = color;
	ret.r = std::min(color.r * factor, 1.0f);
	ret.g = std::min(color.g * factor, 1.0f);
	ret.b = std::min(color.b * factor, 1.0f);
	ret.a = color.a;

	return ret;
}