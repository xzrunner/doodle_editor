#include "VertexArray.h"

#include <string>

using namespace wxgui;

VertexArray::VertexArray(size_t size, int target, int usage)
	: VertexBuffer(size, target, usage)
{
	m_data = new byte[size];
}

VertexArray::~VertexArray()
{
	delete[] m_data;
}

void* VertexArray::map()
{
	return m_data;
}

void VertexArray::unmap()
{
}

void VertexArray::bind()
{
}

void VertexArray::unbind()
{
}

void VertexArray::fill(size_t offset, size_t size, const void* data)
{
	memcpy(m_data + offset, data, size);
}

const void* VertexArray::getPointer(size_t offset) const
{
	return m_data + offset;
}