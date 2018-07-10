#include "SoundService.h"

#include "common/Resource.h"
#include "common/Log.h"

#include <string>

using namespace d2d;

#ifdef D2D_WINDOWS

SoundService::SoundService()
{
	m_soundCount = 0;
}

#elif defined D2D_ANDROID_NATIVE

SoundService::SoundService(android_app* pApplication)
	: m_engineObj(NULL), m_engine(NULL), m_outputMixObj(NULL),
	m_BGMPlayerObj(NULL), m_BGMPlayer(NULL), m_BGMPlayerSeek(NULL),
	m_playerObj(NULL), m_player(NULL), m_playerQueue(NULL)
{
	m_application = pApplication;

	//m_sounds;
	m_soundCount = 0;
}

SoundService::~SoundService()
{
	for (int32_t i = 0; i < m_soundCount; ++i) 
	{
		delete m_sounds[i];
		m_soundCount = 0;
	}
}

status SoundService::start()
{
	Log::info("Starting SoundService.");
	SLresult lRes;
	const SLuint32 lEngineMixIIDCount = 1;
	const SLInterfaceID lEngineMixIIDs[] = { SL_IID_ENGINE };
	const SLboolean lEngineMixReqs[] = { SL_BOOLEAN_TRUE };
	const SLuint32 lOutputMixIIDCount = 0;
	const SLInterfaceID lOutputMixIIDs[] = {};
	const SLboolean lOutputMixReqs[] = {};

	lRes = slCreateEngine(&m_engineObj, 0, NULL, lEngineMixIIDCount, lEngineMixIIDs, lEngineMixReqs);
	if (lRes != SL_RESULT_SUCCESS) goto ERROR;
	lRes=(*m_engineObj)->Realize(m_engineObj, SL_BOOLEAN_FALSE);
	if (lRes != SL_RESULT_SUCCESS) goto ERROR;
	lRes=(*m_engineObj)->GetInterface(m_engineObj, SL_IID_ENGINE, &m_engine);
	if (lRes != SL_RESULT_SUCCESS) goto ERROR;

	lRes = (*m_engine)->CreateOutputMix(m_engine, &m_outputMixObj, lOutputMixIIDCount, lOutputMixIIDs, lOutputMixReqs);
	lRes = (*m_outputMixObj)->Realize(m_outputMixObj, SL_BOOLEAN_FALSE);

	if (startSoundPlayer() != STATUS_OK) goto ERROR;
	for (int32_t i = 0; i < m_soundCount; ++i) 
	{
		if (m_sounds[i]->load() != STATUS_OK) goto ERROR;
	}

	return STATUS_OK;

ERROR:
	Log::error("Error While Starting SoundService.");
	stop();
	return STATUS_KO;
}

void SoundService::stop()
{
	Log::info("Stopping SoundService.");

	// Stops and destroys BGM player.
	stopBGM();

	// Destroys sound player.
	if (m_playerObj != NULL) 
	{
		(*m_playerObj)->Destroy(m_playerObj);
		m_playerObj = NULL; m_player = NULL; m_playerQueue = NULL;
	}

	// Destroys audio output and engine.
	if (m_outputMixObj != NULL) 
	{
		(*m_outputMixObj)->Destroy(m_outputMixObj);
		m_outputMixObj = NULL;
	}
	if (m_engineObj != NULL) 
	{
		(*m_engineObj)->Destroy(m_engineObj);
		m_engineObj = NULL; m_engine = NULL;
	}

	// Frees sound resources.
	for (int32_t i = 0; i < m_soundCount; ++i) 
	{
		m_sounds[i]->unload();
	}
}

