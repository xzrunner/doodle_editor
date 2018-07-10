#ifndef _D2D_EXCEPTION_H_
#define _D2D_EXCEPTION_H_

#include <exception>
#include <string>

namespace d2d
{
	class Exception : public std::exception
	{
	public:
		Exception(const char* fmt, ...);
		virtual ~Exception() throw() {}

		inline virtual const char* what() const throw() { 
			return m_message.c_str(); 
		}

	private:
		std::string m_message;

	}; // Exception 
}

#endif // _D2D_EXCEPTION_H_