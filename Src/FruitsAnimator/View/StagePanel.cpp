#include "StagePanel.h"
#include "LibraryPanel.h"
#include "TimeLinePanel.h"
#include "StageGLCanvas.h"
#include "Dataset/Layer.h"
#include "Dataset/Symbol.h"
#include "Dataset/Sprite.h"
#include "Dataset/SpriteFactory.h"
#include "Dataset/KeyFrame.h"
#include "Dataset/LayersMgr.h"
#include "Edit/ArrangeSpriteOP.h"

using namespace FRUITS_ANIMATOR;

StagePanel::StagePanel(wxWindow* parent, LibraryPanel* libraryPanel, TimeLinePanel* timeLinePanel)
	: EditPanel(parent), MultiSpritesImpl(parent)
{
	m_libraryPanel = libraryPanel;
	m_timeLinePanel = timeLinePanel;
	SetDropTarget(new DragSymbolTarget(this));
	m_editOP = new ArrangeSpriteOP(this);
	m_canvas = new StageGLCanvas(this);
	SetFocus();
}

void StagePanel::traverseSprites(IVisitor& visitor, 
								 wxgui::TraverseType type/* = wxgui::e_allExisting*/,
								 bool order/* = true*/) const
{
	std::vector<Sprite*>::const_iterator itr = m_sprites.begin();
	for ( ; itr != m_sprites.end(); ++itr)
	{
		bool hasNext;
		visitor.visit(*itr, hasNext);
		if (!hasNext) break;
	}
}

void StagePanel::removeSprite(f2Sprite* sprite)
{
	for (size_t i = 0, n = m_sprites.size(); i < n; ++i)
	{
		if (m_sprites[i] == sprite)
		{
			m_timeLinePanel->getLayerMgr()->removeSprite(m_sprites[i]);
			m_sprites[i]->release();
			m_sprites.erase(m_sprites.begin() + i);
			break;
		}
	}
}

void StagePanel::clear()
{
	for (size_t i = 0, n = m_sprites.size(); i < n; ++i)
		m_sprites[i]->release();
	m_sprites.clear();
	m_spriteSelection->clear();
}

void StagePanel::insertSymbol(int index, wxCoord x, wxCoord y)
{
	Symbol* symbol = m_libraryPanel->getSymbol(index);
	if (!symbol) return;
	Layer* layer = m_timeLinePanel->getCurrLayer();
	if (!layer) return;

	f2Vec2 pos = transPosScreenToProject(x, y);
	Sprite* sprite = SpriteFactory::createMorphingSprite(symbol, pos, true);
	bool success = layer->insertSprite(sprite, m_timeLinePanel->getCurrFrame());
	if (!success) delete sprite;
	else loadCurrFrameSprites();
}

void StagePanel::insertSkeleton(int index, wxCoord x, wxCoord y)
{
	WholeSkeleton* skeleton = m_libraryPanel->getSkeleton(index);
	if (!skeleton) return;
	Layer* layer = m_timeLinePanel->getCurrLayer();
	if (!layer) return;

	Sprite* sprite = SpriteFactory::createSkeletalSprite(skeleton);
	bool success = layer->insertSprite(sprite, m_timeLinePanel->getCurrFrame());
	if (!success) delete sprite;
	else loadCurrFrameSprites();
}

void StagePanel::loadCurrFrameSprites()
{
	m_sprites.clear();
	LayersMgr* layersMgr = m_timeLinePanel->getLayerMgr();
	for (size_t i = 0, n = layersMgr->size(); i < n; ++i)
	{
		Layer* layer = layersMgr->getLayer(i);
		KeyFrame* frame = layer->getCurrKeyFrame(m_timeLinePanel->getCurrFrame());
		if (frame) 
		{
			const std::vector<Sprite*>& sprites = frame->getAllSprites();
			copy(sprites.begin(), sprites.end(), back_inserter(m_sprites));
		}
	}
	Refresh();
	m_timeLinePanel->Refresh();
}

void StagePanel::resetCanvas()
{
	m_canvas->resetInitState();
	Refresh();
}

//////////////////////////////////////////////////////////////////////////
// class StagePanel::DragSymbolTarget
//////////////////////////////////////////////////////////////////////////

StagePanel::DragSymbolTarget::DragSymbolTarget(StagePanel* panel)
{
	m_panel = panel;
}

bool StagePanel::DragSymbolTarget::OnDropText(wxCoord x, wxCoord y, const wxString& data)
{
	wxString sType = data.substr(0, data.find(","));
	wxString sIndex = data.substr(data.find(",") + 1);

	long index;
	sIndex.ToLong(&index);

	if (sType == LibraryPanel::SYMBOL_LIST_NAME)
		m_panel->insertSymbol(index, x, y);
	else if (sType == LibraryPanel::SKELETON_LIST_NAME)
		m_panel->insertSkeleton(index, x, y);

	return true;
}