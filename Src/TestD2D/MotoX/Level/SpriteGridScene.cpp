#include "SpriteGridScene.h"

using namespace motox;

void SpriteGridScene::updateGridRegionSingleLayer(const d2d::Vector& center, 
												  const SpriteGridLoader& loader, 
												  int& left, int& right)
{
	left = static_cast<int>((center.x - (d2d::SCREEN_WIDTH >> 1) - loader.m_leftmost) / loader.m_gridWidth);
	left = std::min(std::max(left, 0), (int) (loader.m_internal.size() - 1));

	right = static_cast<int>((center.x + (d2d::SCREEN_WIDTH >> 1) - loader.m_leftmost) / loader.m_gridWidth);
	right = std::max(std::min(right, (int) (loader.m_internal.size() - 1)), 0);

	assert(left <= right);

	combine(loader.m_internal, loader.m_intersect, left, right);
}

void SpriteGridScene::updateGridRegionMultiLayers(const d2d::Vector& center, 
												  const SpriteGridLoader& loader, 
												  int& left, int& right)
{
	int leftRaw = static_cast<int>((center.x - (d2d::SCREEN_WIDTH >> 1) - loader.m_leftmost) / loader.m_gridWidth);
	leftRaw = std::min(std::max(leftRaw, 0), (int) (loader.m_internals[0].size() - 1));

	int rightRaw = static_cast<int>((center.x + (d2d::SCREEN_WIDTH >> 1) - loader.m_leftmost) / loader.m_gridWidth);
	rightRaw = std::max(std::min(rightRaw, (int) (loader.m_internals[0].size() - 1)), 0);

	assert(leftRaw <= rightRaw);

	left = rightRaw;
	right = leftRaw;
	assert(loader.m_internals.size() == loader.m_intersects.size());
 	for (size_t i = 0, n = loader.m_internals.size(); i < n; ++i)
	{
		int l = leftRaw, r = rightRaw;
 		combine(loader.m_internals[i], loader.m_intersects[i], l, r);
		if (l < left) left = l;
		if (r > right) right = r;
	}
}

void SpriteGridScene::combine(const SpriteGridLoader::Grids& internal, 
							  const SpriteGridLoader::Grids& intersect, 
							  int& left, int& right)
{
	while (left < (int)(internal.size()))
	{
		if (internal[left].empty())
		{
			if (left < (int)(intersect.size()))
			{
				if (intersect[left].empty())
				{
					++left;
					if (left > right) break;
				}
				else
				{
					++left;
					break;
				}
			}
			else
			{
				++left;
				if (left > right) break;
			}
		}
		else
			break;
	}
	while (right >= 0)
	{
		if (internal[right].empty())
		{
			if (right > 0)
			{
				if (intersect[right - 1].empty())
				{
					--right;
					if (right < left) break;
				}
				else
				{
					--right;
					break;
				}
			}
			else
			{
				--right;
				if (right < left) break;
			}
		}
		else
			break;
	}
}
