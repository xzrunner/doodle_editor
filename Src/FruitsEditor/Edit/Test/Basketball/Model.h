#ifndef _FEDITOR_BASKETBALL_MODEL_H_
#define _FEDITOR_BASKETBALL_MODEL_H_
#include "../../AbstractModel.h"

class b2World;
class b2Body;
class b2Joint;

namespace FEDITOR
{
	class AbstractBlackboard;

	namespace BASKETBALL
	{
		class Blackboard;

		class Model : public AbstractModel
		{
		public:
			Model(const AbstractBlackboard* blackboard, b2World* world);
			virtual ~Model();

			virtual void handleEvent(const Event& event);

			b2Body* getGround() const;

		private:
			void initLayers();

			void initGround();
			void initBasketAndNet();

		private:
			const Blackboard* m_blackboard;
			b2World* m_world;

			b2Body* m_ground;

			std::vector<b2Body*> m_bodies;
			std::vector<b2Joint*> m_joints;

		}; // Model

		inline b2Body* Model::getGround() const
		{
			return m_ground;
		}
	}
}

#endif // _FEDITOR_BASKETBALL_MODEL_H_