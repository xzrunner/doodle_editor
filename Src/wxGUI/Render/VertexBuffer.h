#ifndef _WX_GUI_VERTEX_BUFFER_H_
#define _WX_GUI_VERTEX_BUFFER_H_

#include <Fruits2D/Fruits2D.h>

namespace wxgui
{
	struct Vertex
	{
		unsigned char r, g, b, a;
		float x, y;
		float u, v;

		Vertex() : r(255), g(255), b(255), a(255) {}
	};

	class VertexBuffer
	{
	public:

		static VertexBuffer* create(size_t size, int target, int usage);

		virtual ~VertexBuffer() {}
	
		virtual void* map() = 0;
		virtual void unmap() = 0;

		virtual void bind() = 0; 
		virtual void unbind() = 0;

		virtual void fill(size_t offset, size_t size, const void* data) = 0;

		virtual const void* getPointer(size_t offset) const = 0;

		size_t getSize() const { return m_size; }
		int getTarget() const { return m_target; }
		int getUsage() const { return m_usage; }

	protected:
		VertexBuffer(size_t size, int target, int usage);

	private:
		size_t m_size;

		int m_target;

		int m_usage;

	}; // VertexBuffer
}

#endif // _WX_GUI_VERTEX_BUFFER_H_