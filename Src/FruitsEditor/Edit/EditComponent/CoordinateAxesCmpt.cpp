#include "CoordinateAxesCmpt.h"
#include "CmptTypeID.h"
#include "Dataset/ChainShape.h"
#include "Dataset/Sprite.h"
#include "Dataset/Layer.h"
#include "Dataset/LayersMgr.h"
#include "Tools/ShapeCreator.h"
#include "glui/glui.h"

using namespace FEDITOR;

std::queue<Event> CoordinateAxesCmpt::m_eventList;

CoordinateAxesCmpt::CoordinateAxesCmpt(LayersMgr& layers, CmptMgr& cmptMgr)
	: AbstractCmpt(e_CoordinateAxesCmpt, cmptMgr)
{
	m_type = 0;
	m_flagDisplay = 1;

	Layer* layer = layers.getLayer(Layer::e_lowermost);
	layer->m_style.m_bDrawCtlPos = false;
	m_sprite = new Sprite;
	layer->addSprite(m_sprite);

	changeCoordinateAxes();
}

void CoordinateAxesCmpt::createUIControls(GLUI_Node* parent, ShortcutKeyListener* shortcutLsn)
{
	if (dynamic_cast<GLUI*>(parent))
		largeLayoutUI(parent);
	else
		smallLayoutUI(parent);
}

void CoordinateAxesCmpt::handleUIEvent()
{
	while (!m_eventList.empty())
	{
		Event event = m_eventList.front(); m_eventList.pop();
		switch (event.getID())
		{
		case e_SetType:
			changeCoordinateAxes();
			break;
		case e_SetDisplay:
			changeDisplay();
			break;
		}
	}
}

f2Vec2 CoordinateAxesCmpt::transToCurrCoordinate(const f2Vec2& pos) const
{
	f2Vec2 ret = pos;
	switch (m_type)
	{
	case 1:
		ret.x = pos.x + SCREEN_WIDTH * 0.5f;
		ret.y = SCREEN_HEIGHT * 0.5f - pos.y;
		break;
	case 2:
		ret.x = pos.x + SCREEN_WIDTH * 0.5f;
		ret.y = pos.y + SCREEN_HEIGHT * 0.5f;
		break;
	}
	return ret;
}

void CoordinateAxesCmpt::smallLayoutUI(GLUI_Node* parent)
{
	new GLUI_StaticText(parent, "Coordinate");

	GLUI_RadioGroup* choose = new GLUI_RadioGroup(parent, &m_type, e_SetType, callback);
	new GLUI_RadioButton(choose, "Center");
	new GLUI_RadioButton(choose, "Left Top");
	new GLUI_RadioButton(choose, "Left Bottom");

	new GLUI_Checkbox(parent, "Display", &m_flagDisplay, e_SetDisplay, callback);

	new GLUI_Separator(parent);
}

void CoordinateAxesCmpt::largeLayoutUI(GLUI_Node* parent)
{
	GLUI_Panel* panel = new GLUI_Panel(parent, "Coordinate");

	GLUI_RadioGroup* choose = new GLUI_RadioGroup(panel, &m_type, e_SetType, callback);
	new GLUI_RadioButton(choose, "Center");
	new GLUI_RadioButton(choose, "Left Top");
	new GLUI_RadioButton(choose, "Left Bottom");

	new GLUI_Checkbox(panel, "Display", &m_flagDisplay, e_SetDisplay, callback);
}

void CoordinateAxesCmpt::changeCoordinateAxes()
{
	if (m_flagDisplay == 0) return;

	switch (m_type)
	{
	case 0:
		m_sprite->clearShapes();
		createCenterLines();
		break;
	case 1:
		m_sprite->clearShapes();
		createLeftTopLines();
		break;
	case 2:
		m_sprite->clearShapes();
		createLeftBottomLines();
		break;
	}
}

void CoordinateAxesCmpt::changeDisplay()
{
	if (m_flagDisplay == 1)
		changeCoordinateAxes();
	else
		m_sprite->clearShapes();
}

void CoordinateAxesCmpt::createCenterLines()
{
	const float w = SCREEN_WIDTH, h = SCREEN_HEIGHT;

	ChainShape* hor = new ChainShape;
	hor->pushBack(f2Vec2(-w * 0.25f, 0.0f));
	hor->pushBack(f2Vec2( w * 1.0f, 0.0f));
	m_sprite->pushShape(hor);

	Shape* toRight = ShapeCreator::arrow(f2Vec2(w * 1.0f, 0.0f), 3);
	m_sprite->pushShape(toRight);

	ChainShape* vert = new ChainShape;
	vert->pushBack(f2Vec2(0.0f, -h * 0.25f));
	vert->pushBack(f2Vec2(0.0f,  h * 1.0f));
	m_sprite->pushShape(vert);

	Shape* toUp = ShapeCreator::arrow(f2Vec2(0.0f, h * 1.0f), 0);
	m_sprite->pushShape(toUp);
}

void CoordinateAxesCmpt::createLeftTopLines()
{
	const float w = SCREEN_WIDTH, h = SCREEN_HEIGHT;

	ChainShape* hor = new ChainShape;
	hor->pushBack(f2Vec2(-w * 0.75f, h * 0.5f));
	hor->pushBack(f2Vec2( w * 1.0f, h * 0.5f));
	m_sprite->pushShape(hor);

	Shape* toRight = ShapeCreator::arrow(f2Vec2(w * 1.0f, h * 0.5f), 3);
	m_sprite->pushShape(toRight);

	ChainShape* vert = new ChainShape;
	vert->pushBack(f2Vec2(-w * 0.5f,  h * 0.75f));
	vert->pushBack(f2Vec2(-w * 0.5f, -h * 1.0f));
	m_sprite->pushShape(vert);

	Shape* toDown = ShapeCreator::arrow(f2Vec2(-w * 0.5f,  -h * 1.0f), 1);
	m_sprite->pushShape(toDown);
}

void CoordinateAxesCmpt::createLeftBottomLines()
{
	const float w = SCREEN_WIDTH, h = SCREEN_HEIGHT;

	ChainShape* hor = new ChainShape;
	hor->pushBack(f2Vec2(-w * 0.75f, -h * 0.5f));
	hor->pushBack(f2Vec2( w * 1.0f, -h * 0.5f));
	m_sprite->pushShape(hor);

	Shape* toRight = ShapeCreator::arrow(f2Vec2(w * 1.0f, -h * 0.5f), 3);
	m_sprite->pushShape(toRight);

	ChainShape* vert = new ChainShape;
	vert->pushBack(f2Vec2(-w * 0.5f, -h * 0.75f));
	vert->pushBack(f2Vec2(-w * 0.5f,  h * 1.0f));
	m_sprite->pushShape(vert);

	Shape* toUp = ShapeCreator::arrow(f2Vec2(-w * 0.5f, h * 1.0f), 0);
	m_sprite->pushShape(toUp);
}

void CoordinateAxesCmpt::callback(int id)
{
	m_eventList.push(Event(id));
}