#ifndef _WX_GUI_VERTEX_ARRAY_H_
#define _WX_GUI_VERTEX_ARRAY_H_

#include "VertexBuffer.h"

namespace wxgui
{
	class VertexArray : public VertexBuffer
	{
	public:
		VertexArray(size_t size, int target, int usage);
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

#endif // _WX_GUI_VERTEX_ARRAY_H_