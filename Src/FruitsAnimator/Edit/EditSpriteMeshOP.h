#ifndef _FRUITS_ANIMATOR_EDIT_SPRITE_MESH_OP_H_
#define _FRUITS_ANIMATOR_EDIT_SPRITE_MESH_OP_H_

#include "EditMeshUtility.h"

#include <wxGUI/wxGUI.h>

namespace FRUITS_ANIMATOR
{
	class Mesh;
	class MeshNode;
	class MeshTri;

	class EditSpriteMeshOP : public wxgui::ZoomViewOP, private EditMeshUtility
	{
	public:
		EditSpriteMeshOP(wxgui::EditPanel* editPanel, Mesh* mesh);

		virtual bool onMouseLeftDown(int x, int y);
		virtual bool onMouseLeftUp(int x, int y);
		virtual bool onMouseDrag(int x, int y);

		virtual bool onDraw() const;
		virtual bool clear();

	private:
		MeshTri* selectTriByPos(const f2Vec2& pos) const;

	private:
		Mesh* m_mesh;

		MeshNode* m_selectedNode;
		MeshTri* m_selectedTri;

		f2Vec2 m_lastPos;

	}; // EditSpriteMeshOP
}

#endif // _FRUITS_ANIMATOR_EDIT_SPRITE_MESH_OP_H_