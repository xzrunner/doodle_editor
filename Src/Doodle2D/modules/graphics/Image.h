#ifndef _D2D_IMAGE_H_
#define _D2D_IMAGE_H_

#include "common/Resource.h"

#include <GLES/gl.h>

//#define LOAD_BY_SOIL

namespace d2d
{
	class Image
	{
	public:
		enum Type
		{
			e_unknown = 0,
			e_png,
			e_jpg
		};

	public:
#ifdef D2D_WINDOWS
		Image(const std::string& pPath);
#elif defined D2D_ANDROID_NATIVE
		Image(android_app* pApplication, const std::string& pPath);
#elif defined D2D_ANDROID_JNI
		Image(const std::string& pPath);
#endif

		uint8_t* loadImage();

		Type type() const { return m_type; }

		const std::string& path() const { 
			return m_resource.getPath(); 
		}

		int32_t width() const { return m_width; }
		int32_t height() const { return m_height; }

		GLint format() const { return m_format; }

		void clear();

	private:
#ifdef LOAD_BY_SOIL	
		uint8_t* loadBySOIL();
#else
		uint8_t* loadByLibPng();
		uint8_t* loadByLibJpeg();
#endif // LOAD_BY_SOIL	

	private:
		Type m_type;

		Resource m_resource;

		int32_t m_width, m_height;

		GLint m_format;

	}; // ImageLoader
}

#endif // _D2D_IMAGE_H_