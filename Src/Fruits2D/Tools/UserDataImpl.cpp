#include "UserDataImpl.h"

#include <stdlib.h>

using namespace F2D;

UserDataImpl::UserDataImpl() 
{ 
	m_userData = NULL; 
}

UserDataImpl::~UserDataImpl() 
{ 
//	clearUserData(true);
}

void UserDataImpl::setUserData(void* data) 
{ 
	if (m_userData != data)
	{
		clearUserData(true);
		m_userData = data;
	}
}

void* UserDataImpl::getUserData() const 
{
	return m_userData;
}
