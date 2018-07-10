#ifndef _FEDITOR_TEST_RENDERING_MODEL_H_
#define _FEDITOR_TEST_RENDERING_MODEL_H_
#include "Edit/AbstractModel.h"

namespace FEDITOR
{
	class AbstractBlackboard;
	class AbstractView;
	class Sprite;

	namespace TEST_RENDERING
	{
		class Blackboard;

		class Model : public AbstractModel
		{
		public:
			Model(const AbstractBlackboard* blackboard, AbstractView* view);
			virtual ~Model();

			virtual void handleEvent(const Event& event);

		private:
			void initData();
			void renderData();

		private:
			Blackboard* m_blackboard;
			AbstractView* m_view;

			std::string m_filename;
			std::vector<Sprite*> m_sprites;

		}; // Model
	}
}

#endif // _FEDITOR_TEST_RENDERING_MODEL_H_