#include "EditMeshUtility.h"
#include "Dataset/Mesh.h"
#include "Tools/Render.h"

using namespace FRUITS_ANIMATOR;

const float EditMeshUtility::NODE_RADIUS = 0.5f;

EditMeshUtility::EditMeshUtility(Mesh* mesh)
{
	m_mesh = mesh;
}

void EditMeshUtility::draw() const
{
	const std::vector<MeshTri*>& tris = m_mesh->getAllTris();
	for (size_t i = 0, n = tris.size(); i < n; ++i)
	{
		std::vector<MeshNode*> nodes;
		tris[i]->getNodes(nodes);

		glColor3f(0.0f, 1.0f, 0.0f);
		glBegin(GL_LINE_LOOP);
			glVertex2f(nodes[0]->projCoords.x, nodes[0]->projCoords.y);
			glVertex2f(nodes[1]->projCoords.x, nodes[1]->projCoords.y);
			glVertex2f(nodes[2]->projCoords.x, nodes[2]->projCoords.y);
		glEnd();

		glColor3f(1.0f, 0.0f, 0.0f);
		Render::drawPos(nodes[0]->projCoords, NODE_RADIUS);
		Render::drawPos(nodes[1]->projCoords, NODE_RADIUS);
		Render::drawPos(nodes[2]->projCoords, NODE_RADIUS);
	}
}

MeshNode* EditMeshUtility::selectNodeByPos(const f2Vec2& pos) const
{
	MeshNode* selected = NULL;
	float nearest = FLOAT_MAX;

	const std::vector<MeshTri*>& tris = m_mesh->getAllTris();
	for (size_t i = 0, n = tris.size(); i < n; ++i)
	{
		std::vector<MeshNode*> nodes;
		tris[i]->getNodes(nodes);
		for (size_t j = 0; j < 3; ++j)
		{
			float dis = f2Math::getDistance(pos, nodes[j]->projCoords);
			if (dis < nearest)
			{
				nearest = dis;
				selected = nodes[j];
			}
		}
	}

	if (nearest < NODE_RADIUS) return selected;
	else return NULL;
}