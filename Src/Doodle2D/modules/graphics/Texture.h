#ifndef _D2D_TEXTURE_H_
#define _D2D_TEXTURE_H_

#include "Image.h"

#include <GLES/gl.h>

namespace d2d
{
	class Texture
	{
	public:

#ifdef D2D_WINDOWS
		Texture(const std::string& pPath);
#elif defined D2D_ANDROID_NATIVE
		Texture(android_app* pApplication, const std::string& pPath);
#elif defined D2D_ANDROID_JNI
		Texture(const std::string& pPath);
#endif
		~Texture();

		const std::string& getPath() const { return m_image.path(); }
		int32_t getWidth() const { return m_image.width(); }
		int32_t getHeight() const { return m_image.height(); }
		bool isFlipY() const { return m_image.type() == Image::e_jpg; }

		status load();
		void unload();
		void bind();
		void unbind();

//		void reload();

	private:
//		status loadBySOIL();
		status loadByLibpngLibjpeg();

	private:
		Image m_image;

		GLuint m_textureId;

	}; // Texture
}

#endif // _D2D_TEXTURE_H_