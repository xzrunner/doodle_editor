#include "Resource.h"
#include "Log.h"

#ifdef D2D_ANDROID_JNI
//#include "fmemopen/fmemopen.c"
#include "modules/filesystem/FileSystem.h"
#endif // D2D_ANDROID_JNI

#include <sys/stat.h>

using namespace d2d;

#ifdef D2D_ANDROID_NATIVE
Resource::Resource(android_app* pApplication, const std::string& pPath)
	: m_path(pPath)
{
	m_assetManager = pApplication->activity->assetManager;
	m_asset = NULL;
}
#else
Resource::Resource(const std::string& pPath)
	: m_path(pPath)
{
	m_buffer = NULL;
#ifdef D2D_ANDROID_JNI
//	m_pFile = NULL;
	m_nSize = 0;
	m_offset = 0;
#endif // D2D_ANDROID_JNI
}
#endif // D2D_ANDROID_NATIVE

const std::string& Resource::getPath() const
{
	return m_path;
}

status Resource::open()
{
#ifdef D2D_WINDOWS
 	m_inputStream.open(m_path.c_str(), std::ios::in | std::ios::binary);
	return m_inputStream.fail() ? STATUS_KO : STATUS_OK;
#elif defined D2D_ANDROID_NATIVE
	m_asset = AAssetManager_open(m_assetManager, m_path.c_str(), AASSET_MODE_UNKNOWN);
	return (m_asset != NULL) ? STATUS_OK : STATUS_KO;
#elif defined D2D_ANDROID_JNI
	m_buffer = FileSystem::Instance()->getFileData(m_path.c_str(), "rb", &m_nSize);
//	m_pFile = fmemopen(m_buffer, m_nSize, "rb");
	return STATUS_OK;
#endif
}

void Resource::close()
{
#ifdef D2D_WINDOWS
 	m_inputStream.close();
 	delete[] m_buffer; m_buffer = NULL;
#elif defined D2D_ANDROID_NATIVE
	if (m_asset != NULL)
	{
		AAsset_close(m_asset);
		m_asset = NULL;
	}
#elif defined D2D_ANDROID_JNI
// 	fclose(m_pFile);
// 	m_pFile = NULL;
	delete[] m_buffer; m_buffer = NULL;
#endif
}

status Resource::read(void* pBuffer, size_t pCount)
{
#ifdef D2D_WINDOWS
 	m_inputStream.read((char*)pBuffer, pCount);
 	return (!m_inputStream.fail()) ? STATUS_OK : STATUS_KO;
#elif defined D2D_ANDROID_NATIVE
	int32_t lReadCount = AAsset_read(m_asset, pBuffer, pCount);
	return (lReadCount == pCount) ? STATUS_OK : STATUS_KO;
#elif defined D2D_ANDROID_JNI
	if(m_offset + pCount <= m_nSize)
	{
		memcpy(pBuffer, m_buffer + m_offset, pCount);
		m_offset += pCount;
		return STATUS_OK;
	}
	else
	{
		return STATUS_KO;
	}
#endif
}

off_t Resource::getLength() 
{
#ifdef D2D_WINDOWS
 	struct stat filestatus;
 	if (stat(m_path.c_str(), &filestatus) >= 0) 
 	{
 		return filestatus.st_size;
 	} 
 	else 
 	{
 		return -1;
 	}
#elif defined D2D_ANDROID_NATIVE
	return AAsset_getLength(m_asset);
#elif defined D2D_ANDROID_JNI
	return m_nSize;
#endif
}

const void* Resource::bufferize() 
{
#ifdef D2D_WINDOWS
 	off_t lSize = getLength();
 	if (lSize <= 0) return NULL;
 
 	m_buffer = new char[lSize];
 	m_inputStream.read(m_buffer, lSize);
 	if (!m_inputStream.fail())
 		return m_buffer;
 	else
 		return NULL;
#elif defined D2D_ANDROID_NATIVE
	return AAsset_getBuffer(m_asset);
#elif defined D2D_ANDROID_JNI
	return m_buffer;
#endif
}

#ifdef D2D_ANDROID_NATIVE
ResourceDescriptor Resource::descript()
{
	ResourceDescriptor lDescriptor = { -1, 0, 0 };
	AAsset* lAsset = AAssetManager_open(m_assetManager, m_path.c_str(), AASSET_MODE_UNKNOWN);
	if (lAsset != NULL) 
	{
		lDescriptor.m_descriptor = AAsset_openFileDescriptor(lAsset, 
			&lDescriptor.m_start, &lDescriptor.m_length);
		AAsset_close(lAsset);
	}
	return lDescriptor;
}
#endif