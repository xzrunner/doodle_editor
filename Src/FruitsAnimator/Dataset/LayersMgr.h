#ifndef _FRUITS_ANIMATOR_LAYERS_MGR_H_
#define _FRUITS_ANIMATOR_LAYERS_MGR_H_

#include <Fruits2D/Fruits2D.h>

namespace FRUITS_ANIMATOR
{
	class Layer;
	class LibraryPanel;

	class LayersMgr
	{
	public:
		~LayersMgr();
 
		void loadFromTextFile(std::ifstream& fin, const LibraryPanel& library);
		void storeToTextFile(std::ofstream& fout, const LibraryPanel& library) const;

		void insertNewLayer();
		void deleteLayer(int index);
		void changeLayerOrder(int from, int to);

		size_t size() const;

		Layer* getLayer(size_t index) const;

		int getFrameCount() const;

		void clear();

		void removeSprite(f2Sprite* sprite);

	private:
		std::vector<Layer*> m_layers;

	}; // LayersMgr
}

#endif // _FRUITS_ANIMATOR_LAYERS_MGR_H_