#ifndef _FEDITOR_ARRANGE_SPRITE_PHYS_OPERATION_H_
#define _FEDITOR_ARRANGE_SPRITE_PHYS_OPERATION_H_
#include "AbstractOp.h"

class b2World;
class b2Body;
class b2MouseJoint;

namespace FEDITOR
{
	class Layer;
//	class SelectSpritesOp;

	class ArrangeSpritePhysOp : public AbstractOp
	{
	public:

		enum QueryType
		{
			e_MouseOn,
			e_MouseNear
		};

		ArrangeSpritePhysOp(AbstractControl* task, b2World* world, b2Body* ground, int type = e_MouseOn);
//		ArrangeSpritePhysOp(AbstractControl* task, Layer* editable, b2World* world, b2Body* ground, int type = e_MouseOn);
		virtual ~ArrangeSpritePhysOp();

		virtual void onMouseLeftDown(int x, int y);
		virtual void onMouseLeftUp(int x, int y);
		virtual void onMouseDrag(int x, int y);

	private:
//		SelectSpritesOp* m_selectOp;

		b2World* m_world;
		b2Body* m_ground;

		int m_queryType;

		b2MouseJoint* m_mouseJoint;

	}; // PhysMouseDragOp
}

#endif // _FEDITOR_ARRANGE_SPRITE_PHYS_OPERATION_H_