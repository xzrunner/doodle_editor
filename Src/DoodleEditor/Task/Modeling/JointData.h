#ifndef _DEDITOR_MODELING_JOINT_DATA_H_
#define _DEDITOR_MODELING_JOINT_DATA_H_

#include <wxGUI/wxGUI.h>

namespace deditor
{
	namespace modeling
	{
		class BodyData;

		class JointData : public IObject
		{
		public:
			enum Type
			{
				e_revoluteJoint,
				e_prismaticJoint,
				e_distanceJoint,
				e_pulleyJoint,
				e_mouseJoint,
				e_gearJoint,
				e_wheelJoint,
				e_weldJoint,
				e_frictionJoint,
				e_ropeJoint
			};

			enum DrawType
			{
				e_default,
				e_mouseOn,
				e_selected
			};

		public:
			JointData(BodyData* b0, BodyData* b1, Type type);
			virtual ~JointData() {}
			
			virtual JointData* clone() { return NULL; }

			virtual bool isContain(const f2Vec2& pos) const = 0;

			virtual void draw(DrawType type) const = 0;

		protected:
			void drawBodyFlag() const;

			static f2Vec2 transWorldToLocal(const f2Vec2& world, 
				const wxgui::ISprite* sprite);
			static f2Vec2 transLocalToWorld(const f2Vec2& local, 
				const wxgui::ISprite* sprite);

		private:
			void drawBodyFlag(const f2Vec2& pos) const;

		protected:
			static const float JOINT_RADIUS_OUT;
			static const float JOINT_RADIUS_IN;
			static const float JOINT_RADIUS_SELECT;

		public:
			wxString m_name;

			Type type;

			BodyData* bodyA;
			BodyData* bodyB;

			bool collideConnected;

		}; // JointData
	}
}

#endif // _DEDITOR_MODELING_JOINT_DATA_H_