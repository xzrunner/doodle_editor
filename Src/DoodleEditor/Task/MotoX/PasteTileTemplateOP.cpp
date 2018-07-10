#include "PasteTileTemplateOP.h"
#include "PasteTileTemplateCMPT.h"
#include "StagePanel.h"
#include "LibraryTemplateItem.h"
#include "LibraryTemplateList.h"
#include "TrackChain.h"

using namespace deditor::motox;

const f2Vec2 PasteTileTemplateOP::INVALID_POS = f2Vec2(-(float)0xffff, -(float)0xffff);

PasteTileTemplateOP::PasteTileTemplateOP(StagePanel* stagePanel, 
										 wxgui::LibraryPanel* libraryPanel,
										 PasteTileTemplateCMPT* cmpt)
	: ZoomViewOP(stagePanel, true)
	, m_stagePanel(stagePanel)
	, m_libraryPanel(libraryPanel)
	, m_cmpt(cmpt)
	, m_lastSelected(NULL)
{
}

bool PasteTileTemplateOP::onMouseLeftDown(int x, int y)
{
	if (ZoomViewOP::onMouseLeftDown(x, y)) return true;

	for (size_t i = 0, n = m_sprites.size(); i < n; ++i)
	{
		if (!isPosInvalid(m_sprites[i]->getPosition()))
		{
			wxgui::ISprite* copy = m_sprites[i]->clone();
			m_stagePanel->insertSprite(copy);
			copy->release();
		}
	}

	if (m_cmpt->isIndexRamdomOpen())
	{
		LibraryTemplateItem* random = randomTemplate();
		if (random != m_lastSelected)
		{
			initSpritesFromBatch(*random);
			m_lastSelected = random;
		}
	}

	return false;
}

bool PasteTileTemplateOP::onMouseRightDown(int x, int y)
{
	if (ZoomViewOP::onMouseRightDown(x, y)) return true;

	if (m_cmpt->isIndexRamdomOpen())
	{
		LibraryTemplateItem* random = randomTemplate();
		if (random != m_lastSelected)
		{
			initSpritesFromBatch(*random);
			m_lastSelected = random;
			m_editPanel->Refresh();
		}
	}

	return false;
}

bool PasteTileTemplateOP::onMouseMove(int x, int y)
{
	if (ZoomViewOP::onMouseMove(x, y)) return true;

	LibraryTemplateItem* batch = NULL;
	if (m_cmpt->isIndexRamdomOpen())
	{
		if (!m_lastSelected)
		{
			LibraryTemplateItem* random = randomTemplate();
			initSpritesFromBatch(*random);
			m_lastSelected = random;
		}
		batch = m_lastSelected;
	}
	else
	{
		batch = dynamic_cast<LibraryTemplateItem*>(m_libraryPanel->getSymbol());
		if (!batch) 
			return false;

		if (m_sprites.empty() || m_lastSelected != batch || batch->m_sprites.size() != m_sprites.size())
		{
			initSpritesFromBatch(*batch);
			m_lastSelected = batch;
		}
	}
	
	computeSpritesPosition(*batch, m_editPanel->transPosScreenToProject(x, y));

	m_editPanel->Refresh();

	return false;
}

bool PasteTileTemplateOP::onDraw() const
{
	if (ZoomViewOP::onDraw()) return true;

	for (size_t i = 0, n = m_sprites.size(); i < n; ++i)
	{
		if (!isPosInvalid(m_sprites[i]->getPosition()))
			wxgui::SpriteDraw::drawSprite(m_sprites[i]);
	}

	return false;
}

bool PasteTileTemplateOP::clear()
{
	if (ZoomViewOP::clear()) return true;

	m_lastSelected = NULL;

	for_each(m_sprites.begin(), m_sprites.end(), DeletePointerFunctor<wxgui::ISprite>());
	m_sprites.clear();

	return false;
}

void PasteTileTemplateOP::initSpritesFromBatch(const LibraryTemplateItem& batch)
{
	for (size_t i = 0, n = m_sprites.size(); i < n; ++i)
		m_sprites[i]->release();
	m_sprites.clear();

	m_sprites.reserve(batch.m_sprites.size());
	for (size_t i = 0, n = batch.m_sprites.size(); i < n; ++i)
	{
		wxgui::ISprite* copy = batch.m_sprites[i]->clone();
		copy->setTransform(INVALID_POS, 0);
		m_sprites.push_back(copy);
	}
}

