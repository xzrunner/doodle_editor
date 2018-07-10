#include "Utility.h"
#include "BoundsContainer.h"
#include "Dataset/ChainShape.h"
#include "Dataset/Sprite.h"
#include "File/LoopsFileAdapter.h"

using namespace FEDITOR;
using namespace FEDITOR::SKATER;

void Utility::addSpriteBound(Sprite* sprite, const BoundsContainer& m_bounds)
{
	if (sprite->getAllShapes().empty())
	{
		LoopsFileAdapter* adapter = m_bounds.query(sprite->getFilename());
		if (adapter)
		{
			for (size_t i = 0, n = adapter->m_loops.size(); i < n; ++i)
				sprite->pushShape(adapter->m_loops[i]->clone());
		}
	}
}