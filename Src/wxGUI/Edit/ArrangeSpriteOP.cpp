#ifndef _WX_GUI_ARRANGE_SPRITE_OP_CPP_
#define _WX_GUI_ARRANGE_SPRITE_OP_CPP_

#include "ArrangeSpriteOP.h"

#include "Dataset/ISprite.h"
#include "Tools/Math.h"
#include "View/EditPanel.h"
#include "View/MultiSpritesImpl.h"
#include "View/PropertySettingPanel.h"
#include "Atomic/ArrangeSpriteAtomicOP.h"
#include "Render/PrimitiveDraw.h"

namespace wxgui
{
	template <typename TBase>
	const float ArrangeSpriteOP<TBase>::SCALE_NODE_RADIUS = 2.0f;

	template <typename TBase>
	ArrangeSpriteOP<TBase>::ArrangeSpriteOP(EditPanel* editPanel, MultiSpritesImpl* spritesImpl, 
		PropertySettingPanel* propertyPanel, AbstractEditCMPT* callback/* = NULL*/, bool scaleOpen/* = true*/)
		: TBase(editPanel, spritesImpl, propertyPanel, callback)
		, m_scaleOpen(scaleOpen)
		, m_spritesImpl(spritesImpl)
		, m_propertyPanel(propertyPanel)
		, m_bRightPress(false)
		, m_scaling(NULL)
		, m_bDirty(false)
	{
		m_selection = spritesImpl->getSpriteSelection();
		m_selection->retain();

		m_firstPos.setInvalid();

		m_scaleSelected.setInvalid();
	}

	template <typename TBase>
	ArrangeSpriteOP<TBase>::~ArrangeSpriteOP()
	{
		m_selection->release();
	}

	template <typename TBase>
	bool ArrangeSpriteOP<TBase>::onKeyDown(int keyCode)
	{
		std::vector<ISprite*> sprites;
		m_selection->traverse(FetchAllVisitor<ISprite>(sprites));
		for (size_t i = 0, n = sprites.size(); i < n; ++i)
			sprites[i]->retain();

		if (TBase::onKeyDown(keyCode)) 
		{
			for (size_t i = 0, n = sprites.size(); i < n; ++i)
				sprites[i]->release();
			return true;
		}

		switch (keyCode)
		{
		case WXK_DELETE:
			{
				std::vector<ISprite*> noPhysicsSprites;
				for (size_t i = 0, n = sprites.size(); i < n; ++i)
					if (!sprites[i]->getBody()) 
						noPhysicsSprites.push_back(sprites[i]);
				m_editPanel->addHistoryOP(new arrange_sprite::DeleteSpritesAOP(noPhysicsSprites, m_spritesImpl));
			}
			m_spritesImpl->removeSpriteSelection();
			m_scaling = NULL;
			break;
		case 'a': case 'A':
			translateSprite(f2Vec2(-1, 0));
			break;
		case 'd': case 'D':
			translateSprite(f2Vec2(1, 0));
			break;
		case 's': case 'S':
			translateSprite(f2Vec2(0, -1));
			break;
		case 'w': case 'W':
			translateSprite(f2Vec2(0, 1));
			break;
		}

		for (size_t i = 0, n = sprites.size(); i < n; ++i)
			sprites[i]->release();
		return false;
	}

	// todo: ugly
	template <typename TBase>
	bool ArrangeSpriteOP<TBase>::onMouseLeftDown(int x, int y)
	{
		m_lastPos = m_editPanel->transPosScreenToProject(x, y);
		m_scaleSelected.setInvalid();

		if (m_scaleOpen && m_scaling)
		{
			f2Vec2 quad[4];
			Math::computeQuadNodes(m_scaling->getPosition(), m_scaling->getAngle(), 
				m_scaling->getScale(), m_scaling->getBounding()->width() / m_scaling->getScale(), 
				m_scaling->getBounding()->height() / m_scaling->getScale(), quad);

			for (size_t i = 0; i < 4; ++i)
			{
				if (f2Math::getDistance(quad[i], m_lastPos) < SCALE_NODE_RADIUS)
				{
					m_scaleSelected = m_scaling->getPosition() + (quad[i] - m_scaling->getPosition()) / m_scaling->getScale();
					return false;
				}
			}
		}

		if (TBase::onMouseLeftDown(x, y)) return true;

		setScalingFromSelected();

		if (!m_selection->empty())
		{
			m_firstPos = m_lastPos;
		}
		m_bRightPress = false;

		return false;
	}

