#ifndef _FEDITOR_SIMULATE_CLOTH_MODEL_H_
#define _FEDITOR_SIMULATE_CLOTH_MODEL_H_
#include "Edit/AbstractModel.h"
#include "RegularGrids.h"

class b2World;
class b2Body;
class b2Joint;

namespace FEDITOR
{
	class AbstractBlackboard;
	class Texture;
	class Sprite;

	namespace SIMULATE_CLOTH
	{
		class Triangle;
		class Blackboard;

		class Model : public AbstractModel
		{
		public:
			Model(const AbstractBlackboard* blackboard, b2World* world);
			virtual ~Model();

			virtual void handleEvent(const Event& event);

			b2Body* getGround() const;

		private:
			void stepUpdate();

			void clearGridsPhyData();

			void resetJointsFrequency();
			void resetJointsDamping();
			void resetNodesEdge();

		private:
			const Blackboard* m_blackboard;
			b2World* m_world;

			RegularGrids m_regularGrids;

			Sprite* m_bgSprite;
			Texture* m_bgTexture;

			Sprite* m_deformationSprite;

			b2Body* m_ground;

			std::vector<b2Body*> m_bodies;
			std::vector<b2Joint*> m_joints;

			std::vector<Triangle*> m_tris;

			friend class RegularGrids;

		}; // Model

		inline b2Body* Model::getGround() const
		{
			return m_ground;
		}
	}
}

#endif // _FEDITOR_SIMULATE_CLOTH_MODEL_H_