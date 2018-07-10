#include "ArrangeSpriteOP.h"
#include "SpriteEditDialog.h"
#include "StagePanel.h"

using namespace deditor::skater;

ArrangeSpriteOP::ArrangeSpriteOP(StagePanel* editPanel,
								 wxgui::PropertySettingPanel* propertyPanel,
								 wxgui::AbstractEditCMPT* callback)
	: wxgui::ArrangeSpriteOP<wxgui::SelectSpritesOP>(editPanel, editPanel, propertyPanel, callback)
	, m_editPanel(editPanel)
{
}

bool ArrangeSpriteOP::onMouseLeftDClick(int x, int y)
{
	if (wxgui::ArrangeSpriteOP<wxgui::SelectSpritesOP>::onMouseLeftDClick(x, y)) return true;

	f2Vec2 pos = m_editPanel->transPosScreenToProject(x, y);
	wxgui::ISprite* selected = m_editPanel->querySpriteByPos(pos);

	wxgui::ImageSprite* sprite = dynamic_cast<wxgui::ImageSprite*>(selected);
	if (sprite)
	{
		SpriteEditDialog dlg(m_editPanel, sprite);
		dlg.ShowModal();
		m_editPanel->resetCanvas();
	}

	return false;
}