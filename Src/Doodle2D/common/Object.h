#ifndef _D2D_OBJECT_H_
#define _D2D_OBJECT_H_

namespace d2d
{
	class Object
	{
	public:
		Object() {
			m_count = 1;
		}
		virtual ~Object() {}

		int getReferenceCount() const {
			return m_count;
		}

		void retain() {
			++m_count;
		}
		void release() {
			if (--m_count <= 0)
				delete this;
		}

	private:
		int m_count;

	}; // Object
}

#endif // _D2D_OBJECT_H_