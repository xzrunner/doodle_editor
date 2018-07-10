#include "NodeCaptureCmpt.h"
#include "CmptTypeID.h"
#include "../../Dataset/Layer.h"
#include "../../Dataset/LayersMgr.h"
#include "../../Dataset/Sprite.h"
#include "glui/glui.h"

using namespace FEDITOR;

NodeCaptureCmpt::NodeCaptureCmpt(LayersMgr& layers, CmptMgr& cmptMgr, float scale/* = 1.0f*/)
	: AbstractCmpt(e_NodeCaptureCmpt, cmptMgr), m_layers(layers)
{
	m_scale = scale;
	createCaptureLayer();
}

void NodeCaptureCmpt::createUIControls(GLUI_Node* parent, ShortcutKeyListener* shortcutLsn)
{
	m_uiCtrls.createUIControls(parent);
}

void NodeCaptureCmpt::handleUIEvent()
{
	while (!m_uiCtrls.m_eventList.empty())
	{
		Event event = m_uiCtrls.m_eventList.front(); m_uiCtrls.m_eventList.pop();
		switch (event.getID())
		{
		case UICtrls::e_SetState:
			m_uiCtrls.onEvent(event);
			break;
		}
	}
}

bool NodeCaptureCmpt::captureByPos(const f2Vec2& pos)
{
	if (!isOpen()) return false;

	const float dis = f2Math::getDistance(pos, m_dst->m_pos);
	if (dis > getTolerance()) 
	{
		const bool capture = captureByPos(pos, m_src.isValid());
		if (capture)
			return true;
		else
		{
			clear();
			return false;
		}
	}
	else
		return true;
}

const ChainShapeAddr& NodeCaptureCmpt::getCapturedAddr() const
{
	return m_src;
}

void NodeCaptureCmpt::createCaptureLayer()
{
	const std::vector<Layer*>& layers = m_layers.getAllLayers();
	Layer* layer = NULL;
	for (size_t i = 0, n = layers.size(); i < n; ++i)
	{
		if (layers[i]->getType() == Layer::e_uppermost)
		{
			layer = layers[i];
			break;
		}
	}

	if (!layer)
	{
		layer = new Layer(Layer::e_middle, "Capture");
		m_layers.addLayer(layer);
	}

	layer->m_style.m_pointStyle.size = 10;
	layer->m_style.m_pointStyle.color = f2Colorf(0, 0.5f, 0.5f);

	m_dst = new PointShape;
	m_dst->m_pos.set(FLOAT_MAX, FLOAT_MAX);
	Sprite* sprite = new Sprite;
	sprite->pushShape(m_dst);
	layer->addSprite(sprite);
}

bool NodeCaptureCmpt::captureByPos(const f2Vec2& pos, bool preferPrevious)
{
	if (preferPrevious)
	{
		const bool capture = captureByPos(pos, m_src.layer, true);
		if (capture) 
		{
			return true;
		}
		else
		{
			const std::vector<Layer*> layers = m_layers.getAllLayers();
			for (size_t i = 0, n = layers.size(); i < n; ++i)
			{
				Layer* layer = layers[i];
				if (layer == m_src.layer) continue;
				if (layer->getType() == Layer::e_uppermost) continue;

				const bool capture = captureByPos(pos, layer, false);
				if (capture) return true;
			}
			return false;
		}
	}
	else
	{
		const std::vector<Layer*> layers = m_layers.getAllLayers();
		for (size_t i = 0, n = layers.size(); i < n; ++i)
		{
			Layer* layer = layers[i];
			if (layer->getType() == Layer::e_uppermost) continue;

			const bool capture = captureByPos(pos, layer, false);
			if (capture) return true;
		}
		return false;
	}
}

bool NodeCaptureCmpt::captureByPos(const f2Vec2& pos, Layer* layer, bool preferPrevious)
{
	if (!layer->isVisible()) return false;

	if (preferPrevious)
	{
		const bool capture = captureByPos(pos, m_src.sprite, true);
		if (capture) 
		{
			m_src.layer = layer;
			return true;
		}
		else
		{
			const std::vector<Sprite*>& sprites = layer->getAllSprites();
			for (size_t i = 0, n = sprites.size(); i < n; ++i)
			{
				Sprite* sprite = sprites[i];
				if (sprite == m_src.sprite) continue;

				const bool capture = captureByPos(pos, sprite, false);
				if (capture) 
				{
					m_src.layer = layer;
					return true;
				}
			}
			return false;
		}
	}
	else
	{
		const std::vector<Sprite*>& sprites = layer->getAllSprites();
		for (size_t i = 0, n = sprites.size(); i < n; ++i)
		{
			Sprite* sprite = sprites[i];

			const bool capture = captureByPos(pos, sprite, false);
			if (capture) 
			{
				m_src.layer = layer;
				return true;
			}
		}
		return false;
	}
}