status SoundService::playBGM(const std::string& pPath)
{
	SLresult lRes;
	Log::info("Opening BGM %s", pPath.c_str());

	Resource lResource(m_application, pPath);
	ResourceDescriptor lDescriptor = lResource.descript();
	if (lDescriptor.m_descriptor < 0) 
	{
		Log::info("Could not open BGM file");
		return STATUS_KO;
	}

	SLDataLocator_AndroidFD lDataLocatorIn;
	lDataLocatorIn.locatorType = SL_DATALOCATOR_ANDROIDFD;
	lDataLocatorIn.fd          = lDescriptor.m_descriptor;
	lDataLocatorIn.offset      = lDescriptor.m_start;
	lDataLocatorIn.length      = lDescriptor.m_length;

// 	// sdcard
// 	//////////////////////////////////////////////////////////////////////////
// 	SLDataLocator_URI lDataLocatorIn;
// 	std::string lPath = std::string("file://") + pPath;
// 	lDataLocatorIn.locatorType = SL_DATALOCATOR_URI;
// 	lDataLocatorIn.URI = (SLchar*) lPath.c_str();
// 	//////////////////////////////////////////////////////////////////////////

	SLDataFormat_MIME lDataFormat;
	lDataFormat.formatType    = SL_DATAFORMAT_MIME;
	lDataFormat.mimeType      = NULL;
	lDataFormat.containerType = SL_CONTAINERTYPE_UNSPECIFIED;

	SLDataSource lDataSource;
	lDataSource.pLocator = &lDataLocatorIn;
	lDataSource.pFormat  = &lDataFormat;

	SLDataLocator_OutputMix lDataLocatorOut;
	lDataLocatorOut.locatorType = SL_DATALOCATOR_OUTPUTMIX;
	lDataLocatorOut.outputMix   = m_outputMixObj;

	SLDataSink lDataSink;
	lDataSink.pLocator = &lDataLocatorOut;
	lDataSink.pFormat  = NULL;

	const SLuint32 lBGMPlayerIIDCount = 2;
	const SLInterfaceID lBGMPlayerIIDs[] = { SL_IID_PLAY, SL_IID_SEEK };
	const SLboolean lBGMPlayerReqs[] = { SL_BOOLEAN_TRUE, SL_BOOLEAN_TRUE };

	lRes = (*m_engine)->CreateAudioPlayer(m_engine, &m_BGMPlayerObj, &lDataSource, 
		&lDataSink, lBGMPlayerIIDCount, lBGMPlayerIIDs, lBGMPlayerReqs);
	if (lRes != SL_RESULT_SUCCESS) goto ERROR;
	lRes = (*m_BGMPlayerObj)->Realize(m_BGMPlayerObj, SL_BOOLEAN_FALSE);
	if (lRes != SL_RESULT_SUCCESS) goto ERROR;
	lRes = (*m_BGMPlayerObj)->GetInterface(m_BGMPlayerObj, SL_IID_PLAY, &m_BGMPlayer);
	if (lRes != SL_RESULT_SUCCESS) goto ERROR;
	lRes = (*m_BGMPlayerObj)->GetInterface(m_BGMPlayerObj, SL_IID_SEEK, &m_BGMPlayerSeek);
	if (lRes != SL_RESULT_SUCCESS) goto ERROR;
	lRes = (*m_BGMPlayerSeek)->SetLoop(m_BGMPlayerSeek, SL_BOOLEAN_TRUE, 0, SL_TIME_UNKNOWN);
	if (lRes != SL_RESULT_SUCCESS) goto ERROR;
	lRes = (*m_BGMPlayer)->SetPlayState(m_BGMPlayer, SL_PLAYSTATE_PLAYING);
	if (lRes != SL_RESULT_SUCCESS) goto ERROR;

	return STATUS_OK;

ERROR:
	return STATUS_KO;
}

void SoundService::stopBGM()
{
	if (m_BGMPlayer != NULL) 
	{
		SLuint32 lBGMPlayerState;
		(*m_BGMPlayerObj)->GetState(m_BGMPlayerObj, &lBGMPlayerState);
		if (lBGMPlayerState == SL_OBJECT_STATE_REALIZED) 
		{
			(*m_BGMPlayer)->SetPlayState(m_BGMPlayer, SL_PLAYSTATE_PAUSED);
			(*m_BGMPlayerObj)->Destroy(m_BGMPlayerObj);
			m_BGMPlayerObj = NULL;
			m_BGMPlayer = NULL;
			m_BGMPlayerSeek = NULL;
		}
	}
}

Sound* SoundService::registerSound(const std::string& pPath) 
{
	for (int32_t i = 0; i < m_soundCount; ++i) 
	{
		if (strcmp(pPath.c_str(), m_sounds[i]->getPath().c_str()) == 0) 
		{
			return m_sounds[i];
		}
	}

	Sound* lSound = new Sound(m_application, pPath);
	m_sounds[m_soundCount++] = lSound;
	return lSound;
}

