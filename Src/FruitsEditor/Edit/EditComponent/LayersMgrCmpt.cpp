#include "LayersMgrCmpt.h"
#include "CmptTypeID.h"
#include "../../Dataset/Layer.h"
#include "../AbstractBlackboard.h"
#include "glui/glui.h"

using namespace FEDITOR;

LayersMgrCmpt::LayersMgrCmpt(LayersMgr& layers, CmptMgr& cmptMgr, AbstractBlackboard* bb)
	: AbstractCmpt(e_LayersMgrCmpt, cmptMgr)
{
	m_bb = bb;

	m_content = new Content(layers);
	m_uiCtrls = new UICtrls;
	m_uiCtrls->setEditedIndex(m_content->getTotSize(), m_content->getUppermostEditableLayerIndex());
}

LayersMgrCmpt::~LayersMgrCmpt()
{
	delete m_content;
	delete m_uiCtrls;
}

void LayersMgrCmpt::createUIControls(GLUI_Node* parent, ShortcutKeyListener* shortcutLsn)
{
	m_uiCtrls->setParent(parent);
	createUICtrls(false, m_content->getUppermostEditableLayerIndex());
	setLayersDrawAABB();
}

void LayersMgrCmpt::handleUIEvent()
{
	while (!m_uiCtrls->m_eventList.empty())
	{
		Event event = m_uiCtrls->m_eventList.front(); m_uiCtrls->m_eventList.pop();
		switch (event.getID())
		{
		case UICtrls::e_AddLayer:
			addLayer();
			break;
		case UICtrls::e_DelLayer:
			delLayer();
			break;

		case UICtrls::e_SetLayerEditable:
			setLayersDrawAABB();
			if (m_bb) m_bb->pushEvent(Event(e_ChangeEditableLayer));
			break;
		case UICtrls::e_SetLayerVisible:
			m_content->setLayersVisible();
			break;

		case UICtrls::e_UpLayer:
			changeLayerLevel(true);
			break;
		case UICtrls::e_DownLayer:
			changeLayerLevel(false);
			break;

		case UICtrls::e_SetDrawAABB:
			setLayersDrawAABB();
			break;
		case UICtrls::e_SetDrawShape:
			setLayersDrawShape();
			break;
		}
	}
}

Layer* LayersMgrCmpt::getCertainTypeLayer(Type type) const
{
	return m_content->getCertainTypeLayer(type, getEditedIndex());
}

void LayersMgrCmpt::addLayer(Layer* layer)
{
	const bool reset = m_content->addLayer(layer);
	if (reset) createUICtrls(true, m_content->getUppermostEditableLayerIndex());
}

void LayersMgrCmpt::reloadLayers()
{
	m_content->reloadLayers();
	createUICtrls(true, m_content->getUppermostEditableLayerIndex());
	setLayersDrawAABB();
}

void LayersMgrCmpt::pushEvent(Event event)
{
	m_uiCtrls->m_eventList.push(event);
}

void LayersMgrCmpt::createUICtrls(bool onlyLayers, size_t editedLayerIndex)
{
	m_uiCtrls->setEditedIndex(m_content->getTotSize(), editedLayerIndex);
	if (onlyLayers)
		m_uiCtrls->createLayersUICtrls();
	else
		m_uiCtrls->createUICtrls();
	m_uiCtrls->initLayers(m_content->getWrappers());
}

void LayersMgrCmpt::addLayer()
{
	const bool reset = m_content->addLayer(new Layer(Layer::e_middle));
	if (reset) createUICtrls(true, m_content->getUppermostEditableLayerIndex());
	setLayersDrawAABB();
}

void LayersMgrCmpt::delLayer()
{
	const bool reset = m_content->deleteLayer(getEditedIndex());
	if (reset) createUICtrls(true, m_content->getUppermostEditableLayerIndex());
	setLayersDrawAABB();
}

void LayersMgrCmpt::changeLayerLevel(bool isUp)
{
	const int editedLayerIndex = getEditedIndex();
	const bool reset = m_content->changeLayerLevel(editedLayerIndex, isUp);
	if (reset) 
	{
		if (isUp) createUICtrls(true, editedLayerIndex + 1);
		else createUICtrls(true, editedLayerIndex - 1);
	}
}

int LayersMgrCmpt::getEditedIndex() const
{
	return m_uiCtrls->getEditedIndex(m_content->getTotSize());
}

void LayersMgrCmpt::setLayersDrawAABB()
{
	m_content->setlayersEditable(getEditedIndex(), m_uiCtrls->isDrawAABB(), m_uiCtrls->isDrawShape());
}

void LayersMgrCmpt::setLayersDrawShape()
{
	m_content->setlayersEditable(getEditedIndex(), m_uiCtrls->isDrawAABB(), m_uiCtrls->isDrawShape());
}

//////////////////////////////////////////////////////////////////////////
// class LayersMgrCmpt::Wrapper
//////////////////////////////////////////////////////////////////////////

LayersMgrCmpt::Wrapper::Wrapper()
{
	layer = NULL;
	visible = 1;
	disable = false;
}

