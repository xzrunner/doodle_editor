#ifndef _D2D_RESOURCE_H_
#define _D2D_RESOURCE_H_

#include "config.h"
#include "types.h"

#include <fstream>
#ifdef D2D_ANDROID_NATIVE
#	include <android_native_app_glue.h>
#endif // D2D_ANDROID_NATIVE

namespace d2d
{
#ifdef D2D_ANDROID_NATIVE
	struct ResourceDescriptor
	{
		int32_t m_descriptor;
		off_t m_start;
		off_t m_length;
	};
#endif // D2D_ANDROID_NATIVE

	class Resource
	{
	public:
#ifdef D2D_ANDROID_NATIVE
		Resource(android_app* pApplication, const std::string& pPath);
#else
		Resource(const std::string& pPath);
#endif // D2D_ANDROID_NATIVE

		const std::string& getPath() const;

		status open();
		void close();
 		status read(void* pBuffer, size_t pCount);

 		off_t getLength();
		const void* bufferize();

#ifdef D2D_ANDROID_NATIVE
		ResourceDescriptor descript();
#endif

	private:
		std::string m_path;

#ifdef D2D_WINDOWS
 		std::ifstream m_inputStream;
 		char* m_buffer;
#elif defined D2D_ANDROID_NATIVE
		AAssetManager* m_assetManager;
		AAsset* m_asset;
#elif defined D2D_ANDROID_JNI
//		FILE* m_pFile;
		unsigned long m_nSize;
		unsigned char* m_buffer;
		unsigned long m_offset;
#endif

	}; // Resource 
}

#endif // _D2D_RESOURCE_H_