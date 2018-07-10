#include "AEPartsOP.h"
#include "AEEditPanel.h"
#include "LibraryActorItem.h"

using namespace deditor::motox;

AEPartsOP::AEPartsOP(AEEditPanel* editPanel, AEPartsCMPT* cmpt,
					 wxgui::PropertySettingPanel* propertyPanel)
	: wxgui::ArrangeSpriteOP<wxgui::SelectSpritesOP>(editPanel, editPanel, propertyPanel)
	, m_parts(editPanel->getParts())
{
	m_cmpt = cmpt;
}

bool AEPartsOP::onMouseLeftDown(int x, int y)
{
	if (wxgui::ArrangeSpriteOP<wxgui::SelectSpritesOP>::onMouseLeftDown(x, y)) return true;

	resetSelectionToPart();

	return false;
}

bool AEPartsOP::onMouseLeftUp(int x, int y)
{
	if (wxgui::ArrangeSpriteOP<wxgui::SelectSpritesOP>::onMouseLeftUp(x, y)) return true;

	resetSelectionToPart();

	return false;
}

void AEPartsOP::loadPart(wxgui::ISymbol* symbol, const f2Vec2& pos)
{
	AEParts& parts = static_cast<AEEditPanel*>(m_editPanel)->getParts();
	parts.loadPart(m_cmpt->getSelectedID(), symbol, pos);
	symbol->reloadTexture();
}

void AEPartsOP::translateSprite(const f2Vec2& delta)
{
	wxgui::ArrangeSpriteOP<wxgui::SelectSpritesOP>::translateSprite(delta);
	afterSpriteArrange();
}

void AEPartsOP::rotateSprite(const f2Vec2& dst)
{
	wxgui::ArrangeSpriteOP<wxgui::SelectSpritesOP>::rotateSprite(dst);
	afterSpriteArrange();
}

void AEPartsOP::afterSpriteArrange()
{
	AEParts& parts = static_cast<AEEditPanel*>(m_editPanel)->getParts();
	m_selection->traverse(UpdateVisitor(parts));
}

void AEPartsOP::resetSelectionToPart()
{
	AEParts& parts = static_cast<AEEditPanel*>(m_editPanel)->getParts();
	int part0, part1;
	parts.mapCtrlIDToPartIDs(m_cmpt->getSelectedID(), part0, part1);
	if (part1 == -1)
	{
		wxgui::ISprite* sprite0 = parts.getPart(part0);
		if (m_selection->isExist(sprite0))
		{
			m_selection->clear();
			m_selection->insert(sprite0);
		}
		else
		{
			m_selection->clear();
		}
	}
	else
	{
		wxgui::ISprite *sprite0 = parts.getPart(part0),
			*sprite1 = parts.getPart(part1);
		if (m_selection->isExist(sprite0) || m_selection->isExist(sprite1))
		{
			m_selection->clear();
			m_selection->insert(sprite0);
		}
		else
		{
			m_selection->clear();
		}
	}
}

//////////////////////////////////////////////////////////////////////////
// class AEPartsOP::UpdateVisitor
//////////////////////////////////////////////////////////////////////////

AEPartsOP::UpdateVisitor::UpdateVisitor(AEParts& parts)
	: m_parts(parts)
{
}

void AEPartsOP::UpdateVisitor::
visit(IObject* object, bool& bFetchNext)
{
	wxgui::ISprite* sprite = static_cast<wxgui::ISprite*>(object);

	for (size_t i = 0; i < PARTS_COUNT; ++i)
	{
		if (sprite == m_parts.getPart(i))
		{
			m_parts.m_params.m_parts[i].pos = sprite->getPosition();
			m_parts.m_params.m_parts[i].angle = sprite->getAngle();
		}
	}

	update(sprite, e_PartBigArmLeft, e_PartBigArmRight);
	update(sprite, e_PartSmallArmLeft, e_PartSmallArmRight);
	update(sprite, e_PartBigLegLeft, e_PartBigLegRight);
	update(sprite, e_PartSmallLegLeft, e_PartSmallLegRight);

	bFetchNext = true;
}

void AEPartsOP::UpdateVisitor::
update(wxgui::ISprite* changed, int id0, int id1)
{
	wxgui::ISprite *pair0 = m_parts.getPart(id0), 
		*pair1 = m_parts.getPart(id1);

	if (changed == pair0)
	{
		pair1->setTransform(pair0->getPosition(), pair0->getAngle());
		m_parts.m_params.m_parts[id1].pos = pair0->getPosition();
		m_parts.m_params.m_parts[id1].angle = pair0->getAngle();
	}
	if (changed == pair1)
	{
		pair0->setTransform(pair1->getPosition(), pair1->getAngle());
		m_parts.m_params.m_parts[id0].pos = pair1->getPosition();
		m_parts.m_params.m_parts[id0].angle = pair1->getAngle();
	}
}