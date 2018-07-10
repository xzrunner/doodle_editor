#include "DrawPolylineCmpt.h"
#include "CmptTypeID.h"
#include "NodeCaptureCmpt.h"
#include "../AbstractControl.h"
#include "../EditOperation/DrawPolylineOp.h"
#include "../EditOperation/DrawPolylineCB.h"
#include "../EditOperation/EditPolylineOp.h"
#include "../EditOperation/SelectCtlposOp.h"
#include "../../Dataset/Sprite.h"
#include "../../Dataset/Layer.h"
#include "../../Dataset/LayersMgr.h"
#include "../ShortcutKeyListener.h"
#include "glui/glui.h"

using namespace FEDITOR;

std::queue<Event> DrawPolylineCmpt::m_eventList;

DrawPolylineCmpt::DrawPolylineCmpt(AbstractControl* control, Sprite* sprite, Layer* layer)
	: AbstractCmpt(e_DrawPolylineCmpt, control->getCmptMgr())
{
	m_control = control;
	m_capture = new NodeCaptureCmpt(control->getLayersMgr(), control->getCmptMgr(), control->getScale());
	m_sprite = sprite;
	m_layer = layer;
	initTmpSprite();
	m_addToSingleSprite = sprite != NULL;
}

void DrawPolylineCmpt::createUIControls(GLUI_Node* parent, ShortcutKeyListener* shortcutLsn)
{
	if (dynamic_cast<GLUI*>(parent))
		largeLayoutUI(parent);
	else
		smallLayoutUI(parent);

	shortcutLsn->registerEventList(&m_eventList);
	shortcutLsn->registerKeyEvent('d', e_Draw);
	shortcutLsn->registerKeyEvent('e', e_Edit);
}

void DrawPolylineCmpt::handleUIEvent()
{
	while (!m_eventList.empty())
	{
		Event event = m_eventList.front(); m_eventList.pop();
		switch (event.getID())
		{
		case e_Draw:
			{
				std::vector<f2Vec2> preload;
				SelectCtlposOp* editOp = dynamic_cast<SelectCtlposOp*>(m_control->getEditOp());
				if (editOp) preload = editOp->getSelectedCtlpos();

				m_control->setEditOp(NULL);
				swapTmpSprite();
				m_control->setEditOp(new DrawPolylineOp(m_control, m_capture, new DrawPolylineCB(m_temp, preload)));
			}
			break;
		case e_Edit:
			m_control->setEditOp(NULL);
			swapTmpSprite();
			m_control->setEditOp(new EditPolylineOP(m_control, m_layer, m_capture));
			break;
		case e_Clear:
			clear();
			break;
		}
	}
}

void DrawPolylineCmpt::callback(int id)
{
	m_eventList.push(Event(id));
}

void DrawPolylineCmpt::smallLayoutUI(GLUI_Node* parent)
{
	GLUI_Panel* panel = new GLUI_Panel(parent, "", false);

	m_cmptMgr.createUIControls(panel, e_NodeCaptureCmpt);

	new GLUI_Button(panel, "Draw (D)", e_Draw, callback);
	new GLUI_Button(panel, "Edit (E)", e_Edit, callback);
	new GLUI_Button(panel, "Clear", e_Clear, callback);
}

void DrawPolylineCmpt::largeLayoutUI(GLUI_Node* parent)
{
	GLUI_Panel* panel = new GLUI_Panel(parent, "Edit Polyline");

	m_cmptMgr.createUIControls(panel, e_NodeCaptureCmpt);

	GLUI_Panel* btnPanel = new GLUI_Panel(panel, "");
	new GLUI_Button(btnPanel, "Draw (D)", e_Draw, callback);
	new GLUI_Button(btnPanel, "Edit (E)", e_Edit, callback);
	new GLUI_Button(btnPanel, "Clear", e_Clear, callback);
}

void DrawPolylineCmpt::initTmpSprite()
{
	Layer* layer = m_control->getLayersMgr().getLayer(Layer::e_uppermost);
	assert(layer);
	m_temp = new Sprite();
	layer->addSprite(m_temp);
}

void DrawPolylineCmpt::swapTmpSprite()
{
	if (m_temp->getAllShapes().empty()) return;

	if (m_addToSingleSprite)
	{
		const std::vector<Shape*>& shapes = m_temp->getAllShapes();
		for (size_t i = 0, n = shapes.size(); i < n; ++i)
		{
			ChainShape* shape = static_cast<ChainShape*>(shapes[i]);
			assert(shape);
			m_sprite->pushShape(shape->clone());
		}
	}
	else
	{
		Sprite* sprite = new Sprite(*m_temp);
		m_layer->addSprite(sprite);
	}

	m_temp->clearShapes();
}

void DrawPolylineCmpt::clear()
{
	if (m_addToSingleSprite)
		m_sprite->clearShapes();
	else
		m_layer->clearSprites();
}