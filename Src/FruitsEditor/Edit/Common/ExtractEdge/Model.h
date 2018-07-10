#ifndef _FEDITOR_EXTRACT_EDGE_MODEL_H_
#define _FEDITOR_EXTRACT_EDGE_MODEL_H_
#include <Fruits2D/Fruits2D.h>
#include "Edit/AbstractModel.h"

//////////////////////////////////////////////////////////////////////////
// Text File Format:
// 1 background texture file name
// 2 coordinate type
// 3 chain shape size
// 3.1 each chain shape
//////////////////////////////////////////////////////////////////////////

namespace FEDITOR
{
	class Texture;
	class Layer;
	class AbstractBlackboard;
	class Sprite;
	class ChainShape;

	namespace EXTRACT_EDGE
	{
		class Blackboard;
		class SameColorRegionSelect;

		class Model : public AbstractModel
		{
		public:
			Model(const AbstractBlackboard* blackboard);
			virtual ~Model();

			virtual void handleEvent(const Event& event);

			SameColorRegionSelect* getAutoSelect();

			void refreshAutoSelectLayer();

			f2Vec2 getCoordsInCurrentType(const f2Vec2& pos) const;

			Sprite* getEditedSprite() const;
			Layer* getEditedLayer() const;

		private:
			void initLayers();

			void loadFromFile(const std::string& filename);
			void loadFromLoopsFile(const std::string& filename);
			void storeToTextFile() const;

			void loadBgLayer(const std::string& file);

			void buildCoordLinesLayer();
			void buildCoordLinesSprite();

			void setCoordLinesPosition();
			void setCoordLinesLayerVisible();

			void adjustShapeCoords(ChainShape* shape) const;
			void restoreShapeCoords(ChainShape* shape) const;

		private:
			const Blackboard* m_blackboard;

			Layer* m_dataLayer;
			Layer* m_autoLayer;
			Layer* m_coordLinesLayer;

			Sprite* m_bgSprite;
			Texture* m_bgTexture;

			Sprite* m_edgeSprite;

			SameColorRegionSelect* m_autoSelect;

			Sprite* m_coordLinesSprite;

		}; // Model

		inline SameColorRegionSelect* Model::getAutoSelect()
		{
			return m_autoSelect;
		}

		inline Sprite* Model::getEditedSprite() const
		{
			return m_edgeSprite;
		}

		inline Layer* Model::getEditedLayer() const
		{
			return m_dataLayer;
		}
	}
}

#endif // _FEDITOR_EXTRACT_EDGE_MODEL_H_