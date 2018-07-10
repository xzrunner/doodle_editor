#ifndef _FRUITS_ANIMATOR_EDIT_MESH_NODE_OP_H_
#define _FRUITS_ANIMATOR_EDIT_MESH_NODE_OP_H_

#include "EditMeshUtility.h"

#include <wxGUI/wxGUI.h>

namespace FRUITS_ANIMATOR
{
	class Mesh;
	class MeshNode;

	class EditMeshNodeOP : public wxgui::ZoomViewOP, private EditMeshUtility
	{
	public:
		EditMeshNodeOP(wxgui::EditPanel* editPanel, Mesh* mesh);

		virtual bool onMouseLeftDown(int x, int y);
		virtual bool onMouseLeftUp(int x, int y);
		virtual bool onMouseRightDown(int x, int y);
		virtual bool onMouseDrag(int x, int y);
		
		virtual bool onDraw() const;
		virtual bool clear();

	private:
		Mesh* m_mesh;

		f2Vec2 m_firstPos;
		MeshNode* m_selected;

	}; // EditMeshNodeOP
}

#endif // _FRUITS_ANIMATOR_EDIT_MESH_NODE_OP_H_