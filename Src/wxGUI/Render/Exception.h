#ifndef _WX_GUI_EXCEPTION_H_
#define _WX_GUI_EXCEPTION_H_

#include <exception>
#include <string>

namespace wxgui
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

#endif // _WX_GUI_EXCEPTION_H_