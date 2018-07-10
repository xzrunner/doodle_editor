#include "Sound.h"

#include "common/Log.h"

using namespace d2d;

#ifdef D2D_WINDOWS
Sound::Sound(const std::string& pPath) 
	: m_resource(pPath)
{
	m_buffer = NULL;
	m_length = 0;
}
#elif defined D2D_ANDROID_NATIVE
Sound::Sound(android_app* pApplication, const std::string& pPath) 
	: m_resource(pApplication, pPath)
{
	m_buffer = NULL;
	m_length = 0;
}
#elif defined D2D_ANDROID_JNI
Sound::Sound(const std::string& pPath) 
	: m_resource(pPath)
{
	m_buffer = NULL;
	m_length = 0;
}
#endif

const std::string& Sound::getPath() 
{
	return m_resource.getPath();
}

status Sound::load() 
{
	status lRes;

	if (m_resource.open() != STATUS_OK) 
	{
		return STATUS_KO;
	}

	m_length = m_resource.getLength();
	m_buffer = new uint8_t[m_length];
	lRes = m_resource.read(m_buffer, m_length);
	m_resource.close();

	if (lRes != STATUS_OK) 
	{
		Log::error("Error while reading PCM sound.");
		return STATUS_KO;
	} 
	else 
	{
		return STATUS_OK;
	}
}

status Sound::unload() 
{
	delete[] m_buffer;
	m_buffer = NULL; m_length = 0;
	return STATUS_OK;
}