bool NodeCaptureCmpt::captureByPos(const f2Vec2& pos, Sprite* sprite, bool preferPrevious)
{
	if (preferPrevious)
	{
		const bool capture = captureByPos(pos, m_src.shape, true);
		if (capture)
		{
			m_src.sprite = sprite;
			return true;
		}
		else
		{
			const std::vector<Shape*>& shapes = sprite->getAllShapes();
			for (size_t i = 0, n = shapes.size(); i < n; ++i)
			{
				Shape* shape = shapes[i];
				if (shape == m_src.shape) continue;

				const bool capture = captureByPos(pos, shape, false);
				if (capture) 
				{
					m_src.sprite = sprite;
					return true;
				}
			}
			return false;
		}
	}
	else
	{
		const std::vector<Shape*>& shapes = sprite->getAllShapes();
		for (size_t i = 0, n = shapes.size(); i < n; ++i)
		{
			Shape* shape = shapes[i];

			const bool capture = captureByPos(pos, shape, false);
			if (capture) 
			{
				m_src.sprite = sprite;
				return true;
			}
		}
		return false;
	}
}

bool NodeCaptureCmpt::captureByPos(const f2Vec2& pos, Shape* shape, bool preferPrevious)
{
	if (shape->getType() != e_chain) return false;

	ChainShape* cs = dynamic_cast<ChainShape*>(shape);
	assert(cs != NULL);

	if (preferPrevious)
	{
		const float dis = f2Math::getDistance(pos, cs->m_vertices[m_src.iPos]);
		if (dis < getTolerance())
		{
			m_src.shape = cs;
			m_src.iPos = m_src.iPos;
			m_dst->m_pos = cs->m_vertices[m_src.iPos];
			return true;
		}
		else
		{
			for (size_t i = 0, n = cs->m_vertices.size(); i < n; ++i)
			{
				if (i == m_src.iPos) continue;

				const float dis = f2Math::getDistance(pos, cs->m_vertices[i]);
				if (dis < getTolerance())
				{
					m_src.shape = cs;
					m_src.iPos = i;
					m_dst->m_pos = cs->m_vertices[i];
					return true;
				}
			}
			return false;
		}
	}
	else
	{
		for (size_t i = 0, n = cs->m_vertices.size(); i < n; ++i)
		{
			const float dis = f2Math::getDistance(pos, cs->m_vertices[i]);
			if (dis < getTolerance())
			{
				m_src.shape = cs;
				m_src.iPos = i;
				m_dst->m_pos = cs->m_vertices[i];
				return true;
			}
		}
		return false;
	}
}

//////////////////////////////////////////////////////////////////////////
// class NodeCaptureCmpt::UICtrls
//////////////////////////////////////////////////////////////////////////

std::queue<Event> NodeCaptureCmpt::UICtrls::m_eventList;

NodeCaptureCmpt::UICtrls::UICtrls()
{
	m_captureOpen = 1;
	m_tolerance = 5.0f;
}

void NodeCaptureCmpt::UICtrls::createUIControls(GLUI_Node* parent)
{
	if (dynamic_cast<GLUI*>(parent))
		largeLayoutUI(parent);
	else
		smallLayoutUI(parent);
}

void NodeCaptureCmpt::UICtrls::onEvent(Event event)
{
	switch (event.getID())
	{
	case e_SetState:
		setState();
		break;
	}
}

void NodeCaptureCmpt::UICtrls::smallLayoutUI(GLUI_Node* parent)
{
	GLUI_Panel* panel = new GLUI_Panel(parent, "", false);

	new GLUI_Checkbox(panel, "node capture", &m_captureOpen, e_SetState, callback);
	m_tolUI = new GLUI_Spinner(panel, "tolerance: ", &m_tolerance);
	m_tolUI->set_float_limits(1.0f, 10.0f);
}

void NodeCaptureCmpt::UICtrls::largeLayoutUI(GLUI_Node* parent)
{
	GLUI_Panel* panel = new GLUI_Panel(parent, "Node Capture");

	new GLUI_Checkbox(panel, "capture", &m_captureOpen, e_SetState, callback);

	m_tolUI = new GLUI_Spinner(panel, "tolerance: ", &m_tolerance);
	m_tolUI->set_float_limits(1.0f, 10.0f);
}

void NodeCaptureCmpt::UICtrls::setState()
{
	if (m_captureOpen == 0)
		m_tolUI->disable();
	else
		m_tolUI->enable();
}

void NodeCaptureCmpt::UICtrls::callback(int id)
{
	m_eventList.push(Event(id));
}