#include "View.h"
#include "UICtrlsMgr.h"
#include "Blackboard.h"
#include "../../../Dataset/LayersMgr.h"
#include "../../../Render/Render.h"
#include "glui/glui.h"

using namespace FEDITOR;
using namespace FEDITOR::MOTOX::LEVEL;

View::View(float scale/* = 1.0f*/)
	: AbstractView(scale)
{
	Blackboard* bb = new Blackboard;
	m_blackboard = bb;
	m_uiCtlsMgr = new UICtrlsMgr(bb);
}

void View::onDraw(const LayersMgr& layers) const
{
	Render::drawLayers(layers.getAllLayers());
	Render::drawSelection(layers.getSelectionConst());
}

void View::onUIEvent(const Event& event)
{
	switch (event.getID())
	{
	case Blackboard::e_ResetScale:
		{
			Blackboard* bb = static_cast<Blackboard*>(getBlackboard());
			bb->m_scaleSpinner->set_float_val(1.0f);
			bb->m_spriteScale = 0.0f;
			bb->m_flagSpriteMirror = 0;
		}
		break;

	default:
		m_blackboard->pushEvent(event);
	}
}