#include "Log.h"
#include "tools.h"

#include <stdarg.h>

#ifdef D2D_WINDOWS
#	include <iostream>
#else
#	include <android/log.h>
#endif

using namespace d2d;

void Log::error(const char* pMessage, ...)
{
#ifdef D2D_WINDOWS
	va_list args;
	int size_buffer = 256, size_out;
	char* buffer;
	while (true)
	{
		buffer = new char[size_buffer];
		memset(buffer, 0, size_buffer);

		va_start(args, pMessage);
		size_out = vsnprintf(buffer, size_buffer, pMessage, args);
		va_end(args);

		if (size_out == size_buffer || size_out == -1 || size_out == size_buffer-1)
			size_buffer *= 2;
		else if (size_out > size_buffer)
			size_buffer = size_out + 2; // to avoid the ambiguous case
		else
			break;

		delete[] buffer;
	}
	std::cout << buffer << std::endl;
	delete[] buffer;
#else
	va_list lVarArgs;
	va_start(lVarArgs, pMessage);
	__android_log_vprint(ANDROID_LOG_ERROR, "d2d", pMessage, lVarArgs);
	__android_log_print(ANDROID_LOG_ERROR, "d2d", "\n");
	va_end(lVarArgs);
#endif
}

void Log::warn(const char* pMessage, ...)
{
#ifdef D2D_WINDOWS
	va_list args;
	int size_buffer = 256, size_out;
	char* buffer;
	while (true)
	{
		buffer = new char[size_buffer];
		memset(buffer, 0, size_buffer);

		va_start(args, pMessage);
		size_out = vsnprintf(buffer, size_buffer, pMessage, args);
		va_end(args);

		if (size_out == size_buffer || size_out == -1 || size_out == size_buffer-1)
			size_buffer *= 2;
		else if (size_out > size_buffer)
			size_buffer = size_out + 2; // to avoid the ambiguous case
		else
			break;

		delete[] buffer;
	}
	std::cout << buffer << std::endl;
	delete[] buffer;
#else
	va_list lVarArgs;
	va_start(lVarArgs, pMessage);
	__android_log_vprint(ANDROID_LOG_WARN, "d2d", pMessage, lVarArgs);
	__android_log_print(ANDROID_LOG_WARN, "d2d", "\n");
	va_end(lVarArgs);
#endif
}

void Log::info(const char* pMessage, ...)
{
#ifdef D2D_WINDOWS
	va_list args;
	int size_buffer = 256, size_out;
	char* buffer;
	while (true)
	{
		buffer = new char[size_buffer];
		memset(buffer, 0, size_buffer);

		va_start(args, pMessage);
		size_out = vsnprintf(buffer, size_buffer, pMessage, args);
		va_end(args);

		if (size_out == size_buffer || size_out == -1 || size_out == size_buffer-1)
			size_buffer *= 2;
		else if (size_out > size_buffer)
			size_buffer = size_out + 2; // to avoid the ambiguous case
		else
			break;

		delete[] buffer;
	}
	std::cout << buffer << std::endl;
	delete[] buffer;
#else
	va_list lVarArgs;
	va_start(lVarArgs, pMessage);
	__android_log_vprint(ANDROID_LOG_INFO, "d2d", pMessage, lVarArgs);
	__android_log_print(ANDROID_LOG_INFO, "d2d", "\n");
	va_end(lVarArgs);
#endif
}

void Log::debug(const char* pMessage, ...)
{
#ifdef D2D_WINDOWS
	va_list args;
	int size_buffer = 256, size_out;
	char* buffer;
	while (true)
	{
		buffer = new char[size_buffer];
		memset(buffer, 0, size_buffer);

		va_start(args, pMessage);
		size_out = vsnprintf(buffer, size_buffer, pMessage, args);
		va_end(args);

		if (size_out == size_buffer || size_out == -1 || size_out == size_buffer-1)
			size_buffer *= 2;
		else if (size_out > size_buffer)
			size_buffer = size_out + 2; // to avoid the ambiguous case
		else
			break;

		delete[] buffer;
	}
	std::cout << buffer << std::endl;
	delete[] buffer;
#else
	va_list lVarArgs;
	va_start(lVarArgs, pMessage);
	__android_log_vprint(ANDROID_LOG_DEBUG, "d2d", pMessage, lVarArgs);
	__android_log_print(ANDROID_LOG_DEBUG, "d2d", "\n");
	va_end(lVarArgs);
#endif
}