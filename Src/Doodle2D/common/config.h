#ifndef _D2D_CONFIG_H_
#define _D2D_CONFIG_H_

// Platform stuff.
#if defined(WIN32) || defined(_WIN32)
#	define D2D_WINDOWS 1
#elif defined(linux) || defined(__linux) || defined(__linux__)
	#define D2D_ANDROID_NATIVE
//	#define D2D_ANDROID_JNI
#endif

// #ifndef D2D_FAST_MATH
// #define D2D_FAST_MATH 1
// #endif

#ifdef D2D_WINDOWS
	#define NOMINMAX
#endif

#define D2D_FRAME_RATE

#endif // _D2D_CONFIG_H_