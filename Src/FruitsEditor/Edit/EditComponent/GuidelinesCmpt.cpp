#include "GuidelinesCmpt.h"
#include "CmptTypeID.h"
#include "Dataset/ChainShape.h"
#include "Dataset/Sprite.h"
#include "Dataset/Layer.h"
#include "Dataset/LayersMgr.h"
#include "glui/glui.h"

using namespace FEDITOR;

std::queue<Event> GuidelinesCmpt::m_eventList;

GuidelinesCmpt::GuidelinesCmpt(LayersMgr& layers, CmptMgr& cmptMgr)
	: AbstractCmpt(e_GuidelinesCmpt, cmptMgr)
{
	m_type = 0;
	m_gridSize = 1;

	m_setGridSize = NULL;

	Layer* layer = layers.getLayer(Layer::e_lowermost);
	layer->m_style.m_bDrawCtlPos = false;
	m_sprite = new Sprite;
	layer->addSprite(m_sprite);

	changeGuidelines();
}

void GuidelinesCmpt::createUIControls(GLUI_Node* parent, ShortcutKeyListener* shortcutLsn)
{
	if (dynamic_cast<GLUI*>(parent))
		largeLayoutUI(parent);
	else
		smallLayoutUI(parent);
}

void GuidelinesCmpt::handleUIEvent()
{
	while (!m_eventList.empty())
	{
		Event event = m_eventList.front(); m_eventList.pop();
		switch (event.getID())
		{
		case e_SetType:
			changeGuidelines();
			break;
		case e_SetGridSize:
			changeGuidelines();
			break;
		}
	}
}

void GuidelinesCmpt::smallLayoutUI(GLUI_Node* parent)
{
	new GLUI_StaticText(parent, "Guidelines");

	GLUI_RadioGroup* choose = new GLUI_RadioGroup(parent, &m_type, e_SetType, callback);
	new GLUI_RadioButton(choose, "Null");
	new GLUI_RadioButton(choose, "Polygon");
	new GLUI_RadioButton(choose, "Cross");
	new GLUI_RadioButton(choose, "Grid");

	m_setGridSize = new GLUI_Spinner(parent, "Grid Size: ", &m_gridSize, e_SetGridSize, callback);
	m_setGridSize->set_int_limits(1, 50);
	if (m_type != 3) m_setGridSize->disable();

	new GLUI_Separator(parent);
}

void GuidelinesCmpt::largeLayoutUI(GLUI_Node* parent)
{
	GLUI_Panel* panel = new GLUI_Panel(parent, "Guidelines");

	GLUI_RadioGroup* choose = new GLUI_RadioGroup(panel, &m_type, e_SetType, callback);
	new GLUI_RadioButton(choose, "Null");
	new GLUI_RadioButton(choose, "Polygon");
	new GLUI_RadioButton(choose, "Cross");
	new GLUI_RadioButton(choose, "Grid");

	m_setGridSize = new GLUI_Spinner(panel, "Grid Size: ", &m_gridSize, e_SetGridSize, callback);
	m_setGridSize->set_int_limits(1, 50);
	if (m_type != 3) m_setGridSize->disable();
}

void GuidelinesCmpt::changeGuidelines()
{
	switch (m_type)
	{
	case 0:
		m_sprite->clearShapes();
		break;
	case 1:
		m_sprite->clearShapes();
		createPolygonLines();
		break;
	case 2:
		m_sprite->clearShapes();
		createCrossLines();
		break;
	case 3:
		m_sprite->clearShapes();
		createGridLines();
		break;
	}

	if (m_setGridSize)
	{
		if (m_type == 3) m_setGridSize->enable();
		else m_setGridSize->disable();
	}
}

void GuidelinesCmpt::createPolygonLines()
{
	const float hw = SCREEN_WIDTH * 0.5f,
		hh = SCREEN_HEIGHT * 0.5f;

	ChainShape* shape = new ChainShape;
	shape->pushBack(f2Vec2(-hw, -hh));
	shape->pushBack(f2Vec2( hw, -hh));
	shape->pushBack(f2Vec2( hw,  hh));
	shape->pushBack(f2Vec2(-hw,  hh));
	shape->m_isLoop = true;
	m_sprite->pushShape(shape);
}

void GuidelinesCmpt::createCrossLines()
{
	ChainShape* hor = new ChainShape;
	hor->pushBack(f2Vec2(-SCREEN_WIDTH, 0.0f));
	hor->pushBack(f2Vec2( SCREEN_WIDTH, 0.0f));
	m_sprite->pushShape(hor);

	ChainShape* vert = new ChainShape;
	vert->pushBack(f2Vec2(0.0f, -SCREEN_HEIGHT));
	vert->pushBack(f2Vec2(0.0f,  SCREEN_HEIGHT));
	m_sprite->pushShape(vert);
}

void GuidelinesCmpt::createGridLines()
{
	const float hw = SCREEN_WIDTH * 0.5f,
		hh = SCREEN_HEIGHT * 0.5f;

	for (float y = -hh; y <= hh; y += m_gridSize)
	{
		ChainShape* line = new ChainShape;
		line->pushBack(f2Vec2(-hw, y));
		line->pushBack(f2Vec2( hw, y));
		m_sprite->pushShape(line);
	}

	for (float x = -hw; x <= hw; x += m_gridSize)
	{
		ChainShape* line = new ChainShape;
		line->pushBack(f2Vec2(x, -hh));
		line->pushBack(f2Vec2(x,  hh));
		m_sprite->pushShape(line);
	}
}

void GuidelinesCmpt::callback(int id)
{
	m_eventList.push(Event(id));
}