void SoundService::playSound(Sound* pSound)
{
	SLresult lRes;
	SLuint32 lPlayerState;
	(*m_playerObj)->GetState(m_playerObj, &lPlayerState);
	if (lPlayerState == SL_OBJECT_STATE_REALIZED) 
	{
		int16_t* lBuffer = (int16_t*) pSound->m_buffer;
		off_t    lLength = pSound->m_length;

		// Removes any sound from the queue.
		lRes = (*m_playerQueue)->Clear(m_playerQueue);
		if (lRes != SL_RESULT_SUCCESS) goto ERROR;

		// Plays the new sound.
		lRes = (*m_playerQueue)->Enqueue(m_playerQueue, lBuffer, lLength);
		if (lRes != SL_RESULT_SUCCESS) goto ERROR;
	}

	return;

ERROR:
	d2d::Log::error("Error trying to play sound");
}

status SoundService::startSoundPlayer()
{
	SLresult lRes;

	// Set-up sound audio source.
	SLDataLocator_AndroidSimpleBufferQueue lDataLocatorIn;
	lDataLocatorIn.locatorType = SL_DATALOCATOR_ANDROIDSIMPLEBUFFERQUEUE;
	// At most one buffer in the queue.
	lDataLocatorIn.numBuffers = 1;

	SLDataFormat_PCM lDataFormat;
	lDataFormat.formatType = SL_DATAFORMAT_PCM;
	lDataFormat.numChannels = 1; // Mono sound.
	lDataFormat.samplesPerSec = SL_SAMPLINGRATE_44_1;
	lDataFormat.bitsPerSample = SL_PCMSAMPLEFORMAT_FIXED_16;
	lDataFormat.containerSize = SL_PCMSAMPLEFORMAT_FIXED_16;
	lDataFormat.channelMask = SL_SPEAKER_FRONT_CENTER;
	lDataFormat.endianness = SL_BYTEORDER_LITTLEENDIAN;

	SLDataSource lDataSource;
	lDataSource.pLocator = &lDataLocatorIn;
	lDataSource.pFormat = &lDataFormat;

	SLDataLocator_OutputMix lDataLocatorOut;
	lDataLocatorOut.locatorType = SL_DATALOCATOR_OUTPUTMIX;
	lDataLocatorOut.outputMix = m_outputMixObj;

	SLDataSink lDataSink;
	lDataSink.pLocator = &lDataLocatorOut;
	lDataSink.pFormat = NULL;

	const SLuint32 lSoundPlayerIIDCount = 2;
	const SLInterfaceID lSoundPlayerIIDs[] = { SL_IID_PLAY, SL_IID_BUFFERQUEUE };
	const SLboolean lSoundPlayerReqs[] = { SL_BOOLEAN_TRUE, SL_BOOLEAN_TRUE };

	lRes = (*m_engine)->CreateAudioPlayer(m_engine, &m_playerObj, &lDataSource, 
		&lDataSink, lSoundPlayerIIDCount, lSoundPlayerIIDs, lSoundPlayerReqs);
	if (lRes != SL_RESULT_SUCCESS) goto ERROR;
	lRes = (*m_playerObj)->Realize(m_playerObj, SL_BOOLEAN_FALSE);
	if (lRes != SL_RESULT_SUCCESS) goto ERROR;
	lRes = (*m_playerObj)->GetInterface(m_playerObj, SL_IID_PLAY, &m_player);
	if (lRes != SL_RESULT_SUCCESS) goto ERROR;
	lRes = (*m_playerObj)->GetInterface(m_playerObj, SL_IID_BUFFERQUEUE, &m_playerQueue);
	if (lRes != SL_RESULT_SUCCESS) goto ERROR;
	lRes = (*m_player)->SetPlayState(m_player, SL_PLAYSTATE_PLAYING);
	if (lRes != SL_RESULT_SUCCESS) goto ERROR;

	// Registers a callback called when sound is finished.
	lRes = (*m_playerQueue)->RegisterCallback(m_playerQueue, callback_sound, this);
	//	slCheckErrorWithStatus(lRes, "Problem registering player callback (Error %d).", lRes);
	lRes = (*m_player)->SetCallbackEventsMask(m_player, SL_PLAYEVENT_HEADATEND);
	//	slCheckErrorWithStatus(lRes, "Problem registering player callback mask (Error %d).", lRes);

	return STATUS_OK;

ERROR:
	d2d::Log::error("Error while starting SoundPlayer");
	return STATUS_KO;
}

void SoundService::callback_sound(SLBufferQueueItf pObject, void* pContext)
{
	// Context can be casted back to the original type.
	SoundService& lService = *(SoundService*)pContext;

	Log::info("Ended playing sound.");
}

#elif defined D2D_ANDROID_JNI

SoundService::SoundService()
{
	m_soundCount = 0;
}

#endif
