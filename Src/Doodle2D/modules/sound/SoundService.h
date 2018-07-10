#ifndef _D2D_SOUND_SERVICE_H_
#define _D2D_SOUND_SERVICE_H_

#include "common/config.h"
#include "common/Types.h"
#include "Sound.h"

#ifdef D2D_WINDOWS

namespace d2d
{
	class SoundService
	{
	public:
		SoundService();

	private:
		Sound* m_sounds[32]; int32_t m_soundCount;

	}; // SoundService
}

#elif defined D2D_ANDROID_NATIVE

#include <android_native_app_glue.h>
#include <SLES/OpenSLES.h>
#include <SLES/OpenSLES_Android.h>
#include <SLES/OpenSLES_AndroidConfiguration.h>

namespace d2d 
{
	class SoundService 
	{
	public:
		SoundService(android_app* pApplication);
		~SoundService();

		status start();
		void stop();

		status playBGM(const std::string& pPath);
		void stopBGM();

		Sound* registerSound(const std::string& pPath);
		void playSound(Sound* pSound);

	private:
		status startSoundPlayer();

		static void callback_sound(SLBufferQueueItf pObject, void* pContext);

	private:
		android_app* m_application;
		SLObjectItf m_engineObj; SLEngineItf m_engine;
		SLObjectItf m_outputMixObj;

		SLObjectItf m_BGMPlayerObj; SLPlayItf m_BGMPlayer;
		SLSeekItf m_BGMPlayerSeek;

		SLObjectItf m_playerObj; SLPlayItf m_player;
		SLBufferQueueItf m_playerQueue;
		Sound* m_sounds[32]; int32_t m_soundCount;

	}; // SoundService
}

#elif defined D2D_ANDROID_JNI

namespace d2d
{
	class SoundService
	{
	public:
		SoundService();

	private:
		Sound* m_sounds[32]; int32_t m_soundCount;

	}; // SoundService
}

#endif

#endif // _D2D_SOUND_SERVICE_H_
