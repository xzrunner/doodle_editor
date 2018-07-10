#include "Image.h"

#include "Render/GL10.h"

#include <SOIL/SOIL.h>

using namespace wxgui;

Image::Image()
{
	m_textureID = 0;
	m_width = m_height = 0;
}

bool Image::loadFromFile(const wxString& filepath)
{
	m_filepath = filepath;

	reload();

	//  	LibJpeg::ImageData data;
	//  	LibJpeg::read_JPEG_file(m_filepath.c_str(), data);
	//  	m_textureID = SOIL_internal_create_OGL_texture(
	//  		data.pixels, data.width, data.height, data.channels,
	//  		m_textureID, SOIL_FLAG_INVERT_Y,
	//  		GL_TEXTURE_2D, GL_TEXTURE_2D,
	//  		GL_MAX_TEXTURE_SIZE );
	//  	delete[] data.pixels;

	if (m_textureID == 0)
	{
		m_width = m_height = 0;
		return false;
	}
	else
	{
		GL10::BindTexture(GL10::GL_TEXTURE_2D, m_textureID);
		GL10::GetTexLevelParameteriv(GL10::GL_TEXTURE_2D, 0, GL10::GL_TEXTURE_WIDTH, &m_width);
		GL10::GetTexLevelParameteriv(GL10::GL_TEXTURE_2D, 0, GL10::GL_TEXTURE_HEIGHT, &m_height);
		GL10::BindTexture(GL10::GL_TEXTURE_2D, NULL);
		return true;
	}
}

void Image::reload() const
{
	m_textureID = SOIL_load_OGL_texture
		(
		m_filepath.c_str(),
		SOIL_LOAD_AUTO,
		m_textureID,
		SOIL_FLAG_INVERT_Y
		);
}

void Image::draw() const
{
	GL10::Enable(GL10::GL_BLEND);
	GL10::BlendFunc(GL10::GL_SRC_ALPHA, GL10::GL_ONE_MINUS_SRC_ALPHA);

	GL10::Color4f(1.0f, 1.0f, 1.0f, 1.0f);

	const float hWidth = m_width * 0.5f,
		hHeight = m_height * 0.5f;

	GL10::BindTexture(GL10::GL_TEXTURE_2D, m_textureID);
	GL10::Begin(GL10::GL_QUADS);
		GL10::TexCoord2f(0, 0); GL10::Vertex3f(-hWidth, -hHeight, -1.0f);
		GL10::TexCoord2f(1, 0); GL10::Vertex3f( hWidth, -hHeight, -1.0f);
		GL10::TexCoord2f(1, 1); GL10::Vertex3f( hWidth,  hHeight, -1.0f);
		GL10::TexCoord2f(0, 1); GL10::Vertex3f(-hWidth,  hHeight, -1.0f);
	GL10::End();
	GL10::BindTexture(GL10::GL_TEXTURE_2D, NULL);

	GL10::Disable(GL10::GL_BLEND);
}