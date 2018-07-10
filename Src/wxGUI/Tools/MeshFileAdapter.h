#ifndef _WX_GUI_MESH_FILE_ADAPTER_H_
#define _WX_GUI_MESH_FILE_ADAPTER_H_

#include "IFileAdapter.h"

#include <wx/wx.h>
#include <Fruits2D/Fruits2D.h>

namespace wxgui
{
	class MeshFileAdapter : public IFileAdapter
	{
	public:
		virtual void load(const char* filename);

	public:
		wxString m_imagePath;

		std::vector<f2Vec2> m_vertices;
		std::vector<f2Vec2> m_texCoords;

	}; // MeshFileAdapter
}

#endif // _WX_GUI_MESH_FILE_ADAPTER_H_