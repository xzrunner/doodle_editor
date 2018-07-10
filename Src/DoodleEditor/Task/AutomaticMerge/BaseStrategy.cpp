#include "BaseStrategy.h"

using namespace deditor::automatic_merge;

void BaseStrategy::sortByArea(std::vector<wxgui::ImageSprite*>& sprites, bool isDescend/* = true*/) const
{
	std::sort(sprites.begin(), sprites.end(), SpriteCmp(e_area, isDescend));
}

void BaseStrategy::sortByMaxEdge(std::vector<wxgui::ImageSprite*>& sprites, bool isDescend/* = true*/) const
{
	std::sort(sprites.begin(), sprites.end(), SpriteCmp(e_maxEdge, isDescend));
}

void BaseStrategy::sortByTotEdges(std::vector<wxgui::ImageSprite*>& sprites, bool isDescend/* = true*/) const
{
	std::sort(sprites.begin(), sprites.end(), SpriteCmp(e_totEdges, isDescend));
}

BaseStrategy::SpriteCmp::SpriteCmp(SortStrategy strategy, bool isDescend)
{
	m_strategy = strategy;
	m_isDescend = isDescend;
}

bool BaseStrategy::SpriteCmp::operator() (const wxgui::ImageSprite* s0, const wxgui::ImageSprite* s1) const
{
	bool isLess;

	switch (m_strategy)
	{
	case e_area:
		isLess = isAreaLess(s0, s1);
		break;
	case e_maxEdge:
		isLess = isEdgeLess(s0, s1);
		break;
	case e_totEdges:
		isLess = isTotEdgesLess(s0, s1);
		break;
	}

	if (m_isDescend) return !isLess;
	else return isLess;
}

bool BaseStrategy::SpriteCmp::isAreaLess(const wxgui::ImageSprite* s0, const wxgui::ImageSprite* s1) const
{
	return s0->getSymbol().getWidth() * s0->getSymbol().getHeight()
		<= s1->getSymbol().getWidth() * s1->getSymbol().getHeight();
}

bool BaseStrategy::SpriteCmp::isEdgeLess(const wxgui::ImageSprite* s0, const wxgui::ImageSprite* s1) const
{
	return std::max(s0->getSymbol().getWidth(), s0->getSymbol().getHeight())
		<= std::max(s1->getSymbol().getWidth(), s1->getSymbol().getHeight());
}

bool BaseStrategy::SpriteCmp::isTotEdgesLess(const wxgui::ImageSprite* s0, const wxgui::ImageSprite* s1) const
{
	return s0->getSymbol().getWidth() + s0->getSymbol().getHeight()
		<= s1->getSymbol().getWidth() + s1->getSymbol().getHeight();
}