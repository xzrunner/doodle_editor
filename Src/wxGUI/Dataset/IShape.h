#ifndef _WX_GUI_INTERFACE_SHAPE_H_
#define _WX_GUI_INTERFACE_SHAPE_H_

#include <Fruits2D/Fruits2D.h>

namespace wxgui
{
	class IShape : public f2Shape, public ISerializable
	{
	public:

		//
		// IObject interface
		//
		virtual IShape* clone() { return NULL; }

		virtual const f2AABB& getAABB() const = 0;

		virtual void draw(const f2Colorf& color = f2Colorf(0, 0, 0)) const = 0;

	}; // IShape
}

#endif // _WX_GUI_INTERFACE_SHAPE_H_