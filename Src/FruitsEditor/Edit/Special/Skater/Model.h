#ifndef _FEDITOR_SKATER_MODEL_H_
#define _FEDITOR_SKATER_MODEL_H_
#include "Edit/AbstractModel.h"
#include "BoundsContainer.h"

namespace FEDITOR
{
	class Sprite;
	class Layer;
	class AbstractBlackboard;
	class LayersMgrCmpt;

	namespace SKATER
	{
		class Blackboard;

		class Model : public AbstractModel
		{
		public:
			Model(const AbstractBlackboard* blackboard);
			virtual ~Model();

			virtual void handleEvent(const Event& event);

			void setLayersMgrCmpt(LayersMgrCmpt* layersMgr);

			const BoundsContainer& getBoundsContainer() const;

			Sprite* getTrackSprite() const;
			Layer* getTrackLayer() const;

		private:
			void initLayers();

			void saveLevel(const std::string& filename) const;
			void loadLevel(const std::string& filename);

			void fixOldVersionData(const std::string& filename) const;

			void setSelectionTexCoords();

			void resetSpriteTexRegions(Sprite* sprite);

			void addSpritesBound(const std::string& filename);

			void saveTrackToFile();


		private:
			static const int BG_GRID_WIDTH = 100;

		private:
			const Blackboard* m_blackboard;

			LayersMgrCmpt* m_layersMgr;
			BoundsContainer m_bounds;

			Sprite* m_bgSprite;

			Layer* m_trackLayer;
			Sprite* m_trackSprite;

		}; // Model

		inline Sprite* Model::getTrackSprite() const
		{
			return m_trackSprite;
		}

		inline Layer* Model::getTrackLayer() const
		{
			return m_trackLayer;
		}
	}
}

#endif // _FEDITOR_SKATER_MODEL_H_