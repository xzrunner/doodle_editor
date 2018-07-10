#ifndef _WX_GUI_DRAG_PHYSICS_OP_H_
#define _WX_GUI_DRAG_PHYSICS_OP_H_

#include "ZoomViewOP.h"

#include <Box2D/Box2D.h>

namespace wxgui
{
	class DragPhysicsOP : public ZoomViewOP
	{
	public:
		DragPhysicsOP(EditPanel* editPanel, b2World* world, b2Body* ground);

		virtual bool onMouseLeftDown(int x, int y);
		virtual bool onMouseLeftUp(int x, int y);
		virtual bool onMouseDrag(int x, int y);

	private:
		b2World* m_world;
		b2Body* m_ground;

		b2MouseJoint* m_mouseJoint;

	}; // DragPhysicsOP
}

#endif // _WX_GUI_DRAG_PHYSICS_OP_H_