#include "VertexBufferObject.h"

#include "common/Exception.h"

#include <stdlib.h>

using namespace d2d;

VertexBufferObject::VertexBufferObject(size_t size, GLenum target, GLenum usage)
	: VertexBuffer(size, target, usage)
	, m_vbo(0)
	, m_mapped(NULL)
	, m_bufferCopy(NULL)
{
	std::string strVersion((char *)glGetString(GL_VERSION));
	if ((int)strVersion.find("1.0") != -1)
 		throw d2d::Exception("Not supported");

	bool ok = load(false);

	if (!ok)
		throw d2d::Exception("Could not load VBO.");
}

VertexBufferObject::~VertexBufferObject()
{
	if (m_vbo)
		unload(false);
}

void* VertexBufferObject::map()
{
	if (m_mapped)
		throw d2d::Exception("VBO is already mapped!");

	m_mapped = malloc(getSize());
	if (!m_mapped)
		throw d2d::Exception("Out of memory!");
//	glGetBufferSubData(getTarget(), 0, getSize(), m_mapped);

	return m_mapped;
}

void VertexBufferObject::unmap()
{
	glBufferSubData(getTarget(), 0, getSize(), m_mapped);
	free(m_mapped), m_mapped = NULL;
}

void VertexBufferObject::bind()
{
	glBindBuffer(getTarget(), m_vbo);
}

void VertexBufferObject::unbind()
{
	glBindBuffer(getTarget(), 0);
}

void VertexBufferObject::fill(size_t offset, size_t size, const void* data)
{
 	if (m_mapped)
 		memcpy(static_cast<char*>(m_mapped) + offset, data, size);
 	else
		glBufferSubData(getTarget(), offset, size, data);
}

const void* VertexBufferObject::getPointer(size_t offset) const
{
	return reinterpret_cast<const void*>(offset);	
}

bool VertexBufferObject::loadVolatile()
{
	return load(true);
}

void VertexBufferObject::unloadVolatile()
{
	unload(true);
}

bool VertexBufferObject::load(bool restore)
{
	glGenBuffers(1, &m_vbo);

	bind();

	// Copy the old buffer only if 'restore' was requested.
	const GLvoid *src = restore ? m_bufferCopy : 0;

	while (GL_NO_ERROR != glGetError())
		/* clear error messages */;

	// Note that if 'src' is '0', no data will be copied.
	glBufferData(getTarget(), getSize(), src, getUsage());
	GLenum err = glGetError();

	delete[] m_bufferCopy, m_bufferCopy = NULL;

	unbind();

	return (GL_NO_ERROR == err);
}

void VertexBufferObject::unload(bool save)
{
	delete[] m_bufferCopy, m_bufferCopy = NULL;

	// Save data before unloading.
	if (save)
	{
		bind();

		GLint size;
		glGetBufferParameteriv(getTarget(), GL_BUFFER_SIZE, &size);

		const byte* src = static_cast<byte*>(map());
		if (src)
		{
			m_bufferCopy = new byte[size];
			memcpy(m_bufferCopy, src, size);
			unmap();
		}

		unbind();
	}

	glDeleteBuffers(1, &m_vbo);
	m_vbo = 0;
}