#ifndef _FEDITOR_LAYERS_MGR_H_
#define _FEDITOR_LAYERS_MGR_H_
#include <Fruits2D/Fruits2D.h>
#include "SelectionSet.h"

namespace FEDITOR
{
	class Layer;

	class LayersMgr
	{
	public:
		~LayersMgr();
		
		void addLayer(Layer* layer);
		void addMidLayer(Layer* layer);
		Layer* getLayer(int type) const;
		void clearLayers(bool reclaimMemory = true);
		void deleteLayer(int index);
		void changeLayerLevel(int index, bool isUp);

		const std::vector<Layer*>& getAllLayers() const;
		SelectionSet& getSelection();
		const SelectionSet& getSelectionConst() const;

		void updateEachFrame();

	private:
		std::vector<Layer*> m_layers;

		SelectionSet m_selection;

	}; // LayersMgr

	inline const std::vector<Layer*>& LayersMgr::getAllLayers() const
	{
		return m_layers;
	}

	inline SelectionSet& LayersMgr::getSelection()
	{
		return m_selection;
	}

	inline const SelectionSet& LayersMgr::getSelectionConst() const
	{
		return m_selection;
	}
}

#endif // _FEDITOR_LAYERS_MGR_H_