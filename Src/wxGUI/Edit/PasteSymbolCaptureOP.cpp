#include "PasteSymbolCaptureOP.h"

#include "Dataset/SpriteFactory.h"
#include "Component/PasteSymbolCaptureCMPT.h"
#include "View/MultiSpritesImpl.h"
#include "View/LibraryPanel.h"

using namespace wxgui;

PasteSymbolCaptureOP::PasteSymbolCaptureOP(EditPanel* editPanel, MultiSpritesImpl* spritesImpl,
										   LibraryPanel* libraryPanel, PasteSymbolCaptureCMPT* cmpt)
	: PasteSymbolOP(editPanel, spritesImpl, libraryPanel)
	, m_cmpt(cmpt)
	, m_bCaptured(false)
{
	m_lastPos.setInvalid();
}

bool PasteSymbolCaptureOP::onMouseLeftDown(int x, int y)
{
	ISymbol* symbol = m_libraryPanel->getSymbol();
	if (symbol) 
	{
		if (!m_bCaptured)
			m_pos = m_editPanel->transPosScreenToProject(x, y);
		m_lastPos = m_pos;

		ISprite* sprite = SpriteFactory::create(symbol);
		sprite->translate(m_pos);
		m_panelImpl->insertSprite(sprite);
		sprite->release();
	}

	return false;
}

bool PasteSymbolCaptureOP::onMouseMove(int x, int y)
{
	if (ZoomViewOP::onMouseMove(x, y)) return true;

	m_bCaptured = false;
	m_pos = m_editPanel->transPosScreenToProject(x, y);
	if (m_lastPos.isValid())
	{
		f2Vec2 offset = m_cmpt->getOffset();
		f2Vec2 newPos = m_lastPos + offset;
		if (f2Math::getDistance(m_pos, newPos) < 
			f2Math::getDistance(offset, f2Vec2(0, 0)))
		{
			m_bCaptured = true;
			m_pos = newPos;
		}
	}
	m_editPanel->Refresh();

	return false;
}

bool PasteSymbolCaptureOP::clear()
{
	if (PasteSymbolOP::clear()) return true;

	m_lastPos.setInvalid();

	return false;
}