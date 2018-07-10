#include "GuidelinesLongCmpt.h"
#include "CmptTypeID.h"
#include "Dataset/ChainShape.h"
#include "Dataset/Sprite.h"
#include "Dataset/Layer.h"
#include "Dataset/LayersMgr.h"
#include "Tools/ShapeCreator.h"
#include "glui/glui.h"

using namespace FEDITOR;

std::queue<Event> GuidelinesLongCmpt::m_eventList;

GuidelinesLongCmpt::GuidelinesLongCmpt(LayersMgr& layers, CmptMgr& cmptMgr, int baseLength/* = 100*/)
	: AbstractCmpt(e_GuidelinesCmpt, cmptMgr)
{
	m_type = 0;
	m_gridXSize = baseLength;
	m_gridYSize = 1;

	m_setGridXSize = m_setGridYSize = NULL;

	m_displayAxes = 1;

	Layer* layer = layers.getLayer(Layer::e_lowermost);
	layer->m_style.m_bDrawCtlPos = false;
	m_sprite = new Sprite;
	layer->addSprite(m_sprite);

	changeGuidelines();
}

void GuidelinesLongCmpt::createUIControls(GLUI_Node* parent, ShortcutKeyListener* shortcutLsn)
{
	if (dynamic_cast<GLUI*>(parent))
		largeLayoutUI(parent);
	else
		smallLayoutUI(parent);
}

void GuidelinesLongCmpt::handleUIEvent()
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
		case e_SetDisplayAxes:
			changeGuidelines();
			break;
		}
	}
}

void GuidelinesLongCmpt::smallLayoutUI(GLUI_Node* parent)
{
	new GLUI_StaticText(parent, "Guidelines");

	GLUI_RadioGroup* choose = new GLUI_RadioGroup(parent, &m_type, e_SetType, callback);
	new GLUI_RadioButton(choose, "Null");
	new GLUI_RadioButton(choose, "only x");
	new GLUI_RadioButton(choose, "xy grids");

	m_setGridXSize = new GLUI_Spinner(parent, "X Size: ", &m_gridXSize, e_SetGridSize, callback);
	m_setGridXSize->set_int_limits(1, 1000);
	m_setGridYSize = new GLUI_Spinner(parent, "Y Size: ", &m_gridYSize, e_SetGridSize, callback);
	m_setGridYSize->set_int_limits(1, 100);

	new GLUI_Checkbox(parent, "Axes: ", &m_displayAxes, e_SetDisplayAxes, callback);

	new GLUI_Separator(parent);
}

void GuidelinesLongCmpt::largeLayoutUI(GLUI_Node* parent)
{
	GLUI_Panel* panel = new GLUI_Panel(parent, "Guidelines");

	GLUI_RadioGroup* choose = new GLUI_RadioGroup(panel, &m_type, e_SetType, callback);
	new GLUI_RadioButton(choose, "Null");
	new GLUI_RadioButton(choose, "only x");
	new GLUI_RadioButton(choose, "xy grids");

	m_setGridXSize = new GLUI_Spinner(panel, "X Size: ", &m_gridXSize, e_SetGridSize, callback);
	m_setGridXSize->set_int_limits(1, 1000);
	m_setGridYSize = new GLUI_Spinner(panel, "Y Size: ", &m_gridYSize, e_SetGridSize, callback);
	m_setGridYSize->set_int_limits(1, 100);

	new GLUI_Checkbox(panel, "Axes: ", &m_displayAxes, e_SetDisplayAxes, callback);
}

void GuidelinesLongCmpt::changeGuidelines()
{
	switch (m_type)
	{
	case 0:
		m_sprite->clearShapes();
		break;
	case 1:
		m_sprite->clearShapes();
		createXGuidelines();
		break;
	case 2:
		m_sprite->clearShapes();
		createXYGuidelines();
		break;
	}

	if (m_displayAxes == 1) createCoordinateAxes();

	if (m_setGridXSize && m_setGridYSize)
	{
		if (m_type == 0) 
		{
			m_setGridXSize->disable();
			m_setGridYSize->disable();
		}
		else 
		{
			m_setGridXSize->enable();
			m_setGridYSize->enable();
		}
	}
}

void GuidelinesLongCmpt::createXGuidelines()
{
	const float startY = - (int) (m_gridYSize / 2) * SCREEN_HEIGHT;
	for (size_t i = 0; i <= m_gridYSize; ++i)
	{
		ChainShape* line = new ChainShape;
		line->pushBack(f2Vec2(0.0f, startY + SCREEN_HEIGHT * i));
		line->pushBack(f2Vec2(SCREEN_WIDTH * m_gridXSize, startY + SCREEN_HEIGHT * i));
		m_sprite->pushShape(line);
	}
}

void GuidelinesLongCmpt::createXYGuidelines()
{
	const float startY = - (int) (m_gridYSize / 2) * SCREEN_HEIGHT,
		endY = startY + SCREEN_HEIGHT * m_gridYSize;

	for (size_t i = 0; i <= m_gridYSize; ++i)
	{
		ChainShape* line = new ChainShape;
		line->pushBack(f2Vec2(0.0f, startY + SCREEN_HEIGHT * i));
		line->pushBack(f2Vec2(SCREEN_WIDTH * m_gridXSize, startY + SCREEN_HEIGHT * i));
		m_sprite->pushShape(line);
	}

	for (size_t i = 0; i <= m_gridXSize; ++i)
	{
		ChainShape* line = new ChainShape;
		line->pushBack(f2Vec2(SCREEN_WIDTH * i, startY));
		line->pushBack(f2Vec2(SCREEN_WIDTH * i, endY));
		m_sprite->pushShape(line);
	}
}

void GuidelinesLongCmpt::createCoordinateAxes()
{
	const float extendRatio = 0.1f;

	const float startY = - (int) (m_gridYSize / 2) * SCREEN_HEIGHT,
		endY = startY + SCREEN_HEIGHT * m_gridYSize;
	const float startX = 0.0f, endX = SCREEN_WIDTH * m_gridXSize;

// 	const float xExtend = (endX - startX) * extendRatio,
// 		yExtend = (endY - startY) * extendRatio;
	const float xExtend = SCREEN_WIDTH * extendRatio,
		yExtend = SCREEN_WIDTH * extendRatio;

	ChainShape* hor = new ChainShape;
	hor->pushBack(f2Vec2(startX - xExtend, 0.0f));
	hor->pushBack(f2Vec2(endX + xExtend, 0.0f));
	m_sprite->pushShape(hor);

	Shape* toRight = ShapeCreator::arrow(f2Vec2(endX + xExtend, 0.0f), 3);
	m_sprite->pushShape(toRight);

	ChainShape* vert = new ChainShape;
	vert->pushBack(f2Vec2(startX, startY - yExtend));
	vert->pushBack(f2Vec2(startX, endY + yExtend));
	m_sprite->pushShape(vert);

	Shape* toUp = ShapeCreator::arrow(f2Vec2(startX, endY + yExtend), 0);
	m_sprite->pushShape(toUp);
}

void GuidelinesLongCmpt::callback(int id)
{
	m_eventList.push(Event(id));
}