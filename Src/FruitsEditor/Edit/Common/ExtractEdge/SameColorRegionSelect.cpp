#include "SameColorRegionSelect.h"
#include "Blackboard.h"
#include "Dataset/Texture.h"
#include "Dataset/Sprite.h"
#include "Dataset/PointShape.h"
#include "Dataset/ChainShape.h"
#include "Dataset/Layer.h"
#include "SOIL/SOIL.h"

using namespace FEDITOR;
using namespace FEDITOR::EXTRACT_EDGE;

SameColorRegionSelect::SameColorRegionSelect(const Blackboard* blackboard, const Texture& texture)
	: m_texture(texture)
{
	m_blackboard = blackboard;

	int w, h, c;
	m_pixelData = SOIL_load_image(texture.getFilename().c_str(), &w, &h, &c, 0);

	m_cacheLastPos.setInvalid();
}

void SameColorRegionSelect::selectByPos()
{
	if (!m_cacheLastPos.isValid()) return;
	selectByPos(m_cacheLastPos);
}

void SameColorRegionSelect::selectByPos(const f2Vec2& p)
{
	if (fabs(p.x) > m_texture.getWidth() * 0.5f ||
		fabs(p.y) > m_texture.getHeight() * 0.5f)
		return;

	m_cacheLastPos = p;

	buildSameColorPixelData();
	buildSameColorBoundaryData();
}

void SameColorRegionSelect::simplifyBoundaries()
{
	m_midBoundaries.simplified.clear();

	for (size_t i = 0, n = m_midBoundaries.rough.size(); i < n; ++i)
	{
		if (m_midBoundaries.rough[i].size() <= 2) continue;

		std::vector<f2Vec2> loop;
		DouglasPeucker::implement(m_midBoundaries.rough[i], m_blackboard->m_edgeTolerance, loop);
		m_midBoundaries.simplified.push_back(loop);
	}
}

void SameColorRegionSelect::addDataToLayer(Layer* layer) const
{
	const f2Vec2 offset(- m_texture.getWidth() * 0.5f, - m_texture.getHeight() * 0.5f);

	for (size_t i = 0, n = m_midPixels.boundary.size(); i < n; ++i)
	{
		Sprite* sprite = new Sprite;
		sprite->setTransform(offset, 0);
		PointShape* shape = new PointShape;
		shape->m_pos = m_midPixels.boundary[i];
		sprite->pushShape(shape);
		layer->addSprite(sprite);
	}
	for (size_t i = 0, n = m_midBoundaries.simplified.size(); i < n; ++i)
	{
		Sprite* sprite = new Sprite;
		sprite->setTransform(offset, 0);
		ChainShape* shape = new ChainShape(m_midBoundaries.simplified[i], false);
		sprite->pushShape(shape);
		layer->addSprite(sprite);
	}
}

