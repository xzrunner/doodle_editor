#ifndef _FEDITOR_FILL_COLOR_MODEL_H_
#define _FEDITOR_FILL_COLOR_MODEL_H_
#include "Edit/AbstractModel.h"

namespace FEDITOR
{
	class AbstractBlackboard;
	class Shape;
	class ChainShape;
	class TriangleShape;
	class Sprite;
	class Layer;

	namespace FILL_COLOR
	{
		class Blackboard;

		class Model : public AbstractModel
		{
		public:
			Model(const AbstractBlackboard* blackboard);
			virtual ~Model();

			virtual void handleEvent(const Event& event);

		private:
			void initLayers();

			void triangulationSelections();
			void triangulationSprite(Sprite* sprite);
			void triangulationShape(Sprite* sprite, ChainShape* chain);

			void storeTriShapesToFile(const std::string& filename) const;
			void getValidLayers(std::vector<Layer*>& layers) const;
			void getTriShapes(const Layer* layer, std::vector<TriangleShape*>& tris) const;

			void loadTriShapesFromFile(const std::string& filename);

			void tileSelectionRegionByImg(const std::string& filename);
			void tileLoopByImg(const std::string& filename, Layer* layer, ChainShape* cs);

			void storeFillImgToFile(const std::string& filename) const;
			void loadFillImgFromFile(const std::string& filename);

		private:
			const Blackboard* m_blackboard;

			Sprite* m_chainsSprite;

			std::map<ChainShape*, std::string> m_regions;

		}; // Model
	}
}

#endif // _FEDITOR_FILL_COLOR_MODEL_H_