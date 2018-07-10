#ifndef _FRUITS_ANIMATOR_EDIT_MESH_UTILITY_H_
#define _FRUITS_ANIMATOR_EDIT_MESH_UTILITY_H_
#include <wxGUI/wxGUI.h>

namespace FRUITS_ANIMATOR
{
	class Mesh;
	class MeshNode;

	class EditMeshUtility
	{
	public:
		EditMeshUtility(Mesh* mesh);

	protected:
		static const float NODE_RADIUS;

	protected:
		void draw() const;

		MeshNode* selectNodeByPos(const f2Vec2& pos) const;

	protected:
		Mesh* m_mesh;

	}; // EditMeshUtility
}

#endif // _FRUITS_ANIMATOR_EDIT_MESH_UTILITY_H_