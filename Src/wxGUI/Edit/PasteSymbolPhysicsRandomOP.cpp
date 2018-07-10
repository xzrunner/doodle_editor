#include "PasteSymbolPhysicsRandomOP.h"

#include "Dataset/SpriteFactory.h"
#include "Dataset/IBody.h"
#include "View/LibraryPanel.h"
#include "View/MultiSpritesImpl.h"
#include "Render/SpriteDraw.h"
 
using namespace wxgui;

PasteSymbolPhysicsRandomOP::PasteSymbolPhysicsRandomOP(EditPanel* editPanel, MultiSpritesImpl* spritesImpl, 
													   LibraryPanel* libraryPanel, PhysicsPanelImpl* physicsImpl, 
													   PasteSymbolRandomWidget* randomWidget)
	: PasteSymbolPhysicsOP(editPanel, spritesImpl, libraryPanel, physicsImpl)
	, m_randomWidget(randomWidget)
{
	changeRandomValue();
}

bool PasteSymbolPhysicsRandomOP::onMouseLeftDown(int x, int y)
{
	if (ZoomViewOP::onMouseLeftDown(x, y)) return true;

	ISymbol* symbol = m_randomValue.symbol;
	if (!symbol) 
		symbol = m_libraryPanel->getSymbol();
	if (symbol) 
	{
		m_pos = m_editPanel->transPosScreenToProject(x, y);

		ISprite* sprite = SpriteFactory::create(symbol);
		sprite->translate(m_pos);

		if (m_randomValue.scale != 1.0f) 
			sprite->setScale(m_randomValue.scale);
		if (m_randomValue.angle != 0.0f) 
			sprite->setTransform(m_pos, m_randomValue.angle);
		if (sprite->getBody())
			sprite->getBody()->getBody()->SetType(m_bStatic ? b2_staticBody : b2_dynamicBody);
		m_panelImpl->insertSprite(sprite);
		sprite->release();
	}

	changeRandomValue();

	return false;
}

bool PasteSymbolPhysicsRandomOP::onMouseRightDown(int x, int y)
{
	if (PasteSymbolPhysicsOP::onMouseRightDown(x, y)) return true;

	changeRandomValue();

	return false;
}

bool PasteSymbolPhysicsRandomOP::onDraw() const
{
	if (ZoomViewOP::onDraw()) return true;

	ISymbol* symbol = m_randomValue.symbol;
	if (!symbol) 
		symbol = m_libraryPanel->getSymbol();
	if (symbol && m_pos.isValid())
		SpriteDraw::drawSprite(symbol, m_pos, m_randomValue.angle, m_randomValue.scale);

	return false;
}

void PasteSymbolPhysicsRandomOP::changeRandomValue()
{
	m_randomWidget->getRandomValue(m_randomValue);
}