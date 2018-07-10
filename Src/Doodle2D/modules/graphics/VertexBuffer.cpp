#include "VertexBuffer.h"
#include "VertexArray.h"
#include "VertexBufferObject.h"

#include "common/Exception.h"

using namespace d2d;

VertexBuffer* VertexBuffer::create(size_t size, GLenum target, GLenum usage)
{
 	try
 	{
 		return new VertexBufferObject(size, target, usage);
 	}
 	catch (const d2d::Exception &)
	{
		return new VertexArray(size, target, usage);
	}
}

VertexBuffer::VertexBuffer(size_t size, GLenum target, GLenum usage)
	: m_size(size)
	, m_target(target)
	, m_usage(usage)
{
}