//////////////////////////////////////////////////////////////////////////
// class LayersMgrCmpt::Content
//////////////////////////////////////////////////////////////////////////

LayersMgrCmpt::Content::Content(LayersMgr& layersMgr)
	: m_layersMgr(layersMgr)
{
	reloadLayersFromMgr();
}

bool LayersMgrCmpt::Content::addLayer(Layer* layer)
{
	addLayerToMgr(layer);
	addLayerToWrappers(layer);
	return true;
}

bool LayersMgrCmpt::Content::deleteLayer(int index)
{
	if (m_wrapper.size() <= 3 || 
		m_wrapper[index]->layer->getType() != Layer::e_middle)
		return false;

	m_layersMgr.deleteLayer(index);
	delete m_wrapper[index];
	m_wrapper.erase(m_wrapper.begin() + index);
	return true;
}

bool LayersMgrCmpt::Content::changeLayerLevel(int index, bool isUp)
{
	if (m_wrapper.size() < 2) return false;

	Wrapper* wrapper = m_wrapper[index];
	if (wrapper->layer->getType() != Layer::e_middle) return false;

	if (isUp)
	{
		if (index == m_wrapper.size() - 1 ||
			index == m_wrapper.size() - 2 && m_wrapper.back()->layer->getType() == Layer::e_uppermost)
			return false;

		m_wrapper.erase(m_wrapper.begin() + index);
		m_wrapper.insert(m_wrapper.begin() + index + 1, wrapper);
		m_layersMgr.changeLayerLevel(index, isUp);
		return true;
	}
	else
	{
		if (index == 0 ||
			index == 1 && m_wrapper.front()->layer->getType() == Layer::e_lowermost)
			return false;

		m_wrapper.erase(m_wrapper.begin() + index);
		m_wrapper.insert(m_wrapper.begin() + index - 1, wrapper);
		m_layersMgr.changeLayerLevel(index, isUp);
		return true;
	}
}

Layer* LayersMgrCmpt::Content::getCertainTypeLayer(LayersMgrCmpt::Type type, int editedIndex) const
{
	const std::vector<Layer*>& layers = m_layersMgr.getAllLayers();
	switch (type)
	{
	case LayersMgrCmpt::e_BackgroundLayer:
		for (size_t i = 0, n = layers.size(); i < n; ++i)
		{
			Layer* layer = layers[i];
			if (layer->getType() == Layer::e_lowermost)
				return layer;
		}
		break;
	case LayersMgrCmpt::e_TempLayer:
		for (size_t i = 0, n = layers.size(); i < n; ++i)
		{
			Layer* layer = layers[i];
			if (layer->getType() == Layer::e_uppermost)
				return layer;
		}
		break;
	case LayersMgrCmpt::e_EditedLayer:
		assert(editedIndex < layers.size());
		return layers[editedIndex];
	default:
		return NULL;
	}
	return NULL;
}

int LayersMgrCmpt::Content::getUppermostEditableLayerIndex() const
{
	const std::vector<Layer*>& layers = m_layersMgr.getAllLayers();
	for (int i = layers.size() - 1; i >= 0; --i)
	{
		Layer* layer = layers[i];
		if (layer->getType() == Layer::e_middle)
			return i;
	}
	return -1;
}

void LayersMgrCmpt::Content::setLayersVisible()
{
	const std::vector<Layer*>& original = m_layersMgr.getAllLayers();
	assert(original.size() == m_wrapper.size());
	for (size_t i = 0, n = original.size(); i < n; ++i)
	{
		Layer* layer = original[i];
		layer->setVisible(m_wrapper[i]->visible == 1);
	}
}

void LayersMgrCmpt::Content::setlayersEditable(int editedIndex, bool isDrawAABB, bool isDrawShape)
{
	const std::vector<Layer*>& original = m_layersMgr.getAllLayers();
	assert(original.size() == m_wrapper.size());
	for (size_t i = 0, n = original.size(); i < n; ++i)
	{
		Layer* layer = original[i];

		layer->m_style.m_bDrawAABB = isDrawAABB && (i == editedIndex);

		if (layer->getType() == Layer::e_middle)
			layer->m_style.m_bDrawShape = isDrawShape;
		else
			layer->m_style.m_bDrawShape = true;
	}
}

void LayersMgrCmpt::Content::reloadLayers()
{
	reloadLayersFromMgr();
}

void LayersMgrCmpt::Content::reloadLayersFromMgr()
{
	for_each(m_wrapper.begin(), m_wrapper.end(), DeletePointerFunctor<Wrapper>());
	m_wrapper.clear();

	m_count = 0;

	const std::vector<Layer*>& layers = m_layersMgr.getAllLayers();
	for (size_t i = 0, n = layers.size(); i < n; ++i)
		addLayerToWrappers(layers[i]);
}

void LayersMgrCmpt::Content::addLayerToMgr(Layer* layer)
{
	m_layersMgr.addMidLayer(layer);
}

