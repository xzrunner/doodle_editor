#include "LayersMgr.h"
#include "Layer.h"

using namespace FEDITOR;

LayersMgr::~LayersMgr()
{
	clearLayers();
}

void LayersMgr::addLayer(Layer* layer)
{
	m_layers.push_back(layer);
}

void LayersMgr::addMidLayer(Layer* layer)
{
	assert(layer->getType() == Layer::e_middle);
	if (!m_layers.empty() && m_layers.back()->getType() == Layer::e_uppermost)
		m_layers.insert(m_layers.begin() + (m_layers.size() - 1), layer);
	else
		m_layers.push_back(layer);
}

Layer* LayersMgr::getLayer(int type) const
{
	for (size_t i = 0, n = m_layers.size(); i < n; ++i)
	{
		Layer* layer = m_layers[i];
		if (layer->getType() == type)
			return layer;
	}
	return NULL;
}

void LayersMgr::clearLayers(bool reclaimMemory/* = true*/)
{
	if (reclaimMemory) 
		for_each(m_layers.begin(), m_layers.end(), DeletePointerFunctor<Layer>());
	m_layers.clear();
}

void LayersMgr::deleteLayer(int index)
{
	delete m_layers[index];
	m_layers.erase(m_layers.begin() + index);
}

void LayersMgr::changeLayerLevel(int index, bool isUp)
{
	Layer* layer = m_layers[index];
	if (isUp)
	{
		m_layers.erase(m_layers.begin() + index);
		m_layers.insert(m_layers.begin() + index + 1, layer);
	}
	else
	{
		m_layers.erase(m_layers.begin() + index);
		m_layers.insert(m_layers.begin() + index - 1, layer);
	}
}

void LayersMgr::updateEachFrame()
{
	for (size_t i = 0, n = m_layers.size(); i < n; ++i)
		m_layers[i]->updateEachFrame();
}