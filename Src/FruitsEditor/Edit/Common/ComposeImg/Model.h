#ifndef _FEDITOR_COMPOSE_IMG_MODEL_H_
#define _FEDITOR_COMPOSE_IMG_MODEL_H_
#include "Edit/AbstractModel.h"

namespace FEDITOR
{
	class AbstractBlackboard;
	class Sprite;

	namespace COMPOSE_IMG
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

			void saveLevel(const std::string& filename) const;
			void loadLevel(const std::string& filename);

		private:
			const Blackboard* m_blackboard;

			Sprite* m_bgSprite;

		}; // Model
	}
}

#endif // _FEDITOR_COMPOSE_IMG_MODEL_H_