#include "PasteSymbolPhysicsOP.h"

#include "Dataset/SpriteFactory.h"
#include "Dataset/IBody.h"
#include "View/LibraryPanel.h"
#include "View/PhysicsPanelImpl.h"
#include "View/MultiSpritesImpl.h"
 
using namespace wxgui;

PasteSymbolPhysicsOP::PasteSymbolPhysicsOP(EditPanel* editPanel, MultiSpritesImpl* spritesImpl, 
										   LibraryPanel* libraryPanel, PhysicsPanelImpl* physicsImpl,
										   float* pScale /*= NULL*/)
	: PasteSymbolOP(editPanel, spritesImpl, libraryPanel, pScale)
	, m_pScale(pScale)
	, m_bStatic(false)
{
	m_world = physicsImpl->getWorld();	
}

bool PasteSymbolPhysicsOP::onMouseLeftDown(int x, int y)
{
	if (ZoomViewOP::onMouseLeftDown(x, y)) return true;

	ISymbol* symbol = m_libraryPanel->getSymbol();
	if (symbol) 
	{
		m_pos = m_editPanel->transPosScreenToProject(x, y);

		ISprite* sprite = SpriteFactory::create(symbol);
		sprite->translate(m_pos);

		sprite->loadBodyFromFile();
		if (m_pScale) 
			sprite->setScale(*m_pScale);
		if (sprite->getBody())
			sprite->getBody()->getBody()->SetType(m_bStatic ? b2_staticBody : b2_dynamicBody);
		m_panelImpl->insertSprite(sprite);
		sprite->release();
	}

	return false;
}