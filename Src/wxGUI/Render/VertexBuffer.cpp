#include "VertexBuffer.h"
#include "VertexArray.h"
#include "VertexBufferObject.h"

#include "Exception.h"

using namespace wxgui;

VertexBuffer* VertexBuffer::create(size_t size, int target, int usage)
{
 	try
 	{
 		return new VertexBufferObject(size, target, usage);
 	}
 	catch (const wxgui::Exception &)
	{
		return new VertexArray(size, target, usage);
	}
}

VertexBuffer::VertexBuffer(size_t size, int target, int usage)
	: m_size(size)
	, m_target(target)
	, m_usage(usage)
{
}