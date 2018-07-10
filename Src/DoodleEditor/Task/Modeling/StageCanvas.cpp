#include "StageCanvas.h"
#include "StagePanel.h"
#include "DrawUtils.h"
#include "JointData.h"

#include "Frame/defs.h"

using namespace deditor::modeling;

StageCanvas::StageCanvas(StagePanel* editPanel)
	: wxgui::GLCanvas(editPanel)
{
	m_bgColor.set(0, 0, 0, 1);
}

StageCanvas::~StageCanvas()
{
}

void StageCanvas::onDraw()
{
	drawGuideLines();
	drawSprites();
	static_cast<StagePanel*>(m_editPanel)->traverseJoints(DrawJointVisitor());
	m_editPanel->drawEditTemp();
}

void StageCanvas::drawGuideLines()
{
	drawCrossLine();
}

void StageCanvas::drawSprites()
{
	StagePanel* editPanel = static_cast<StagePanel*>(m_editPanel);
	std::vector<wxgui::ISprite*> sprites;
	editPanel->traverseSprites(FetchAllVisitor<wxgui::ISprite>(sprites));
	for (size_t i = 0, n = sprites.size(); i < n; ++i)
	{
		wxgui::SpriteDraw::drawSprite(sprites[i]);
		DrawUtils::drawBody(static_cast<BodyData*>(sprites[i]->getUserData()), DrawUtils::e_default);
	}
}

void StageCanvas::drawCrossLine() const
{
	const float halfEdge = 1000.0f;
	std::vector<f2Vec2> vertices(4);
	vertices[0].x = -halfEdge;
	vertices[1].x = halfEdge;
	vertices[2].y = -halfEdge;
	vertices[3].y = halfEdge;
	wxgui::PrimitiveDraw::drawLines(vertices, f2Colorf(0.7f, 0.9f, 0.7f), 1);
}

void StageCanvas::drawLines() const
{
 	const float halfEdge = 100.0f;
	// green
	{
		std::vector<f2Vec2> vertices;
		size_t size = halfEdge * 2 * 2 * 2;
		vertices.reserve(size);
		for (float x = -halfEdge; x <= halfEdge; x += 1.0f)
		{
			vertices.push_back(f2Vec2(x, -halfEdge));
			vertices.push_back(f2Vec2(x, halfEdge));
		}
		for (float y = -halfEdge; y <= halfEdge; y += 1.0f)
		{
			vertices.push_back(f2Vec2(-halfEdge, y));
			vertices.push_back(f2Vec2(halfEdge, y));
		}
		wxgui::PrimitiveDraw::drawLines(vertices, f2Colorf(0.7f, 0.9f, 0.7f), 1);
	}
	// red
	{
		std::vector<f2Vec2> vertices;
		size_t size = halfEdge * 0.1f * 2 * 2 * 2;
		vertices.reserve(size);
		for (float x = -halfEdge; x <= halfEdge; x += 10)
		{
			vertices.push_back(f2Vec2(x, -halfEdge));
			vertices.push_back(f2Vec2(x, halfEdge));
		}
		for (float y = -halfEdge; y <= halfEdge; y += 10)
		{
			vertices.push_back(f2Vec2(-halfEdge, y));
			vertices.push_back(f2Vec2(halfEdge, y));
		}
		wxgui::PrimitiveDraw::drawLines(vertices, f2Colorf(0.9f, 0.7f, 0.7f), 1);
	}
}

void StageCanvas::DrawJointVisitor::visit(IObject* object, bool& bFetchNext)
{
	JointData* joint = static_cast<JointData*>(object);
	joint->draw(JointData::e_default);
	bFetchNext = true;
}