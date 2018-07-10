#ifndef _F2D_USER_DATA_H_
#define _F2D_USER_DATA_H_

namespace F2D
{
	class UserDataImpl
	{
	public:
		UserDataImpl();
		virtual ~UserDataImpl();

		virtual void clearUserData(bool deletePtr) = 0;

		void setUserData(void* data);
		void* getUserData() const;

	protected:
		void* m_userData;

	}; // UserDataImpl
}

#endif // _F2D_USER_DATA_H_