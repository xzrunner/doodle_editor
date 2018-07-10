#include "BinaryTreeArrange.h"

using namespace deditor::automatic_merge;

BinaryTreeArrange::BinaryTreeArrange()
{
	m_root = NULL;
}

BinaryTreeArrange::~BinaryTreeArrange()
{
	delete m_root;
}

void BinaryTreeArrange::arrange(const std::vector<wxgui::ImageSprite*>& sprites, int width, int height)
{
	std::vector<wxgui::ImageSprite*> sorted(sprites);
	sortByMaxEdge(sorted);

	int maxArranged = -1, maxFlag = 0;

	int flag = 0;
	while (flag < REINSERT_MAX)
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

		if (i == n)
		{
			break;
		}
		else if (i > maxArranged)
		{
			maxArranged = i;
			maxFlag = flag - 1;
		}
	}

	if (flag >= REINSERT_MAX)
	{
		resetRoot(width, height);

		for (size_t i = 0, n = sorted.size(); i < n; ++i)
		{
			Node* result = m_root->insert(sorted[i], maxFlag);
			if (!result)
			{
				for (size_t j = i; j < n; ++j)
				{
					const wxgui::ImageSymbol& symbol = sorted[j]->getSymbol();
					sorted[j]->setTransform(f2Vec2(-SPACING - symbol.getWidth() * 0.5f, 
						-SPACING - symbol.getHeight() * 0.5f), 0);
				}
				break;
			}
		}
	}
}

void BinaryTreeArrange::resetRoot(int width, int height)
{
	delete m_root;
	m_root = new Node;
	m_root->rc.xMin = m_root->rc.yMin = 0;
	m_root->rc.xMax = width;
	m_root->rc.yMax = height;
}

BinaryTreeArrange::Node::Node()
{
	child[0] = child[1] = NULL;
	texture = NULL;
}

BinaryTreeArrange::Node::~Node()
{
	delete child[0];
	delete child[1];
}

BinaryTreeArrange::Node* 
BinaryTreeArrange::Node::insert(wxgui::ImageSprite* sprite, int flag)
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

		const float width = sprite->getSymbol().getWidth(),
			height = sprite->getSymbol().getHeight();
		if (width > rc.xLength() || height > rc.yLength()) return NULL;

		child[0] = new Node();
		child[1] = new Node();

		const float dw = rc.xLength() - width,
			dh = rc.yLength() - height;
		child[0]->rc = child[1]->rc = rc;
		if ((flag % 2 == 0) && dw > dh)
		{
			child[0]->rc.xMax = rc.xMin + width;
			child[1]->rc.xMin = rc.xMin + width;
		}
		else
		{
			child[0]->rc.yMax = rc.yMin + height;
			child[1]->rc.yMin = rc.yMin + height;
		}
		f2Vec2 center;
		center.x = child[0]->rc.xMin + width * 0.5f;
		center.y = child[0]->rc.yMin + height * 0.5f;
		sprite->setTransform(center, sprite->getAngle());

		if (child[0]->rc.xLength() > width)
		{
			child[0]->child[0] = new Node();
			child[0]->child[1] = new Node();

			child[0]->child[0]->rc = child[0]->child[1]->rc = child[0]->rc;
			child[0]->child[0]->rc.xMax = child[0]->rc.xMin + width;
			child[0]->child[1]->rc.xMin = child[0]->rc.xMin + width;

			child[0]->child[0]->texture = sprite;

			return child[0]->child[0];
		}
		else if (child[0]->rc.yLength() > height)
		{
			child[0]->child[0] = new Node();
			child[0]->child[1] = new Node();

			child[0]->child[0]->rc = child[0]->child[1]->rc = child[0]->rc;
			child[0]->child[0]->rc.yMax = child[0]->rc.yMin + height;
			child[0]->child[1]->rc.yMin = child[0]->rc.yMin + height;

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