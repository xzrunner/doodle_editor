#include "Texture.h"
#include "SOIL/SOIL.h"
#include <windows.h>
#include <GL/gl.h>

using namespace FEDITOR;

bool Texture::loadFromFile(const std::string& filename)
{
	m_filename = filename;

	m_id = SOIL_load_OGL_texture
		(
		m_filename.c_str(),
		SOIL_LOAD_AUTO,
		m_id,
		SOIL_FLAG_INVERT_Y
		);

	if (m_id == 0)
	{
		m_width = m_height = 0;
		return false;
	}

	GLint width, height;
	glBindTexture(GL_TEXTURE_2D, m_id);
		glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &width);
		glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &height);
	glBindTexture(GL_TEXTURE_2D, NULL);
	m_width = width;
	m_height = height;

	return true;
}