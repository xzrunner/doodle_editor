#include "View.h"
#include "Blackboard.h"
#include "UICtrlsMgr.h"
#include "Dataset/LayersMgr.h"
#include "Render/Render.h"

using namespace FEDITOR;
using namespace FEDITOR::SIMULATE_CLOTH;

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
}

void View::onUIEvent(const Event& event)
{
	m_blackboard->pushEvent(event);
}