#ifndef _FEDITOR_SOFT_RENDER_MODEL_H_
#define _FEDITOR_SOFT_RENDER_MODEL_H_
#include "FruitsEditor/Edit/AbstractModel.h"

namespace FEDITOR
{
	class Sprite;
	class AbstractBlackboard;

	namespace SOFT_RENDER
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

		private:
			const Blackboard* m_blackboard;

			Sprite* m_bgSprite;

		}; // Model
	}
}

#endif // _FEDITOR_SOFT_RENDER_MODEL_H_