void PasteTileTemplateOP::computeSpritesPosition(const LibraryTemplateItem& batch, 
												 const f2Vec2& center)
{
	assert(batch.m_sprites.size() == m_sprites.size());

	const std::vector<TrackChain*>& chains = m_stagePanel->getTrackChains();

	std::vector<f2Vec2> dstLine;
	for (size_t i = 0, n = chains.size(); i < n; ++i)
	{
		wxgui::ChainShape* chain = chains[i];
		const f2AABB& aabb = chain->getAABB();
		if (center.x > aabb.xMin && center.x < aabb.xMax)
		{
			dstLine = chain->getVertices();
			break;
		}
	}

	if (dstLine.empty())
	{
		for (size_t i = 0, n = m_sprites.size(); i < n; ++i)
		{
			f2Vec2 pos = center + (batch.m_sprites[i]->getPosition() - batch.m_center);
			m_sprites[i]->setTransform(pos, batch.m_sprites[i]->getAngle());
		}
	}
	else
	{
		if (dstLine.back().x < dstLine.front().x)
			reverse(dstLine.begin(), dstLine.end());

		f2Vec2 startPos;
		int iBaseForward = -1, iBaseBackward = -1;
		float disForward, disBackward;
		for (size_t i = 0, n = dstLine.size() - 1; i < n; ++i)
		{
			if (center.x >= dstLine[i].x && center.x <= dstLine[i + 1].x)
			{
				startPos.x = center.x;
				startPos.y = f2Math::findYOnSeg(dstLine[i], dstLine[i+1], startPos.x);

				iBaseForward = i+1;
				iBaseBackward = i;
				disForward = f2Math::getDistance(center, dstLine[i+1]);
				disBackward = f2Math::getDistance(center, dstLine[i]);
				
				break;
			}
		}

		for (size_t i = 0, n = batch.m_sprites.size(); i < n; ++i)
		{
			const f2Vec2& ori = batch.m_sprites[i]->getPosition();
			if ((ori.x > 0 && fabs(ori.x) <= disForward)
				|| (ori.x < 0 && fabs(ori.x) <= disBackward))
			{
				if (ori.x > 0)
					fixedSpritePosition(*batch.m_sprites[i], *m_sprites[i], startPos, dstLine[iBaseForward], 0, disForward);
				else
					fixedSpritePosition(*batch.m_sprites[i], *m_sprites[i], startPos, dstLine[iBaseBackward], 0, disBackward);
			}
			else
			{
				if (ori.x > 0)
				{
		 			int iStart = iBaseForward, 
		 				iEnd = iBaseForward + 1;
					float currDis = disForward;
					while (iEnd < dstLine.size())
					{
						float dis = f2Math::getDistance(dstLine[iStart], dstLine[iEnd]);
						if (currDis + dis > fabs(ori.x))
						{
							fixedSpritePosition(*batch.m_sprites[i], *m_sprites[i], dstLine[iStart], dstLine[iEnd], currDis, dis);
							break;
						}
						else
						{
							currDis += dis;
							++iStart;
							++iEnd;
						}
					}

					if (iEnd >= dstLine.size())
					{
						m_sprites[i]->setTransform(INVALID_POS, 0);
					}
				}
				else
				{
					int iStart = iBaseBackward, 
						iEnd = iBaseBackward - 1;
					float currDis = disBackward;
					while (iEnd >= 0)
					{
						float dis = f2Math::getDistance(dstLine[iStart], dstLine[iEnd]);
						if (currDis + dis > fabs(ori.x))
						{
							fixedSpritePosition(*batch.m_sprites[i], *m_sprites[i], dstLine[iStart], dstLine[iEnd], currDis, dis);
							break;
						}
						else
						{
							currDis += dis;
							--iStart;
							--iEnd;
						}
					}

					if (iEnd < 0)
					{
						m_sprites[i]->setTransform(INVALID_POS, 0);
					}
				}
			}
		}

		for (size_t i = 0, n = m_sprites.size(); i < n; ++i)
		{
			wxgui::ISprite* sprite = m_sprites[i];
			const f2Vec2& pos = sprite->getPosition();
			if (!isPosInvalid(pos))
			{
				f2Vec2 fixed(pos.x, pos.y + (center.y - startPos.y));
				sprite->setTransform(fixed, sprite->getAngle());
			}
		}
	}
}

void PasteTileTemplateOP::fixedSpritePosition(const wxgui::ISprite& src, wxgui::ISprite& dst, 
											  const f2Vec2& start, const f2Vec2& end, float currDis, float totDis)
{
	const f2Vec2& ori = src.getPosition();

	const f2Vec2 foot = start + (end - start) * (fabs(ori.x) - currDis) / totDis;

	f2Vec2 dir = end - start;
	dir.normalize();

	bool turnLeft = (ori.y > 0 && ori.x > 0) || (ori.y <= 0 && ori.x <= 0);
	f2Vec2 pos = foot + f2Math::rotateVectorRightAngle(dir, turnLeft) * fabs(ori.y);

	float angle = src.getAngle();
	if (ori.x > 0) angle += f2Math::getLineAngle(start, end);
	else angle += f2Math::getLineAngle(start, end) - PI/* * 0.5f*/;

	dst.setTransform(pos, angle);
}

LibraryTemplateItem* PasteTileTemplateOP::randomTemplate() const
{
	std::vector<LibraryTemplateItem*> templates;
	m_libraryPanel->traverse(FetchAllVisitor<LibraryTemplateItem>(templates));
	const int index = static_cast<int>(templates.size() * Random::getNum0To1());
	return templates[index];
}