#ifndef _WX_GUI_VERTEX_BUFFER_OBJECT_H_
#define _WX_GUI_VERTEX_BUFFER_OBJECT_H_

#include "VertexBuffer.h"

namespace wxgui
{
	class VertexBufferObject : public VertexBuffer
	{
	public:
		VertexBufferObject(size_t size, int target, int usage);
		virtual ~VertexBufferObject();

		virtual void* map();
		virtual void unmap();

		virtual void bind();
		virtual void unbind();

		virtual void fill(size_t offset, size_t size, const void* data);

		virtual const void* getPointer(size_t offset) const ;

		bool loadVolatile();
		void unloadVolatile();

	private:
		bool load(bool restore);
		void unload(bool save);

	private:
		int m_vbo;

		void* m_mapped;

		byte* m_bufferCopy;

	}; // VertexBufferObject
}

#endif // _WX_GUI_VERTEX_BUFFER_OBJECT_H_