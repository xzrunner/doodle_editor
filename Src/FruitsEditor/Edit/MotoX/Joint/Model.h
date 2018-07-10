#ifndef _FEDITOR_MOTOX_JOINT_MODEL_H_
#define _FEDITOR_MOTOX_JOINT_MODEL_H_
#include "../../AbstractModel.h"
#include "Parts.h"
#include "Joints.h"

class b2World;

namespace FEDITOR
{
	class AbstractBlackboard;
	class Layer;
	class PointShape;
	class Body;
	class Sprite;
	class Joint;

	namespace MOTOX
	{
		namespace JOINT
		{
			class Blackboard;
  
			class Model : public AbstractModel
			{
			public:
				Model(const AbstractBlackboard* blackboard, b2World* world);
				virtual ~Model();

				virtual void handleEvent(const Event& event);

				Layer* getEditedLayer();

				PointShape* getJointPos();

				Parts& getParts();
				Joints& getJoints();

				Body* getGround();

			private:
				void initLayers(b2World* world);

				void initBackgroundLayer(b2World* world);
				void initEditedLayer();
				void initTempLayer();

				void loadFromFile(const std::string& filename);
				void storeToFile(const std::string& filename) const;
				void storeToFileOnlyJoints(const std::string& filename) const;

			private:
				const Blackboard* m_blackboard;

				Layer* m_layer;

				Sprite* m_bgSprite;

				Parts m_parts;
				Joints m_joints;

				PointShape* m_jointPos;

			}; // Model

			inline Layer* Model::getEditedLayer()
			{
				return m_layer;
			}

			inline PointShape* Model::getJointPos()
			{
				return m_jointPos;
			}

			inline Parts& Model::getParts()
			{
				return m_parts;
			}

			inline Joints& Model::getJoints()
			{
				return m_joints;
			}
		}
	}
}

#endif // _FEDITOR_MOTOX_JOINT_MODEL_H_