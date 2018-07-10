#include "ShapeEditOP.h"
#include "ShapeEditCMPT.h"
#include "StagePanel.h"

using namespace deditor::combination;

ShapeEditOP::ShapeEditOP(StagePanel* editPanel, ShapeEditCMPT* cmpt)
	: EditPolylineOP<DrawPolygonEdgeOP, wxgui::SelectShapesOP, ShapeEditCMPT>(editPanel, editPanel, cmpt)
//	, m_cmpt(cmpt)
{
}
//
//bool ShapeEditOP::onMouseLeftDown(int x, int y)
//{
//	if (!m_cmpt->isBorderExtractState())
//		return EditPolylineOP<DrawPolygonEdgeOP, wxgui::SelectShapesOP>::onMouseLeftDown(x, y);
//
//// 	f2Vec2 pos = m_editPanel->transPosScreenToProject(x, y);
//// 	wxgui::RawPixels* pixelsData = m_cmpt->getPixelsData();
//// 	int width, height;
//// 	pixelsData->getSize(width, height);
//// 	if (fabs(pos.x) < width * 0.5f && fabs(pos.y) < height * 0.5f)
//// 	{
//// 		buildBorder(pos);
//// 		buildLoops(width, height);
//// 
//// 		m_editPanel->Refresh();
//// 	}
//
//	return false;
//}
//
//bool ShapeEditOP::onDraw() const
//{
//	if (EditPolylineOP<DrawPolygonEdgeOP, wxgui::SelectShapesOP>::onDraw())
//		return true;
//
//	if (!m_border.empty())
//		wxgui::Render::drawPoints(m_border, f2Colorf(1, 0, 0));
//	for (size_t i = 0, n = m_loopsRaw.size(); i < n; ++i)
//		wxgui::Render::drawPolyline(m_loopsRaw[i], f2Colorf(0, 1, 0), true);
//	for (size_t i = 0, n = m_loopsSimplified.size(); i < n; ++i)
//		wxgui::Render::drawPolyline(m_loopsSimplified[i], f2Colorf(0, 0, 1), true);
//
//	return false;
//}
//
//bool ShapeEditOP::clear()
//{
//	if (EditPolylineOP<DrawPolygonEdgeOP, wxgui::SelectShapesOP>::clear())
//		return true;
//
//	m_border.clear();
//	m_loopsRaw.clear();
//	m_loopsSimplified.clear();
//
//	return false;
//}
//
//void ShapeEditOP::buildBorder(const f2Vec2& pos)
//{
//	m_border.clear();
//
//	wxgui::RawPixels* pixelsData = m_cmpt->getPixelsData();
//	int width, height, channels;
//	pixelsData->getSize(width, height);
//	channels = pixelsData->getChannels();
//
//	const unsigned char* imgData = pixelsData->getPixelData();
//
//	const float hWidth = width * 0.5f,
//		hHeight = height * 0.5f;
//
//	int px, py;
//	px = static_cast<int>(pos.x + hWidth);
//	py = static_cast<int>(height - (pos.y + hHeight));
//
//	std::vector<bool> visited(width * height, false);
//
//	const int ptr = width * channels * py + px * channels;
//	const float sr = imgData[ptr], 
//		sg = imgData[ptr + 1], 
//		sb = imgData[ptr + 2];
//
//	std::queue<f2Vec2> buffer;
//	buffer.push(f2Vec2(px, py));
//	while (!buffer.empty())
//	{
//		f2Vec2 curr = buffer.front(); buffer.pop();
//		const int ptrPix = static_cast<int>(curr.y * width + curr.x);
//		if (!visited[ptrPix])
//		{
//			visited[ptrPix] = true;
//
//			const int ptr = ptrPix * channels;
//			const float r = imgData[ptr], 
//				g = imgData[ptr + 1], 
//				b = imgData[ptr + 2],
//				a = imgData[ptr + 3];
//
//			const float dis = sqrt((sr - r) * (sr - r) + (sg - g) * (sg - g) + (sb - b) * (sb - b));
//		//	if (dis < 10)
//			if (a != 0)
//			{
//				if (curr.x - 1 >= 0 && curr.x - 1 < width) buffer.push(f2Vec2(curr.x - 1, curr.y));
//				if (curr.x + 1 >= 0 && curr.x + 1 < width) buffer.push(f2Vec2(curr.x + 1, curr.y));
//				if (curr.y - 1 >= 0 && curr.y - 1 < height) buffer.push(f2Vec2(curr.x, curr.y - 1));
//				if (curr.y + 1 >= 0 && curr.y + 1 < height) buffer.push(f2Vec2(curr.x, curr.y + 1));
//
//				if (curr.x - 1 < 0 || curr.x - 1 >= width || 
//					curr.x + 1 < 0 || curr.x + 1 >= width || 
//					curr.y - 1 < 0 || curr.y - 1 >= height ||
//					curr.y + 1 < 0 || curr.y + 1 >= height)
//				{
//					//m_border.push_back(f2Vec2(curr.x + 0.5f, height - curr.y - 0.5f));
//					m_border.push_back(f2Vec2(curr.x - hWidth, height - curr.y - hHeight));
//				}
//			}
// 			else
// 			{
// 				//m_border.push_back(f2Vec2(curr.x + 0.5f, height - curr.y - 0.5f));
// 				m_border.push_back(f2Vec2(curr.x - hWidth, height - curr.y - hHeight));
// 			}
//		}
//	}
//}
//
//void ShapeEditOP::buildLoops(int width, int height)
//{
//	m_loopsRaw.clear();
//
//	std::sort(m_border.begin(), m_border.end(), PosCmp());
//
//	std::vector<bool> visited(m_border.size(), false);
//	for (size_t i = 0, n = m_border.size(); i < n; ++i)
//	{
//		if (visited[i]) continue;
//
//		std::vector<f2Vec2> loop;
//		visited[i] = true;
//		loop.push_back(m_border[i]);
//
//		f2Vec2 prev = m_border[i];
//		while (true)
//		{
//			if (createLoopByExtend(visited, loop, prev, f2Vec2(prev.x - 1, prev.y + 1), width, height)) continue;
//			if (createLoopByExtend(visited, loop, prev, f2Vec2(prev.x    , prev.y + 1), width, height)) continue;
//			if (createLoopByExtend(visited, loop, prev, f2Vec2(prev.x + 1, prev.y + 1), width, height)) continue;
//			if (createLoopByExtend(visited, loop, prev, f2Vec2(prev.x - 1, prev.y    ), width, height)) continue;
//			if (createLoopByExtend(visited, loop, prev, f2Vec2(prev.x + 1, prev.y    ), width, height)) continue;
//			if (createLoopByExtend(visited, loop, prev, f2Vec2(prev.x - 1, prev.y - 1), width, height)) continue;
//			if (createLoopByExtend(visited, loop, prev, f2Vec2(prev.x    , prev.y - 1), width, height)) continue;
//			if (createLoopByExtend(visited, loop, prev, f2Vec2(prev.x + 1, prev.y - 1), width, height)) continue;
//
//			break;
//		}
//
//		m_loopsRaw.push_back(loop);
//	}
//
//	simplifyBoundaries();
//}
//
//bool ShapeEditOP::createLoopByExtend(std::vector<bool>& visited, std::vector<f2Vec2>& loop, 
//									 f2Vec2& prev, const f2Vec2& next, int width, int height) const
//{
//	if (next.x >= 0 && next.x < width &&
//		next.y >= 0 && next.y < height)
//	{
//		std::vector<f2Vec2>::const_iterator itr = std::find(m_border.begin(), m_border.end(), next);
//		if (itr != m_border.end() && !visited[itr - m_border.begin()])
//		{
//			visited[itr - m_border.begin()] = true;
//			loop.push_back(*itr);
//			prev = *itr;
//			return true;
//		}
//	}
//
//	return false;
//}
//
//void ShapeEditOP::simplifyBoundaries()
//{
//	m_loopsSimplified.clear();
//
//	for (size_t i = 0, n = m_loopsRaw.size(); i < n; ++i)
//	{
//		if (m_loopsRaw[i].size() <= 2) continue;
//
//		std::vector<f2Vec2> loop;
//		DouglasPeucker::implement(m_loopsRaw[i], 10, loop);
//		m_loopsSimplified.push_back(loop);
//	}
//}
