#include "ArrangeSpriteOP.h"
#include "Dataset/Sprite.h"
#include "View/SpriteEditDialog.h"
#include "View/StagePanel.h"

using namespace FRUITS_ANIMATOR;

ArrangeSpriteOP::ArrangeSpriteOP(StagePanel* editPanel)
	: wxgui::ArrangeSpriteOP(editPanel, editPanel)
	, m_editPanel(editPanel)
{	
}

bool ArrangeSpriteOP::onMouseLeftDClick(int x, int y)
{
	if (wxgui::ArrangeSpriteOP::onMouseLeftDClick(x, y)) return true;

	f2Vec2 pos = m_editPanel->transPosScreenToProject(x, y);
	f2Sprite* selected = m_editPanel->querySpriteByPos(pos);

	Sprite* actor = static_cast<Sprite*>(selected);
	SpriteEditDialog dlg(m_editPanel, actor);
	dlg.ShowModal();
	m_editPanel->resetCanvas();

	return false;
}