#include "EditMeshNodeOP.h"
#include "Dataset/Mesh.h"

using namespace FRUITS_ANIMATOR;

EditMeshNodeOP::EditMeshNodeOP(wxgui::EditPanel* editPanel, Mesh* mesh)
	: wxgui::ZoomViewOP(editPanel, false), EditMeshUtility(mesh)
{
	m_mesh = mesh;
	m_selected = NULL;
}

bool EditMeshNodeOP::onMouseLeftDown(int x, int y)
{
	if (ZoomViewOP::onMouseLeftDown(x, y)) return true;

	f2Vec2 pos = m_editPanel->transPosScreenToProject(x, y);
	MeshNode* selected = selectNodeByPos(pos);
	if (selected)
	{
		m_firstPos = selected->projCoords;
		m_selected = selected;
	}
	else
	{
		m_mesh->insertNode(pos);
		m_editPanel->Refresh();
	}

	return false;
}

bool EditMeshNodeOP::onMouseLeftUp(int x, int y)
{
	if (ZoomViewOP::onMouseLeftUp(x, y)) return true;

	if (m_selected)
	{
		f2Vec2 pos = m_editPanel->transPosScreenToProject(x, y);
		m_mesh->deleteNode(m_firstPos);
		m_mesh->insertNode(pos);
		m_selected = NULL;
		m_editPanel->Refresh();
	}

	return false;
}

bool EditMeshNodeOP::onMouseRightDown(int x, int y)
{
	if (ZoomViewOP::onMouseRightDown(x, y)) return true;

	const std::vector<MeshTri*>& tris = m_mesh->getAllTris();
	if (tris.size() <= 1) return false;

	f2Vec2 pos = m_editPanel->transPosScreenToProject(x, y);
	MeshNode* selected = selectNodeByPos(pos);
	if (selected)
	{
		m_mesh->deleteNode(selected->projCoords);
		m_editPanel->Refresh();
	}

	return false;
}

bool EditMeshNodeOP::onMouseDrag(int x, int y)
{
	if (ZoomViewOP::onMouseDrag(x, y)) return true;

	if (m_selected)
	{
		m_selected->projCoords = m_editPanel->transPosScreenToProject(x, y);
		m_editPanel->Refresh();
	}

	return false;
}

bool EditMeshNodeOP::onDraw() const
{
	if (ZoomViewOP::onDraw()) return true;

	draw();

	return false;
}

bool EditMeshNodeOP::clear()
{
	if (ZoomViewOP::clear()) return true;

	m_firstPos.setInvalid();
	m_selected = NULL;

	return false;
}