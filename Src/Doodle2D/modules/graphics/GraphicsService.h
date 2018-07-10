#ifndef _D2D_GRAPHICS_SERVICE_H_
#define _D2D_GRAPHICS_SERVICE_H_

#include "common/types.h"
#include "modules/timer/TimeService.h"

#ifdef D2D_ANDROID_NATIVE
#include <android_native_app_glue.h>
#	include <string>
#elif defined D2D_ANDROID_JNI
#	include <string>
#endif

#include <EGL/egl.h>
#include <vector>

namespace d2d
{
	class Texture;
	class IDrawable;

	class GraphicsService
	{
	public:
#ifdef D2D_WINDOWS
		GraphicsService(TimeService* pTimeService);
#elif defined D2D_ANDROID_NATIVE
		GraphicsService(TimeService* pTimeService, android_app* pApplication);
#elif defined D2D_ANDROID_JNI
		GraphicsService(TimeService* pTimeService);
#endif
		~GraphicsService();

		const int32_t& getWidth() const { return m_width; }
		const int32_t& getHeight() const { return m_height; }
		float getScale() const { return m_scale; }
#ifdef D2D_WINDOWS
		void onResize(int32_t width, int32_t height);
#elif defined D2D_ANDROID_JNI
		void resize(int width, int height);
#endif

		status start();
		void stop();
		status update();

		void setImpl(IDrawable* impl) { m_impl = impl; }

 		Texture* registerTexture(const std::string& pPath);

//		void reloadTextures();
		void clearTextures();

	protected:
		status loadResources();
		status unloadResources();
		void setup();

	private:
		TimeService* m_timeService;

		int32_t m_width, m_height;
		float m_scale;

		std::vector<Texture*> m_textures;

		IDrawable* m_impl;

#ifdef D2D_ANDROID_NATIVE
		android_app* m_application;

		EGLDisplay m_display;
		EGLSurface m_surface;
		EGLContext m_context;
#endif

	}; // GraphicsService
}

#endif // _D2D_GRAPHICS_SERVICE_H_