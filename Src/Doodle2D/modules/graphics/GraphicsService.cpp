#include "GraphicsService.h"
#include "IDrawable.h"
#include "Texture.h"

#include "common/tools.h"
#include "common/Log.h"

#include <GLES/gl.h>

using namespace d2d;

#ifdef D2D_WINDOWS
GraphicsService::GraphicsService(TimeService* pTimeService)
#elif defined D2D_ANDROID_NATIVE
GraphicsService::GraphicsService(TimeService* pTimeService, android_app* pApplication)
	: m_application(pApplication)
	, m_display(EGL_NO_DISPLAY), m_surface(EGL_NO_SURFACE), m_context(EGL_NO_CONTEXT)
#elif defined D2D_ANDROID_JNI
GraphicsService::GraphicsService(TimeService* pTimeService)
#endif
{
	m_timeService = pTimeService;
	m_impl = NULL;
	m_width = m_height = 0;
	m_scale = 1.0f;
}

GraphicsService::~GraphicsService()
{
	clearTextures();
}

#ifdef D2D_WINDOWS

void GraphicsService::onResize(int32_t width, int32_t height)
{
	m_width = width;
	m_height = height;
	m_scale = std::min((float)m_width / d2d::SCREEN_WIDTH, (float)m_height / d2d::SCREEN_HEIGHT);

	glViewport(0, 0, m_width, m_height);

	setup();
}

#elif defined D2D_ANDROID_JNI

void GraphicsService::resize(int width, int height)
{
	m_width = width;
	m_height = height;
	m_scale = std::min((float)m_width / d2d::SCREEN_WIDTH, (float)m_height / d2d::SCREEN_HEIGHT);

	glViewport(0, 0, m_width, m_height);

	setup();
}

#endif

status GraphicsService::start()
{
#ifdef D2D_WINDOWS
	m_scale = std::min((float)m_width / d2d::SCREEN_WIDTH, (float)m_height / d2d::SCREEN_HEIGHT);

	glViewport(0, 0, m_width, m_height);

	if (loadResources() != STATUS_OK)
	{
		Log::error("Error while starting GraphicsService");
		stop();
		return STATUS_KO;
	}
	else
	{
		setup();
		return STATUS_OK;
	}
#elif defined D2D_ANDROID_NATIVE
	EGLint lFormat, lNumConfigs, lErrorResult;
	EGLConfig lConfig;
	const EGLint lAttributes[] = {
		EGL_RENDERABLE_TYPE, EGL_OPENGL_ES_BIT, 
		EGL_BLUE_SIZE, 5, EGL_GREEN_SIZE, 6, EGL_RED_SIZE, 5,
		EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
		EGL_NONE
	};
	m_display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
	if (m_display == EGL_NO_DISPLAY) 
		goto ERROR;

	if (!eglInitialize(m_display, NULL, NULL)) 
		goto ERROR;
	if(!eglChooseConfig(m_display, lAttributes, &lConfig, 1, &lNumConfigs) 
		|| (lNumConfigs <= 0)) 
		goto ERROR;
	if (!eglGetConfigAttrib(m_display, lConfig, EGL_NATIVE_VISUAL_ID, &lFormat)) 
		goto ERROR;
	ANativeWindow_setBuffersGeometry(m_application->window, 0, 0, lFormat);

	m_surface = eglCreateWindowSurface(m_display, lConfig, m_application->window, NULL);
	if (m_surface == EGL_NO_SURFACE) goto ERROR;
	m_context = eglCreateContext(m_display, lConfig, EGL_NO_CONTEXT, NULL);
	if (m_context == EGL_NO_CONTEXT) goto ERROR;
	if (!eglMakeCurrent (m_display, m_surface, m_surface, m_context)
		|| !eglQuerySurface(m_display, m_surface, EGL_WIDTH,  &m_width)
		|| !eglQuerySurface(m_display, m_surface, EGL_HEIGHT, &m_height)
		|| (m_width <= 0) || (m_height <= 0)) goto ERROR;

	m_scale = std::min((float)m_width / d2d::SCREEN_WIDTH, (float)m_height / d2d::SCREEN_HEIGHT);

	glViewport(0, 0, m_width, m_height);

	if (loadResources() != STATUS_OK) goto ERROR;
	setup();
	return STATUS_OK;

ERROR:
	Log::error("Error while starting GraphicsService");
	stop();
	return STATUS_KO;
#elif defined D2D_ANDROID_JNI
// 	m_scale = std::min((float)m_width / d2d::SCREEN_WIDTH, (float)m_height / d2d::SCREEN_HEIGHT);
// 
// 	glViewport(0, 0, m_width, m_height);

	if (loadResources() != STATUS_OK)
	{
		Log::error("Error while starting GraphicsService");
		stop();
		return STATUS_KO;
	}
	else
	{
		setup();
		return STATUS_OK;
	} 
#endif
}