void LayersMgrCmpt::Content::addLayerToWrappers(Layer* layer)
{
	LayersMgrCmpt::Wrapper* wrapper = new LayersMgrCmpt::Wrapper;

	wrapper->layer = layer;
	Layer::Type type = layer->getType();
	if (layer->getName() != "")
		wrapper->name = layer->getName();
	else if (type == Layer::e_lowermost)
		wrapper->name = "bg_layer";
	else if (type == Layer::e_uppermost)
		wrapper->name = "temp_layer";
	else
		wrapper->name = "layer_" + StringTools::intToString(m_count++);
//	wrapper->disable = type != Layer::e_middle;
	wrapper->disable = (type != Layer::e_middle && type != Layer::e_lowermost);
	layer->setName(wrapper->name);

	if (!m_wrapper.empty() && m_wrapper.back()->layer->getType() == Layer::e_uppermost)
		m_wrapper.insert(m_wrapper.begin() + m_wrapper.size() - 1, wrapper);
	else
		m_wrapper.push_back(wrapper);
}

//////////////////////////////////////////////////////////////////////////
// class LayersMgrCmpt::UICtrls
//////////////////////////////////////////////////////////////////////////

std::queue<Event> LayersMgrCmpt::UICtrls::m_eventList;

LayersMgrCmpt::UICtrls::UICtrls()
{
	m_layersPanelWrapper = m_layersPanel = NULL;
 	m_isDrawAABB = 1;
	m_isDrawShape = 1;
}

void LayersMgrCmpt::UICtrls::setParent(GLUI_Node* parent)
{
	m_parent = parent;
}

void LayersMgrCmpt::UICtrls::createUICtrls()
{
	if (dynamic_cast<GLUI*>(m_parent))
		largeLayoutUI();
	else
		smallLayoutUI();
}

void LayersMgrCmpt::UICtrls::createLayersUICtrls()
{
	m_layersPanel->unlink();
	delete m_layersPanel;

	initLayersUICtrls();
}

void LayersMgrCmpt::UICtrls::initLayers(const std::vector<LayersMgrCmpt::Wrapper*>& wrappers)
{
	for (int i = wrappers.size() - 1; i >= 0; --i)
	{
		LayersMgrCmpt::Wrapper* wrapper = wrappers[i];

		GLUI_StaticText* text = new GLUI_StaticText(m_nameList, wrapper->name.c_str());
		text->set_w(BTN_WIDTH);
		GLUI_RadioButton* editable = new GLUI_RadioButton(m_editableList, "");
		GLUI_Checkbox* visible = new GLUI_Checkbox(m_visibleList, "", &wrapper->visible, e_SetLayerVisible, callback);
		if (wrapper->disable)
		{
			editable->disable();
			visible->disable();
		}
	}
}

void LayersMgrCmpt::UICtrls::callback(int id)
{
	m_eventList.push(Event(id));
}

void LayersMgrCmpt::UICtrls::initLayersUICtrls()
{
	m_layersPanel = new GLUI_Panel(m_layersPanelWrapper, "", false);

	m_nameList = new GLUI_Panel(m_layersPanel, "Name");
	m_nameList->set_w(BTN_WIDTH);

	new GLUI_Column(m_layersPanel, false);
	GLUI_Panel* tmpPanel = new GLUI_Panel(m_layersPanel, "Edit");
	m_editableList = new GLUI_RadioGroup(tmpPanel, &m_editedIndex, e_SetLayerEditable, callback);

	new GLUI_Column(m_layersPanel, false);
	m_visibleList = new GLUI_Panel(m_layersPanel, "See", true);
}

void LayersMgrCmpt::UICtrls::smallLayoutUI()
{
	commonLayoutUI(m_parent);
}

void LayersMgrCmpt::UICtrls::largeLayoutUI()
{
	GLUI_Rollout* root = new GLUI_Rollout(m_parent, "Layers", true);
	commonLayoutUI(root);
}

void LayersMgrCmpt::UICtrls::commonLayoutUI(GLUI_Node* parent)
{
	GLUI_Panel* addDelPanel = new GLUI_Panel(parent, "", true);
	GLUI_Button* add = new GLUI_Button(addDelPanel, "Add", e_AddLayer, callback);
	add->set_w(BTN_WIDTH * 8);
	new GLUI_Column(addDelPanel, false);
	GLUI_Button* del = new GLUI_Button(addDelPanel, "Del", e_DelLayer, callback);
	del->set_w(BTN_WIDTH * 8);

	m_layersPanelWrapper = new GLUI_Panel(parent, "", false);
	initLayersUICtrls();

	GLUI_Panel* upDownPanel = new GLUI_Panel(parent, "", true);
	GLUI_Button* up = new GLUI_Button(upDownPanel, "Up", e_UpLayer, callback);
	up->set_w(BTN_WIDTH * 8);
	new GLUI_Column(upDownPanel, false);
	GLUI_Button* down = new GLUI_Button(upDownPanel, "Down", e_DownLayer, callback);
	down->set_w(BTN_WIDTH * 8);

	GLUI_Panel* settingPanel = new GLUI_Panel(parent, "Setting", true);
	new GLUI_Checkbox(settingPanel, "Draw AABB", &m_isDrawAABB, e_SetDrawAABB, callback);
	new GLUI_Checkbox(settingPanel, "Draw Shape", &m_isDrawShape, e_SetDrawShape, callback);
}