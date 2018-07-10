#include "Texture.h"

#include "common/Log.h"
#include "common/math.h"

using namespace d2d;

#ifdef D2D_WINDOWS
Texture::Texture(const std::string& pPath)
	: m_image(pPath)
	, m_textureId(0)
{
}
#elif defined D2D_ANDROID_NATIVE
Texture::Texture(android_app* pApplication, const std::string& pPath)
	: m_image(pApplication, pPath)
	, m_textureId(0)
{
}
#elif defined D2D_ANDROID_JNI
Texture::Texture(const std::string& pPath)
	: m_image(pPath)
	, m_textureId(0)
{
}
#endif

Texture::~Texture()
{
	unload();
}

status Texture::load()
{
	if (m_textureId != 0)
		return STATUS_OK;

	return loadByLibpngLibjpeg();
}

void Texture::unload()
{
	if (m_textureId != 0) 
	{
		glDeleteTextures(1, &m_textureId);
		m_textureId = 0;

		m_image.clear();
	}
}

void Texture::bind()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_textureId);
}

void Texture::unbind()
{
	glBindTexture(GL_TEXTURE_2D, NULL);
}

// void Texture::reload()
// {
// 	loadByLibpngLibjpeg();
// }

//status Texture::loadBySOIL()
//{
//	int channels = 0;
//
//	// 	//////////////////////////////////////////////////////////////////////////
//	// 	// (1) SOIL_load_image + SOIL_create_OGL_texture
//	// 	//////////////////////////////////////////////////////////////////////////
//	//  	uint8_t* lImageBuffer = SOIL_load_image(
//	//  		m_resource.getPath().c_str(),
//	//  		&m_image.width(),
//	//  		&m_image.height(),
//	//  		&channels,
//	//  		SOIL_LOAD_AUTO
//	//  		);
//	// 
//	// 	m_textureId = SOIL_create_OGL_texture(
//	// 		lImageBuffer,
//	// 		m_image.width(),
//	// 		m_image.height(),
//	// 		channels,
//	// 		m_textureId,
//	// 		SOIL_FLAG_INVERT_Y
//	// 		);
//	// 	//////////////////////////////////////////////////////////////////////////
//
//	//////////////////////////////////////////////////////////////////////////
//	// (2) SOIL_load_image_from_memory + SOIL_create_OGL_texture
//	//////////////////////////////////////////////////////////////////////////
//	if (m_resource.open() == STATUS_KO)
//		return STATUS_KO;
//
//	//size_t size = m_resource.getLength();
//	//void *buffer = malloc(size);
//	//m_resource.read(buffer, size);
//
//	const void *buffer = m_resource.bufferize();
//
//	unsigned char* ptr = static_cast<unsigned char*>(const_cast<void*>(buffer));
//	uint8_t* lImageBuffer = SOIL_load_image_from_memory(
//		ptr,
//		m_resource.getLength(),
//		&m_image.width(),
//		&m_image.height(),
//		&channels,
//		SOIL_LOAD_AUTO
//		);
//
//	m_resource.close();
//
//	m_textureId = SOIL_create_OGL_texture(
//		lImageBuffer,
//		m_image.width(),
//		m_image.height(),
//		channels,
//		m_textureId,
//		SOIL_FLAG_INVERT_Y
//		);
//	//////////////////////////////////////////////////////////////////////////
//
//	////////////////////////////////////////////////////////////////////////////
//	//// (3) SOIL_load_image + SOIL_create_OGL_texture
//	////////////////////////////////////////////////////////////////////////////
//	///*	variables	*/
//	//unsigned char* img;
//	///*	try to load the image	*/
//	//img = SOIL_load_image( m_resource.getPath().c_str(), &m_image.width(), &m_image.height(), &channels, SOIL_LOAD_AUTO );
//
//	//if( NULL == img )
//	//	return STATUS_KO;
//
//	///*	OK, make it a texture!	*/
//	//m_textureId = SOIL_internal_create_OGL_texture(
//	//	img, m_image.width(), m_image.height(), channels,
//	//	m_textureId, SOIL_FLAG_INVERT_Y,
//	//	GL_TEXTURE_2D, GL_TEXTURE_2D,
//	//	GL_MAX_TEXTURE_SIZE );
//	///*	and nuke the image data	*/
//	//SOIL_free_image_data( img );
//	///*	and return the handle, such as it is	*/
//	////////////////////////////////////////////////////////////////////////////
//
//	return STATUS_OK;
//}

status Texture::loadByLibpngLibjpeg()
{
	int channels = 0;

	uint8_t* lImageBuffer = m_image.loadImage();
	if (lImageBuffer == NULL) return STATUS_KO;

	int texture_width = getNextPOT(m_image.width());
	int texture_height = getNextPOT(m_image.height());

	// Creates a new OpenGL texture.
	GLenum lErrorResult;
	glGenTextures(1, &m_textureId);
	glBindTexture(GL_TEXTURE_2D, m_textureId);
	// Set-up texture properties.
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, /*GL_NEAREST*/GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, /*GL_NEAREST*/GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	// Loads image data into OpenGL.
	if (texture_width != m_image.width() || texture_height != m_image.height()) 
	{
		//		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		glTexImage2D(GL_TEXTURE_2D, 0, m_image.format(), texture_width, texture_height, 0, m_image.format(), GL_UNSIGNED_BYTE, NULL);
		glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, m_image.width(), m_image.height(), m_image.format(),GL_UNSIGNED_BYTE, lImageBuffer);
	} 
	else
	{
		//		glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
		glTexImage2D(GL_TEXTURE_2D, 0, m_image.format(), texture_width, texture_height, 0, m_image.format(), GL_UNSIGNED_BYTE,lImageBuffer);
	}

	glBindTexture(GL_TEXTURE_2D, NULL);
	delete[] lImageBuffer;
	if (glGetError() != GL_NO_ERROR) 
	{
		Log::error("Error loading texture into OpenGL.");
		unload();
		return STATUS_KO;
	}

	// debug
	Log::info("zz +++++++++++++++++tex_id: %d", m_textureId);

	return STATUS_OK;
}