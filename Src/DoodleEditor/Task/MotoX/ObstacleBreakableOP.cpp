#include "ObstacleBreakableOP.h"
#include "StagePanel.h"
#include "LibraryBreakableItem.h"
#include "BreakableSprite.h"
#include "TypesDef.h"

using namespace deditor::motox;

ObstacleBreakableOP::ObstacleBreakableOP(StagePanel* stagePanel, 
										 wxgui::LibraryPanel* libraryPanel)
	: ZoomViewOP(stagePanel, true)
	, m_stagePanel(stagePanel)
	, m_libraryPanel(libraryPanel)
	, m_bStatic(false)
{
	m_pos.setInvalid();
}

bool ObstacleBreakableOP::onMouseLeftDown(int x, int y)
{
	if (ZoomViewOP::onMouseLeftDown(x, y)) return true;

	LibraryBreakableItem* symbol = dynamic_cast<LibraryBreakableItem*>(m_libraryPanel->getSymbol());
	if (!symbol) return false;

	m_pos = m_editPanel->transPosScreenToProject(x, y);
	BreakableSprite* sprite = new BreakableSprite(symbol, !symbol->getSpriteCombineSymbol());
	sprite->loadBodyFromFile();
	sprite->getBody()->getBody()->SetUserData(new int(BREAKABLE_ID));
	sprite->setTransform(m_pos, 0);
	sprite->getBody()->getBody()->SetType(m_bStatic ? b2_staticBody : b2_dynamicBody);

	m_stagePanel->insertSprite(sprite);
	sprite->release();

	return false;
}

bool ObstacleBreakableOP::onMouseMove(int x, int y)
{
	if (ZoomViewOP::onMouseMove(x, y)) return true;

	m_pos = m_editPanel->transPosScreenToProject(x, y);
	m_editPanel->Refresh();

	return false;
}

bool ObstacleBreakableOP::onDraw() const
{
	if (ZoomViewOP::onDraw()) return true;

	LibraryBreakableItem* symbol = dynamic_cast<LibraryBreakableItem*>(m_libraryPanel->getSymbol());
	if (symbol && m_pos.isValid())
	{
		if (symbol->getSpriteCombineSymbol())
			wxgui::SpriteDraw::drawSprite(symbol->getSpriteCombineSymbol(), m_pos);
		else
			wxgui::SpriteDraw::drawSprite(symbol->getMeshCombineSymbol(), m_pos);
	}

	return false;
}

bool ObstacleBreakableOP::clear()
{
	if (ZoomViewOP::clear()) return true;

	m_pos.setInvalid();

	return false;
}