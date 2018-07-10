#ifndef _D2D_SOUND_H_
#define _D2D_SOUND_H_

#include "common/config.h"
#include "common/Resource.h"
#include "common/Types.h"

namespace d2d
{
	class Sound
	{
	public:
#ifdef D2D_WINDOWS
		Sound(const std::string& pPath);
#elif defined D2D_ANDROID_NATIVE
		Sound(android_app* pApplication, const std::string& pPath);
#elif defined D2D_ANDROID_JNI
		Sound(const std::string& pPath);
#endif

		const std::string& getPath();

		status load();
		status unload();

	private:
		Resource m_resource;
		uint8_t* m_buffer; off_t m_length;

		friend class SoundService;

	}; // Sound
}

#endif // _D2D_SOUND_H_