void GraphicsService::stop()
{
	unloadResources();

#ifdef D2D_ANDROID_NATIVE
	if (m_display != EGL_NO_DISPLAY) 
	{
		eglMakeCurrent(m_display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
		if (m_context != EGL_NO_CONTEXT) 
		{
			eglDestroyContext(m_display, m_context);
			m_context = EGL_NO_CONTEXT;
		}
		if (m_surface != EGL_NO_SURFACE) 
		{
			eglDestroySurface(m_display, m_surface);
			m_surface = EGL_NO_SURFACE;
		}
		eglTerminate(m_display);
		m_display = EGL_NO_DISPLAY;
	}
#endif
}

status GraphicsService::update()
{
#ifdef D2D_FRAME_RATE
	double start = m_timeService->now();
#endif // D2D_FRAME_RATE

	m_impl->draw();

#ifdef D2D_FRAME_RATE
	static double time = 0.0f, totTime = 0.0f;
	static int totFrame = 0;

	double cost = m_timeService->now() - start;
	if (cost > 0.5f)
	{
		time = totTime = 0;
		totFrame = 0;
		m_timeService->reset();
	}
	else
	{
		time += m_timeService->elapsed();
		totTime += cost;
		++totFrame;
		if (time > 1.0f)
		{
			d2d::Log::info("graphics: %.0f", 1.0f * totFrame / totTime);
			time = 0.0f;
		}
	}
#endif // D2D_FRAME_RATE

#ifdef D2D_ANDROID_NATIVE
	if (eglSwapBuffers(m_display, m_surface) != EGL_TRUE) 
	{
		Log::error("Error %d swapping buffers.", eglGetError());
		return STATUS_KO;
	}
#endif
	return STATUS_OK;
}

Texture* GraphicsService::registerTexture(const std::string& pPath)
{
	for (int32_t i = 0, n = m_textures.size(); i < n; ++i) 
	{
		if (strcmp(pPath.c_str(), m_textures[i]->getPath().c_str()) == 0)
			return m_textures[i];
	}
#ifdef D2D_WINDOWS
	Texture* lTexture = new Texture(pPath);
#elif defined D2D_ANDROID_NATIVE
	Texture* lTexture = new Texture(m_application, pPath);
#elif defined D2D_ANDROID_JNI
	Texture* lTexture = new Texture(pPath);
#endif
	m_textures.push_back(lTexture);
	return lTexture;
}

// void GraphicsService::reloadTextures()
// {
// 	for (size_t i = 0, n = m_textures.size(); i < n; ++i)
// 		m_textures[i]->reload();
// }

void GraphicsService::clearTextures()
{
	for_each(m_textures.begin(), m_textures.end(), DeletePointerFunctor<Texture>());
	m_textures.clear();
}

status GraphicsService::loadResources()
{
	for (int32_t i = 0, n = m_textures.size(); i < n; ++i) 
	{
		if (m_textures[i]->load() != STATUS_OK)
			return STATUS_KO;
	}
	//////////////////////////////////////////////////////////////////////////

// 	for (int32_t i = 0; i < m_spriteCount; ++i) 
// 	{
// 		m_sprites[i]->load();
// 	}
// 	for (int32_t i = 0; i < m_tileMapCount; ++i) 
// 	{
// 		if (m_tileMaps[i]->load() != STATUS_OK) {
// 			return STATUS_KO;
// 		}
// 	}

	//////////////////////////////////////////////////////////////////////////
	return m_impl->load();
	//////////////////////////////////////////////////////////////////////////

//	return STATUS_OK;
}

status GraphicsService::unloadResources()
{
	for (int32_t i = 0, n = m_textures.size(); i < n; ++i)
		m_textures[i]->unload();
	return STATUS_OK;
}

void GraphicsService::setup()
{
	glEnable(GL_TEXTURE_2D);
	glDisable(GL_DEPTH_TEST);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrthof(0.0f, (GLfloat)m_width, 0.0f, (GLfloat)m_height, 0.0f, 1.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glScalef(m_scale, m_scale, 0.0f);
}