	template <typename TBase>
	bool ArrangeSpriteOP<TBase>::onMouseLeftUp(int x, int y)
	{
		if (TBase::onMouseLeftUp(x, y)) return true;

		setScalingFromSelected();

		if (m_firstPos.isValid() && !m_selection->empty() && !m_bRightPress)
		{
			f2Vec2 pos = m_editPanel->transPosScreenToProject(x, y);
			m_editPanel->addHistoryOP(new arrange_sprite::MoveSpritesAOP(*m_selection, pos - m_firstPos));
			m_firstPos.setInvalid();
		}

		if (m_propertyPanel && m_bDirty)
		{
			m_propertyPanel->enablePropertyGrid(true);
			m_propertyPanel->updatePropertyGrid();
			m_bDirty = false;
		}

		return false;
	}

	template <typename TBase>
	bool ArrangeSpriteOP<TBase>::onMouseRightDown(int x, int y)
	{
		if (TBase::onMouseRightDown(x, y)) return true;

		m_lastPos = m_editPanel->transPosScreenToProject(x, y);
		if (m_selection->size() == 1)
		{
			m_bRightPress = true;
			m_firstPos = m_lastPos;
		}

		return false;
	}

	template <typename TBase>
	bool ArrangeSpriteOP<TBase>::onMouseRightUp(int x, int y)
	{
		if (TBase::onMouseRightUp(x, y)) return true;

		if (m_bRightPress)
		{
			m_bRightPress = false;
			if (m_firstPos.isValid() && !m_selection->empty())
			{
				f2Vec2 pos = m_editPanel->transPosScreenToProject(x, y);
				m_editPanel->addHistoryOP(new arrange_sprite::RotateSpritesAOP(*m_selection, m_firstPos, pos));
			}
		}

		if (m_propertyPanel && m_bDirty)
		{
			m_propertyPanel->enablePropertyGrid(true);
			m_propertyPanel->updatePropertyGrid();
			m_bDirty = false;
		}

		return false;
	}

	template <typename TBase>
	bool ArrangeSpriteOP<TBase>::onMouseDrag(int x, int y)
	{
		if (TBase::onMouseDrag(x, y)) return true;

		if (m_scaleOpen && m_scaling && m_scaleSelected.isValid())
		{
			f2Vec2 pos = m_editPanel->transPosScreenToProject(x, y);
			scaleSprite(pos);
			return false;
		}

		if (m_selection->empty()) return false;

		f2Vec2 pos = m_editPanel->transPosScreenToProject(x, y);
		if (m_bRightPress)
			rotateSprite(pos);
		else
			translateSprite(pos - m_lastPos);
		m_lastPos = pos;

		return false;
	}

	template <typename TBase>
	bool ArrangeSpriteOP<TBase>::onDraw() const
	{
		if (TBase::onDraw()) return true;

		if (m_scaleOpen && m_scaling)
		{
			f2Vec2 quad[4];
			Math::computeQuadNodes(m_scaling->getPosition(), m_scaling->getAngle(), 
				m_scaling->getScale(), m_scaling->getBounding()->width() / m_scaling->getScale(), 
				m_scaling->getBounding()->height() / m_scaling->getScale(), quad);

			for (size_t i = 0; i < 4; ++i)
				PrimitiveDraw::drawRing(quad[i], SCALE_NODE_RADIUS, f2Colorf(0.2f, 0.8f, 0.2f));
		}

		return false;
	}

