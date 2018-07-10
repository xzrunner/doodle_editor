
#include "SpritesPanelImpl.h"
#include "LibraryPanel.h"
#include "EditPanel.h"

#include "Dataset/SpriteFactory.h"

using namespace wxgui;

SpritesPanelImpl::SpritesPanelImpl(EditPanel* editPanel, LibraryPanel* libraryPanel)
	: MultiSpritesImpl(editPanel)
{
	m_editPanel = editPanel;
	m_libraryPanel = libraryPanel;
	editPanel->SetDropTarget(new DragSymbolTarget(this));
}

SpritesPanelImpl::~SpritesPanelImpl()
{
	clear();
}

void SpritesPanelImpl::traverseSprites(IVisitor& visitor, TraverseType type/* = e_allExisting*/,
									   bool order/* = true*/) const
{
	if (order)
	{
		std::vector<ISprite*>::const_iterator itr = m_sprites.begin();
		for ( ; itr != m_sprites.end(); ++itr)
		{
			bool hasNext;
			visitor.visit(*itr, hasNext);
			if (!hasNext) break;
		}
	}
	else
	{
		std::vector<ISprite*>::const_reverse_iterator itr = m_sprites.rbegin();
		for ( ; itr != m_sprites.rend(); ++itr)
		{
			bool hasNext;
			visitor.visit(*itr, hasNext);
			if (!hasNext) break;
		}
	}
}

void SpritesPanelImpl::removeSprite(ISprite* sprite)
{
	for (size_t i = 0, n = m_sprites.size(); i < n; ++i)
	{
		if (m_sprites[i] == sprite)
		{
			m_sprites[i]->release();
			m_sprites.erase(m_sprites.begin() + i);
			break;
		}
	}
}

void SpritesPanelImpl::insertSprite(ISprite* sprite)
{
	sprite->retain();
	m_sprites.push_back(sprite);
	m_wnd->Refresh();
}

void SpritesPanelImpl::clear()
{
	for (size_t i = 0, n = m_sprites.size(); i < n; ++i)
		m_sprites[i]->release();
	m_sprites.clear();
}

//////////////////////////////////////////////////////////////////////////
// class SpritesPanelImpl::DragSymbolTarget
//////////////////////////////////////////////////////////////////////////

SpritesPanelImpl::DragSymbolTarget::
DragSymbolTarget(SpritesPanelImpl* panelImpl)
{
	m_panelImpl = panelImpl;
}

bool SpritesPanelImpl::DragSymbolTarget::
OnDropText(wxCoord x, wxCoord y, const wxString& data)
{
	wxString sType = data.substr(0, data.find(","));
	wxString sIndex = data.substr(data.find(",") + 1);

	long index;
	sIndex.ToLong(&index);

	ISymbol* symbol = m_panelImpl->m_libraryPanel->getSymbol(index);
	if (symbol)
	{
		f2Vec2 pos = m_panelImpl->m_editPanel->transPosScreenToProject(x, y);
		ISprite* sprite = SpriteFactory::create(symbol);
		sprite->translate(pos);
		m_panelImpl->insertSprite(sprite);
		sprite->release();
	}

	return true;
}