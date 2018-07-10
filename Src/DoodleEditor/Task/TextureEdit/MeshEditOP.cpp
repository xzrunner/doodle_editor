#include "MeshEditOP.h"
#include "MeshCMPT.h"
#include "StagePanel.h"

using namespace deditor::texture_edit;

const float MeshEditOP::BOUNDING_REGION = 1.0f;

MeshEditOP::MeshEditOP(StagePanel* editPanel, MeshCMPT* cmpt)
	: wxgui::EditPolylineOP<wxgui::DrawPolygonEdgeOP, wxgui::SelectShapesOP, MeshCMPT>(editPanel, editPanel, cmpt)
{
}

bool MeshEditOP::onMouseLeftUp(int x, int y)
{
	if (EditPolylineOP<wxgui::DrawPolygonEdgeOP, wxgui::SelectShapesOP, MeshCMPT>::onMouseLeftUp(x, y)) 
		return true;

	fixedAllChainShapes();
	fetchAllBoundingPos();
	m_editPanel->Refresh();

	return false;
}

bool MeshEditOP::onDraw() const
{
	if (EditPolylineOP<wxgui::DrawPolygonEdgeOP, wxgui::SelectShapesOP, MeshCMPT>::onDraw()) 
		return true;

	if (m_bounding.empty()) 
		fetchAllBoundingPos();
	wxgui::PrimitiveDraw::drawCircles(m_bounding, BOUNDING_REGION, f2Colorf(0, 0, 1));

	return false;
}

bool MeshEditOP::clear()
{
	if (EditPolylineOP<wxgui::DrawPolygonEdgeOP, wxgui::SelectShapesOP, MeshCMPT>::onDraw()) 
		return true;

	m_bounding.clear();

	return false;
}

void MeshEditOP::fetchAllBoundingPos() const
{
	m_bounding.clear();

	StagePanel* editPanel = static_cast<StagePanel*>(m_editPanel);

	wxgui::Image* image = editPanel->getTexture();
	if (!image) return;

	const float hWidth = image->width() * 0.5f,
		hHeight = image->height() * 0.5f;

	std::vector<wxgui::ChainShape*> chains;
	editPanel->traverseShapes(FetchAllVisitor<wxgui::ChainShape>(chains));
	for (size_t i = 0, n = chains.size(); i < n; ++i)
	{
		const std::vector<f2Vec2>& vertices = chains[i]->getVertices();
		for (size_t j = 0, m = vertices.size(); j < m; ++j)
		{
			if (fabs(vertices[j].x) == hWidth
				|| fabs(vertices[j].y) == hHeight)
				m_bounding.push_back(vertices[j]);
		}
	}
}

void MeshEditOP::fixedAllChainShapes()
{
	StagePanel* editPanel = static_cast<StagePanel*>(m_editPanel);

	wxgui::Image* image = editPanel->getTexture();
	if (!image) return;

	const float hWidth = image->width() * 0.5f,
		hHeight = image->height() * 0.5f;

	std::vector<wxgui::ChainShape*> chains;
	editPanel->traverseShapes(FetchAllVisitor<wxgui::ChainShape>(chains));
	for (size_t i = 0, n = chains.size(); i < n; ++i)
	{
		const std::vector<f2Vec2>& vertices = chains[i]->getVertices();
		for (size_t j = 0, m = vertices.size(); j < m; ++j)
		{
			f2Vec2 fixed = vertices[j];
			bool bUpdate = false;

			if (fixed.x < 0)
			{
				if (fabs(fixed.x - (-hWidth)) < BOUNDING_REGION)
				{
					fixed.x = -hWidth;
					bUpdate = true;
				}
			}
			else
			{
				if (fabs(fixed.x - hWidth) < BOUNDING_REGION)
				{
					fixed.x = hWidth;
					bUpdate = true;
				}
			}

			if (fixed.y < 0)
			{
				if (fabs(fixed.y - (-hHeight)) < BOUNDING_REGION)
				{
					fixed.y = -hHeight;
					bUpdate = true;
				}
			}
			else
			{
				if (fabs(fixed.y - hHeight) < BOUNDING_REGION)
				{
					fixed.y = hHeight;
					bUpdate = true;
				}
			}

			if (bUpdate)
				chains[i]->changeVertices(vertices[j], fixed);
		}
	}
}