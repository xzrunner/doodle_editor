#ifndef _F2D_SHAPE_H_
#define _F2D_SHAPE_H_

namespace F2D
{
	class f2Shape : public IObject, public UserDataImpl, public Object
	{
	public:

		virtual ~f2Shape() { clearUserData(true); }

		//
		// UserDataImpl interface
		//	
		virtual void clearUserData(bool deletePtr) {}

		virtual bool isContain(const f2Vec2& pos) = 0;
		virtual bool isIntersect(const f2AABB& aabb) = 0;

	protected:
		static const int QUERY_ACCURACY = 5;

	}; // f2Shape
}

#endif // _F2D_SHAPE_H_