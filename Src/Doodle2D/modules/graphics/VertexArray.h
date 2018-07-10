#ifndef _D2D_VERTEX_ARRAY_H_
#define _D2D_VERTEX_ARRAY_H_

#include "VertexBuffer.h"

#include "common/types.h"

namespace d2d
{
	class VertexArray : public VertexBuffer
	{
	public:
		VertexArray(size_t size, GLenum target, GLenum usage);
		virtual ~VertexArray();
		
		virtual void* map();
		virtual void unmap();

		virtual void bind();
		virtual void unbind();

		virtual void fill(size_t offset, size_t size, const void* data);

		virtual const void* getPointer(size_t offset) const ;

	private:
		byte* m_data;

	}; // VertexArray
}

#endif // _D2D_VERTEX_ARRAY_H_