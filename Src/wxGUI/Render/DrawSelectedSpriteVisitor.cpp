#include "DrawSelectedSpriteVisitor.h"
#include "PrimitiveDraw.h"

#include "Dataset/ISprite.h"

using namespace wxgui;

DrawSelectedSpriteVisitor::DrawSelectedSpriteVisitor(const f2Colorf& color)
	: m_color(color)
{}

void DrawSelectedSpriteVisitor::visit(IObject* object, bool& bFetchNext) 
{
	std::vector<f2Vec2> bound;
	ISprite* sprite = static_cast<ISprite*>(object);
	sprite->getBounding()->getBoundPos(bound);

	PrimitiveDraw::drawPolyline(bound, m_color, true);

	bFetchNext = true;
}