void SameColorRegionSelect::buildSameColorPixelData()
{
	m_midPixels.clear();

	const int width = static_cast<int>(m_texture.getWidth()),
		height = static_cast<int>(m_texture.getHeight());

	int px, py;
	px = static_cast<int>(m_cacheLastPos.x + width * 0.5f);
	py = static_cast<int>(height - (m_cacheLastPos.y + height * 0.5f));

	std::vector<bool> visited(width * height, false);

	const int ptr = width * 3 * py + px * 3;
	const float sr = m_pixelData[ptr], 
		sg = m_pixelData[ptr + 1], 
		sb = m_pixelData[ptr + 2];

	std::queue<f2Vec2> buffer;
	buffer.push(f2Vec2(px, py));
	while (!buffer.empty())
	{
		f2Vec2 curr = buffer.front(); buffer.pop();
		const int ptrPix = static_cast<int>(curr.y * width + curr.x);
		if (!visited[ptrPix])
		{
			visited[ptrPix] = true;

			const int ptr = ptrPix * 3;
			const float r = m_pixelData[ptr], 
				g = m_pixelData[ptr + 1], 
				b = m_pixelData[ptr + 2];

			const float dis = sqrt((sr - r) * (sr - r) + (sg - g) * (sg - g) + (sb - b) * (sb - b));
			if (dis < m_blackboard->m_colorTolerance)
			{
				//m_midPixels.inner.push_back(f2Vec2(curr.x + 0.5f, height - curr.y - 0.5f));
				m_midPixels.inner.push_back(f2Vec2(curr.x, height - curr.y));
				if (curr.x - 1 >= 0 && curr.x - 1 < width) buffer.push(f2Vec2(curr.x - 1, curr.y));
				if (curr.x + 1 >= 0 && curr.x + 1 < width) buffer.push(f2Vec2(curr.x + 1, curr.y));
				if (curr.y - 1 >= 0 && curr.y - 1 < height) buffer.push(f2Vec2(curr.x, curr.y - 1));
				if (curr.y + 1 >= 0 && curr.y + 1 < height) buffer.push(f2Vec2(curr.x, curr.y + 1));

				if (curr.x - 1 < 0 || curr.x - 1 >= width || 
					curr.x + 1 < 0 || curr.x + 1 >= width || 
					curr.y - 1 < 0 || curr.y - 1 >= height ||
					curr.y + 1 < 0 || curr.y + 1 >= height)
				{
					//m_midPixels.boundary.push_back(f2Vec2(curr.x + 0.5f, height - curr.y - 0.5f));
					m_midPixels.boundary.push_back(f2Vec2(curr.x, height - curr.y));
				}
			}
			else
			{
				//m_midPixels.boundary.push_back(f2Vec2(curr.x + 0.5f, height - curr.y - 0.5f));
				m_midPixels.boundary.push_back(f2Vec2(curr.x, height - curr.y));
			}
		}
	}
}

void SameColorRegionSelect::buildSameColorBoundaryData()
{
	m_midBoundaries.clear();

	std::sort(m_midPixels.boundary.begin(), m_midPixels.boundary.end(), PosCmp());

	std::vector<bool> visited(m_midPixels.boundary.size(), false);
	for (size_t i = 0, n = m_midPixels.boundary.size(); i < n; ++i)
	{
		if (visited[i]) continue;

		std::vector<f2Vec2> loop;
		visited[i] = true;
		loop.push_back(m_midPixels.boundary[i]);

		f2Vec2 prev = m_midPixels.boundary[i];
		while (true)
		{
			if (createLoopByExtend(visited, loop, prev, f2Vec2(prev.x - 1, prev.y + 1))) continue;
			if (createLoopByExtend(visited, loop, prev, f2Vec2(prev.x    , prev.y + 1))) continue;
			if (createLoopByExtend(visited, loop, prev, f2Vec2(prev.x + 1, prev.y + 1))) continue;
			if (createLoopByExtend(visited, loop, prev, f2Vec2(prev.x - 1, prev.y    ))) continue;
			if (createLoopByExtend(visited, loop, prev, f2Vec2(prev.x + 1, prev.y    ))) continue;
			if (createLoopByExtend(visited, loop, prev, f2Vec2(prev.x - 1, prev.y - 1))) continue;
			if (createLoopByExtend(visited, loop, prev, f2Vec2(prev.x    , prev.y - 1))) continue;
			if (createLoopByExtend(visited, loop, prev, f2Vec2(prev.x + 1, prev.y - 1))) continue;

			break;
		}

		m_midBoundaries.rough.push_back(loop);
	}

	simplifyBoundaries();
}

bool SameColorRegionSelect::createLoopByExtend(std::vector<bool>& visited, std::vector<f2Vec2>& loop, 
											   f2Vec2& prev, const f2Vec2& next) const
{
	if (next.x >= 0 && next.x < m_texture.getWidth() &&
		next.y >= 0 && next.y < m_texture.getHeight())
	{
		std::vector<f2Vec2>::const_iterator itr = std::find(m_midPixels.boundary.begin(), m_midPixels.boundary.end(), next);
		if (itr != m_midPixels.boundary.end() && !visited[itr - m_midPixels.boundary.begin()])
		{
			visited[itr - m_midPixels.boundary.begin()] = true;
			loop.push_back(*itr);
			prev = *itr;
			return true;
		}
	}

	return false;
}

void SameColorRegionSelect::SameColorPixel::clear()
{
	inner.clear();
	boundary.clear();
}

void SameColorRegionSelect::SameColorBoundary::clear()
{
	rough.clear();
	simplified.clear();
}