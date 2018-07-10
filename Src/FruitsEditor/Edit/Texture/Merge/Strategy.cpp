#include "Strategy.h"
#include "Dataset/Texture.h"
#include "Dataset/Sprite.h"

using namespace FEDITOR;
using namespace FEDITOR::TEXTURE_MERGE;

void Strategy::sortByArea(std::vector<Sprite*>& sprites, bool isDescend/* = true*/) const
{
	std::sort(sprites.begin(), sprites.end(), SpriteCmp(isDescend));
}

Strategy::SpriteCmp::SpriteCmp(bool isDescend)
{
	m_isDescend = isDescend;
}

bool Strategy::SpriteCmp::operator() (const Sprite* s0, const Sprite* s1) const
{
// 	const float a0 = s0->getBounding()->area(),
// 		a1 = s1->getBounding()->area();

	//const float a0 = s0->getBounding()->width() + s0->getBounding()->height(),
	//	a1 = s1->getBounding()->width() + s1->getBounding()->height();

	const float a0 = std::max(s0->getBounding()->width(), s0->getBounding()->height()),
		a1 = std::max(s1->getBounding()->width(), s1->getBounding()->height());

	if (m_isDescend) return a0 > a1;
	else return a0 <= a1;
}

//////////////////////////////////////////////////////////////////////////
// class DirectlyStrategy
//////////////////////////////////////////////////////////////////////////

void DirectlyStrategy::arrangeTextures(const std::vector<Sprite*>& sprites, int width, int height)
{
	std::vector<Sprite*> sorted(sprites);
	sortByArea(sorted);

	int sx = 0, sy = 0;
	int hMax = 0;
	for (size_t i = 0, n = sorted.size(); i < n; ++i)
	{
		Sprite* sprite = sorted[i];
		const float w = sprite->getTexture()->getWidth(),
			h = sprite->getTexture()->getHeight();

		if (sx + w <= width)
		{
			sprite->setTransform(f2Vec2(sx + w * 0.5f, sy + h * 0.5f), sprite->getAngle());

			sx += w;
			if (h > hMax)
				hMax = h;
		}
		else
		{
			sx = 0;
			sy += hMax;
			hMax = h;
			sprite->setTransform(f2Vec2(sx + w * 0.5f, sy + h * 0.5f), sprite->getAngle());
			sx = w;
		}
	}
}

//////////////////////////////////////////////////////////////////////////
// class BinaryTreeStrategy
//////////////////////////////////////////////////////////////////////////

BinaryTreeStrategy::BinaryTreeStrategy()
{
	m_root = NULL;
}

BinaryTreeStrategy::~BinaryTreeStrategy()
{
	delete m_root;
}

void BinaryTreeStrategy::arrangeTextures(const std::vector<Sprite*>& sprites, int width, int height)
{
	std::vector<Sprite*> sorted(sprites);
	sortByArea(sorted);

	int flag = 0;
	while (flag < 128)
	{
		resetRoot(width, height);

		size_t i = 0, n = sorted.size();
		for ( ; i < n; ++i)
		{
			Node* result = m_root->insert(sorted[i], flag);
			if (!result)
			{
				++flag;
				break;
			}
		}

		if (i == n) break;
	}
}

void BinaryTreeStrategy::resetRoot(int width, int height)
{
	delete m_root;
	m_root = new Node;
	m_root->rc.xMin = m_root->rc.yMin = 0;
	m_root->rc.xMax = width;
	m_root->rc.yMax = height;
}

BinaryTreeStrategy::Node::Node()
{
	child[0] = child[1] = NULL;
	texture = NULL;
}

BinaryTreeStrategy::Node::~Node()
{
	delete child[0];
	delete child[1];
}

BinaryTreeStrategy::Node* BinaryTreeStrategy::Node::insert(Sprite* sprite, int flag)
{
	if (child[0])
	{
		Node* newNode = child[0]->insert(sprite, flag / 2);
		if (newNode) return newNode;
		return child[1]->insert(sprite, flag / 4);
	}
	else
	{
		if (texture) return NULL;

		const float w = sprite->getTexture()->getWidth(),
			h = sprite->getTexture()->getHeight();
		if (w > rc.xLength() || h > rc.yLength()) return NULL;

		child[0] = new Node();
		child[1] = new Node();

		const float dw = rc.xLength() - w,
			dh = rc.yLength() - h;
		child[0]->rc = child[1]->rc = rc;
		if ((flag % 2 == 0) && dw > dh)
		{
			child[0]->rc.xMax = rc.xMin + w;
			child[1]->rc.xMin = rc.xMin + w;
		}
		else
		{
			child[0]->rc.yMax = rc.yMin + h;
			child[1]->rc.yMin = rc.yMin + h;
		}
		f2Vec2 center;
		center.x = child[0]->rc.xMin + w * 0.5f;
		center.y = child[0]->rc.yMin + h * 0.5f;
		sprite->setTransform(center, sprite->getAngle());

		if (child[0]->rc.xLength() > w)
		{
			child[0]->child[0] = new Node();
			child[0]->child[1] = new Node();

			child[0]->child[0]->rc = child[0]->child[1]->rc = child[0]->rc;
			child[0]->child[0]->rc.xMax = child[0]->rc.xMin + w;
			child[0]->child[1]->rc.xMin = child[0]->rc.xMin + w;

			child[0]->child[0]->texture = sprite;

			return child[0]->child[0];
		}
		else if (child[0]->rc.yLength() > h)
		{
			child[0]->child[0] = new Node();
			child[0]->child[1] = new Node();

			child[0]->child[0]->rc = child[0]->child[1]->rc = child[0]->rc;
			child[0]->child[0]->rc.yMax = child[0]->rc.yMin + h;
			child[0]->child[1]->rc.yMin = child[0]->rc.yMin + h;

			child[0]->child[0]->texture = sprite;

			return child[0]->child[0];
		}
		else
		{
			child[0]->texture = sprite;
			return child[0];
		}
	}
}