#include "ArrangeSpriteAtomicOP.h"

#include "View/MultiSpritesImpl.h"

using namespace wxgui;
using namespace wxgui::arrange_sprite;

//////////////////////////////////////////////////////////////////////////
// class SpritesAOP
//////////////////////////////////////////////////////////////////////////

SpritesAOP::SpritesAOP(const SpriteSelection& selection)
{
	selection.traverse(FetchAllVisitor<ISprite>(m_sprites));
	for (size_t i = 0, n = m_sprites.size(); i < n; ++i)
		m_sprites[i]->retain();
}

SpritesAOP::SpritesAOP(const std::vector<ISprite*>& sprites)
{
	for (size_t i = 0, n = sprites.size(); i < n; ++i)
	{
		sprites[i]->retain();
		m_sprites.push_back(sprites[i]);
	}
}

SpritesAOP::~SpritesAOP()
{
	for (size_t i = 0, n = m_sprites.size(); i < n; ++i)
		m_sprites[i]->release();
}

//////////////////////////////////////////////////////////////////////////
// class MoveSpritesAOP
//////////////////////////////////////////////////////////////////////////

MoveSpritesAOP::MoveSpritesAOP(const SpriteSelection& selection, const f2Vec2& offset)
	: SpritesAOP(selection)
{
	m_offset = offset;
}

MoveSpritesAOP::MoveSpritesAOP(const std::vector<ISprite*>& sprites, const f2Vec2& offset)
	: SpritesAOP(sprites)
{
	m_offset = offset;
}

void MoveSpritesAOP::undo()
{
	for (size_t i = 0, n = m_sprites.size(); i < n; ++i)
	{
		ISprite* sprite = m_sprites[i];
		sprite->translate(-m_offset);
	}
}

void MoveSpritesAOP::redo()
{
	for (size_t i = 0, n = m_sprites.size(); i < n; ++i)
	{
		ISprite* sprite = m_sprites[i];
		sprite->translate(m_offset);
	}
}

//////////////////////////////////////////////////////////////////////////
// class RotateSpritesAOP
//////////////////////////////////////////////////////////////////////////

RotateSpritesAOP::RotateSpritesAOP(const SpriteSelection& selection, const f2Vec2& start, const f2Vec2& end)
	: SpritesAOP(selection)
	, m_start(start)
	, m_end(end)
{
}

RotateSpritesAOP::RotateSpritesAOP(const std::vector<ISprite*>& sprites, const f2Vec2& start, const f2Vec2& end)
	: SpritesAOP(sprites)
	, m_start(start)
	, m_end(end)
{
}

void RotateSpritesAOP::undo()
{
	for (size_t i = 0, n = m_sprites.size(); i < n; ++i)
	{
		ISprite* sprite = m_sprites[i];
		float angle = f2Math::getAngleInDirection(sprite->getPosition(), m_start, m_end);
		sprite->rotate(-angle);
	}
}

void RotateSpritesAOP::redo()
{
	for (size_t i = 0, n = m_sprites.size(); i < n; ++i)
	{
		ISprite* sprite = m_sprites[i];
		float angle = f2Math::getAngleInDirection(sprite->getPosition(), m_start, m_end);
		sprite->rotate(angle);
	}
}

//////////////////////////////////////////////////////////////////////////
// class DeleteSpritesAOP
//////////////////////////////////////////////////////////////////////////

DeleteSpritesAOP::DeleteSpritesAOP(const SpriteSelection& selection, MultiSpritesImpl* spritesImpl)
	: SpritesAOP(selection)
{
	m_spritesImpl = spritesImpl;
}

DeleteSpritesAOP::DeleteSpritesAOP(const std::vector<ISprite*>& sprites, MultiSpritesImpl* spritesImpl)
	: SpritesAOP(sprites)
{
	m_spritesImpl = spritesImpl;
}

void DeleteSpritesAOP::undo()
{
	for (size_t i = 0, n = m_sprites.size(); i < n; ++i)
		m_spritesImpl->insertSprite(m_sprites[i]);
}

void DeleteSpritesAOP::redo()
{
	for (size_t i = 0, n = m_sprites.size(); i < n; ++i)
		m_spritesImpl->removeSprite(m_sprites[i]);
}