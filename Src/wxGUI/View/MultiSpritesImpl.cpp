#include "MultiSpritesImpl.h"

using namespace wxgui;

MultiSpritesImpl::MultiSpritesImpl(wxWindow* wnd)
{
	m_wnd = wnd;
	m_spriteSelection = new SpriteSelection;
}

MultiSpritesImpl::~MultiSpritesImpl()
{
	m_spriteSelection->release();
}

ISprite* MultiSpritesImpl::querySpriteByPos(const f2Vec2& pos) const
{
	ISprite* result = NULL;
	traverseSprites(PointQueryVisitor(pos, &result), e_editable, false);
	return result;
}

void MultiSpritesImpl::querySpritesByAABB(const f2AABB& aabb, std::vector<ISprite*>& result) const
{
	traverseSprites(RectQueryVisitor(aabb, result), e_editable);
}

void MultiSpritesImpl::removeSpriteSelection()
{
	if (!m_spriteSelection->empty())
	{
		m_spriteSelection->traverse(RemoveSelectionVisitor(this));
		m_spriteSelection->clear();
		m_wnd->Refresh();
	}
}

//////////////////////////////////////////////////////////////////////////
// class MultiSpritesImpl::PointQueryVisitor
//////////////////////////////////////////////////////////////////////////

MultiSpritesImpl::PointQueryVisitor::PointQueryVisitor(const f2Vec2& pos, ISprite** pResult)
	: m_pos(pos)
{
	m_pResult = pResult;
	*m_pResult = NULL;
}

void MultiSpritesImpl::PointQueryVisitor::visit(IObject* object, bool& bFetchNext)
{
	ISprite* sprite = static_cast<ISprite*>(object);
	if (sprite->isContain(m_pos))
	{
		*m_pResult = sprite;
		bFetchNext = false;
	}
	else
	{
		bFetchNext = true;
	}
}

//////////////////////////////////////////////////////////////////////////
// class MultiSpritesImpl::RectQueryVisitor
//////////////////////////////////////////////////////////////////////////

MultiSpritesImpl::RectQueryVisitor::RectQueryVisitor(const f2AABB& aabb, std::vector<ISprite*>& result)
	: m_aabb(aabb), m_result(result)
{
}

void MultiSpritesImpl::RectQueryVisitor::visit(IObject* object, bool& bFetchNext)
{
	ISprite* sprite = static_cast<ISprite*>(object);
	if (sprite->isIntersect(m_aabb))
		m_result.push_back(sprite);
	bFetchNext = true;
}

//////////////////////////////////////////////////////////////////////////
// class MultiSpritesImpl::RemoveSelectionVisitor
//////////////////////////////////////////////////////////////////////////

MultiSpritesImpl::RemoveSelectionVisitor::RemoveSelectionVisitor(MultiSpritesImpl* spritesImpl)
{
	m_spritesImpl = spritesImpl;
}

void MultiSpritesImpl::RemoveSelectionVisitor::visit(IObject* object, bool& bFetchNext)
{
	m_spritesImpl->removeSprite(static_cast<ISprite*>(object));
	bFetchNext = true;
}