#include "PasteTileCombinationOP.h"
#include "PasteTileCombinationCMPT.h"
#include "LibraryCombinationItem.h"
#include "LibraryCombinationList.h"
#include "StagePanel.h"

using namespace deditor::motox;

PasteTileCombinationOP::PasteTileCombinationOP(StagePanel* stagePanel, 
									   wxgui::LibraryPanel* libraryPanel, 
									   PasteTileCombinationCMPT* cmpt)
	: ZoomViewOP(stagePanel, true)
	, m_stagePanel(stagePanel)
	, m_libraryPanel(libraryPanel)
	, m_cmpt(cmpt)
	, m_lastSelected(NULL)
{
	m_pos.setInvalid();

	m_lastSelected = dynamic_cast<LibraryCombinationItem*>(m_libraryPanel->getSymbol());
}

bool PasteTileCombinationOP::onMouseLeftDown(int x, int y)
{
	if (ZoomViewOP::onMouseLeftDown(x, y)) return true;

	if (!m_lastSelected)
		m_lastSelected = dynamic_cast<LibraryCombinationItem*>(m_libraryPanel->getSymbol());

	if (m_lastSelected)
	{
		const std::vector<wxgui::ISprite*>& sprites = m_lastSelected->getAllSprites();
		for (size_t i = 0, n = sprites.size(); i < n; ++i)
		{
			wxgui::ISprite* sprite = sprites[i]->clone();
			sprite->translate(m_pos - m_lastSelected->getCenter());
			m_stagePanel->insertSprite(sprite);
			sprite->release();
		}
	}

	if (m_cmpt->isIndexRamdomOpen())
		m_lastSelected = randomDrawing();

	return false;
}

bool PasteTileCombinationOP::onMouseRightDown(int x, int y)
{
	if (ZoomViewOP::onMouseMove(x, y)) return true;

	if (m_cmpt->isIndexRamdomOpen())
	{
		m_lastSelected = randomDrawing();
		m_editPanel->Refresh();
	}

	return false;
}

bool PasteTileCombinationOP::onMouseMove(int x, int y)
{
	if (ZoomViewOP::onMouseMove(x, y)) return true;

	if (!m_cmpt->isIndexRamdomOpen())
		m_lastSelected = dynamic_cast<LibraryCombinationItem*>(m_libraryPanel->getSymbol());

	m_pos = m_editPanel->transPosScreenToProject(x, y);
	m_editPanel->Refresh();

	return false;
}

bool PasteTileCombinationOP::onDraw() const
{
	if (ZoomViewOP::onDraw()) return true;

	if (m_lastSelected && m_pos.isValid())
	{
		const std::vector<wxgui::ISprite*>& sprites = m_lastSelected->getAllSprites();
		f2Vec2 offset = m_pos - m_lastSelected->getCenter();
		glPushMatrix();
		glTranslatef(offset.x, offset.y, 0.0f);
		for (size_t i = 0, n = sprites.size(); i < n; ++i)
			wxgui::SpriteDraw::drawSprite(sprites[i]);
		glPopMatrix();
	}

	return false;
}

bool PasteTileCombinationOP::clear()
{
	if (ZoomViewOP::clear()) return true;

	m_lastSelected = NULL;

	return false;
}

LibraryCombinationItem* PasteTileCombinationOP::randomDrawing() const
{
	std::vector<LibraryCombinationItem*> drawings;
	m_libraryPanel->traverse(FetchAllVisitor<LibraryCombinationItem>(drawings));
	const int index = static_cast<int>(drawings.size() * Random::getNum0To1());
	return drawings[index];
}