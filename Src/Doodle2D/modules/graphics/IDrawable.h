#ifndef _D2D_INTERFACE_DRAWABLE_H_
#define _D2D_INTERFACE_DRAWABLE_H_

namespace d2d
{
	class IDrawable
	{
	public:
		virtual status load() = 0;
		virtual void draw() const = 0;

	}; // IDrawable
}

#endif // _D2D_INTERFACE_DRAWABLE_H_