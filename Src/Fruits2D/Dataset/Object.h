#ifndef _F2D_OBJECT_H_
#define _F2D_OBJECT_H_

namespace F2D
{
	class Object
	{
	public:
		Object();
		virtual ~Object();

		int getReferenceCount() const;

		void retain();
		void release();

	private:
		int m_count;

	}; // Object
}

#endif // _F2D_OBJECT_H_