	template <typename TBase>
	bool ArrangeSpriteOP<TBase>::clear()
	{
		if (TBase::clear()) return true;

		m_lastPos.setInvalid();
		m_bRightPress = false;
		m_scaling = NULL;

		return false;
	}

	template <typename TBase>
	void ArrangeSpriteOP<TBase>::translateSprite(const f2Vec2& delta)
	{
		m_selection->traverse(TranslateVisitor(delta));
		if (!m_selection->empty()) 
		{
			if (m_propertyPanel && !m_bDirty)
			{
				m_propertyPanel->enablePropertyGrid(false);
				m_bDirty = true;
			}
			m_editPanel->Refresh();
		}
	}

	template <typename TBase>
	void ArrangeSpriteOP<TBase>::rotateSprite(const f2Vec2& dst)
	{
		if (m_selection->size() != 1) return;
		m_selection->traverse(RotateVisitor(m_lastPos, dst));
		if (m_propertyPanel && !m_bDirty)
		{
			m_propertyPanel->enablePropertyGrid(false);
			m_bDirty = true;
		}
		m_editPanel->Refresh();
	}

	template <typename TBase>
	void ArrangeSpriteOP<TBase>::scaleSprite(const f2Vec2& currPos)
	{
		if (!m_scaleOpen) return;

		const f2Vec2& center = m_scaling->getPosition();
		f2Vec2 foot;
		f2Math::getFootOfPerpendicular(center, m_scaleSelected, currPos, &foot);
		const float scale = f2Math::getDistance(foot, center) / f2Math::getDistance(m_scaleSelected, center);
		m_scaling->setScale(scale);
		if (m_propertyPanel && !m_bDirty)
		{
			m_propertyPanel->enablePropertyGrid(false);
			m_bDirty = true;
		}
		m_editPanel->Refresh();
	}

	template <typename TBase>
	void ArrangeSpriteOP<TBase>::setScalingFromSelected()
	{
		if (!m_scaleOpen) return;

		bool refresh = false;
		if (m_selection->size() == 1)
		{
			refresh = m_scaling == NULL;
			std::vector<ISprite*> sprites;
			m_selection->traverse(FetchAllVisitor<ISprite>(sprites));
			m_scaling = sprites[0];
		}
		else
		{
			refresh = m_scaling != NULL;
			m_scaling = NULL;
		}

		if (refresh) 
			m_editPanel->Refresh();
	}

	//////////////////////////////////////////////////////////////////////////
	// class ArrangeSpriteOP<TBase>::TranslateVisitor
	//////////////////////////////////////////////////////////////////////////

	template <typename TBase>
	ArrangeSpriteOP<TBase>::TranslateVisitor::
		TranslateVisitor(const f2Vec2& delta)
		: m_delta(delta)
	{
	}

	template <typename TBase>
	void ArrangeSpriteOP<TBase>::TranslateVisitor::
		visit(IObject* object, bool& bFetchNext)
	{
		ISprite* sprite = static_cast<ISprite*>(object);
		sprite->translate(m_delta);
		bFetchNext = true;
	}

	//////////////////////////////////////////////////////////////////////////
	// class ArrangeSpriteOP<TBase>::RotateVisitor
	//////////////////////////////////////////////////////////////////////////

	template <typename TBase>
	ArrangeSpriteOP<TBase>::RotateVisitor::
		RotateVisitor(const f2Vec2& start, const f2Vec2& end)
		: m_start(start), m_end(end)
	{
	}

	template <typename TBase>
	void ArrangeSpriteOP<TBase>::RotateVisitor::
		visit(IObject* object, bool& bFetchNext)
	{
		ISprite* sprite = static_cast<ISprite*>(object);

		float angle = f2Math::getAngleInDirection(sprite->getPosition(), m_start, m_end);
		sprite->rotate(angle);

		bFetchNext = false;
	}
}

#endif // _WX_GUI_ARRANGE_SPRITE_OP_CPP_