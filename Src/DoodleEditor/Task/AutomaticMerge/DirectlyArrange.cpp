#include "DirectlyArrange.h"

using namespace deditor::automatic_merge;

void DirectlyArrange::arrange(const std::vector<wxgui::ImageSprite*>& sprites, 
							  int totWidth, int totHeight)
{
	std::vector<wxgui::ImageSprite*> sorted(sprites);
	sortByArea(sorted);

	int sx = 0, sy = 0;
	int hMax = 0;
	for (size_t i = 0, n = sorted.size(); i < n; ++i)
	{
		wxgui::ImageSprite* sprite = sorted[i];
		const float width = sprite->getSymbol().getWidth(),
			height = sprite->getSymbol().getHeight();

		if (sx + width <= totWidth)
		{
			sprite->setTransform(f2Vec2(sx + width * 0.5f, sy + height * 0.5f), sprite->getAngle());

			sx += width;
			if (height > hMax)
				hMax = height;
		}
		else
		{
			sx = 0;
			sy += hMax;
			hMax = height;
			sprite->setTransform(f2Vec2(sx + width * 0.5f, sy + height * 0.5f), sprite->getAngle());
			sx = width;
		}
	}
}