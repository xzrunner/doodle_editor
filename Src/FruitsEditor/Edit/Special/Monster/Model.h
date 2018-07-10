#ifndef _FEDITOR_MONSTER_MODEL_H_
#define _FEDITOR_MONSTER_MODEL_H_
#include "Edit/AbstractModel.h"

namespace FEDITOR
{
	class Sprite;
	class Layer;
	class AbstractBlackboard;

	namespace MONSTER
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

			void reloadBgSprite();
			void reloadTileSprites();

			void saveLevel(const std::string& filename) const;
			void loadLevel(const std::string& filename);

		private:
			Blackboard* m_blackboard;

			Sprite* m_bgSprite;

		}; // Model
	}
}

#endif // _FEDITOR_MONSTER_MODEL_H_