#ifndef _D2D_LOG_H_
#define _D2D_LOG_H_

#include "config.h"

namespace d2d
{
	class Log
	{
	public:
		static void error(const char* pMessage, ...);
		static void warn(const char* pMessage, ...);
		static void info(const char* pMessage, ...);
		static void debug(const char* pMessage, ...);

	}; // Log
}

#ifndef NDEBUG
	#define DB_Log_debug(...) d2d::Log::debug(__VA_ARGS__)
#else
	#define DB_Log_debug(...)
#endif

#endif // _D2D_LOG_H_