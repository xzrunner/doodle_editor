#ifndef _D2D_VERTEX_BUFFER_H_
#define _D2D_VERTEX_BUFFER_H_

#include <GLES/gl.h>

namespace d2d
{
	class VertexBuffer
	{
	public:

		static VertexBuffer* create(size_t size, GLenum target, GLenum usage);

		virtual ~VertexBuffer() {}
	
		virtual void* map() = 0;
		virtual void unmap() = 0;

		virtual void bind() = 0;
		virtual void unbind() = 0;

		virtual void fill(size_t offset, size_t size, const void* data) = 0;

		virtual const void* getPointer(size_t offset) const = 0;

		size_t getSize() const { return m_size; }
		GLenum getTarget() const { return m_target; }
		GLenum getUsage() const { return m_usage; }

	protected:
		VertexBuffer(size_t size, GLenum target, GLenum usage);

	private:
		size_t m_size;

		GLenum m_target;

		GLenum m_usage;

	}; // VertexBuffer
}

#endif // _D2D_VERTEX_BUFFER_H_