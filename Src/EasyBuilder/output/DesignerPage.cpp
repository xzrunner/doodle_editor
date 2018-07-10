#include "DesignerPage.h"

#include "dataset/Actor.h"
#include "dataset/Scene.h"
#include "dataset/Game.h"
#include "view/Context.h"
#include "view/PropertySettingPanel.h"
#include "view/LibraryPanel.h"
#include "view/ActorPropertySetting.h"
#include "view/ScenesPage.h"
#include "view/SceneItem.h"
#include "view/StagePanel.h"
#include "view/BackstagePanel.h"

using namespace ebuilder;

DesignerPage::DesignerPage(wxWindow* parent)
	: wxgui::EditPanel(parent)
	, wxgui::MultiSpritesImpl(this)
	, m_scene(NULL)
{
	m_editOP = new ArrangeActorOP(this, NULL);
	m_canvas = new Canvas(this);

	SetDropTarget(new DragActorTarget(this));
}

void DesignerPage::traverseSprites(IVisitor& visitor, 
								   wxgui::TraverseType type/* = e_allExisting*/, 
								   bool order/* = true*/) const
{
	if (!m_scene) return;

	const std::vector<Actor*>& actors = m_scene->getScene()->getActors();
	if (order)
	{
		std::vector<Actor*>::const_iterator itr = actors.begin();
		for ( ; itr != actors.end(); ++itr)
		{
			bool hasNext;
			visitor.visit(*itr, hasNext);
			if (!hasNext) break;
		}
	}
	else
	{
		std::vector<Actor*>::const_reverse_iterator itr = actors.rbegin();
		for ( ; itr != actors.rend(); ++itr)
		{
			bool hasNext;
			visitor.visit(*itr, hasNext);
			if (!hasNext) break;
		}
	}
}

void DesignerPage::removeSprite(wxgui::ISprite* sprite)
{
	if (m_scene)
	{
		m_scene->removeActor(static_cast<Actor*>(sprite));
		updateCodePage();
	}
}

void DesignerPage::insertSprite(wxgui::ISprite* sprite)
{
	if (m_scene)
	{
		sprite->retain();
		m_scene->insertActor(static_cast<Actor*>(sprite));
		m_wnd->Refresh();
		updateCodePage();
	}
}

void DesignerPage::clear()
{
	wxgui::EditPanel::clear();
}

void DesignerPage::setScene(SceneItem* scene)
{
	m_scene = scene;
}

Scene* DesignerPage::getScene() const
{
	return m_scene->getScene();
}

void DesignerPage::updateCodePage()
{
	Context::Instance()->stage->updateCodePages(m_scene);
}

//////////////////////////////////////////////////////////////////////////
// class DesignerPage::Canvas
//////////////////////////////////////////////////////////////////////////

DesignerPage::Canvas::Canvas(DesignerPage* panel)
	: wxgui::SpriteStageCanvas(panel, panel)
{
	setBgColor(f2Colorf(0.8f, 0.8f, 0.8f));
}

void DesignerPage::Canvas::onDraw()
{
	drawBackground();	

	wxgui::SpriteStageCanvas::onDraw();

	drawCenter();
}

void DesignerPage::Canvas::drawBackground()
{
	wxgui::PrimitiveDraw::drawRectangle(f2Vec2(), 
		Game::WIDTH, Game::HEIGHT, f2Colorf(0, 0, 0));
}

void DesignerPage::Canvas::drawCenter()
{
	const int hEdge = 15;
	wxgui::PrimitiveDraw::drawLine(f2Vec2(-hEdge, 0), f2Vec2(hEdge, 0), 
		f2Colorf(1, 0, 0), 2);
	wxgui::PrimitiveDraw::drawLine(f2Vec2(0, -hEdge), f2Vec2(0, hEdge), 
		f2Colorf(1, 0, 0), 2);
}

//////////////////////////////////////////////////////////////////////////
// class DesignerPage::DragActorTarget
//////////////////////////////////////////////////////////////////////////

DesignerPage::DragActorTarget::
DragActorTarget(DesignerPage* editPanel)
	: m_editPanel(editPanel)
{
}

bool DesignerPage::DragActorTarget::
OnDropText(wxCoord x, wxCoord y, const wxString& data)
{
	wxString sType = data.substr(0, data.find(","));
	wxString sIndex = data.substr(data.find(",") + 1);

	long index;
	sIndex.ToLong(&index);

 	if (wxgui::ImageSymbol* symbol = dynamic_cast<wxgui::ImageSymbol*>
		(Context::Instance()->library->getSymbol(index)))
 	{
 		f2Vec2 pos = m_editPanel->transPosScreenToProject(x, y);

		Actor* actor = new Actor(symbol);
 		actor->translate(pos);
 		m_editPanel->insertSprite(actor);
		Context::Instance()->library->addActor(actor);
 		actor->release();
 	}

	return true;
}

//////////////////////////////////////////////////////////////////////////
// class DesignerPage::SelectActorOP
//////////////////////////////////////////////////////////////////////////

DesignerPage::SelectActorOP::
SelectActorOP(wxgui::EditPanel* editPanel, 
			  wxgui::MultiSpritesImpl* spritesImpl,
			  wxgui::PropertySettingPanel* propertyPanel,
			  wxgui::AbstractEditCMPT* callback/* = NULL*/,
			  const f2Colorf& color/* = f2Colorf(1, 1, 1)*/)
	: wxgui::SelectSpritesOP(editPanel, spritesImpl, propertyPanel, callback, color)
{
}

bool DesignerPage::SelectActorOP::
onMouseLeftUp(int x, int y)
{
	if (wxgui::SelectSpritesOP::onMouseLeftUp(x, y))
		return true;

	if (m_selection->size() != 1)
		clearBackstage();

	return false;
}

bool DesignerPage::SelectActorOP::
clear()
{
	if (wxgui::SelectSpritesOP::clear())
		return true;

	clearBackstage();

	return false;
}

wxgui::IPropertySetting* DesignerPage::SelectActorOP::
createPropertySetting(wxgui::ISprite* sprite) const
{
	Context* context = Context::Instance();

	context->backstage->initFromActor(static_cast<Actor*>(sprite));

	return new ActorPropertySetting(static_cast<Actor*>(sprite), 
		context->library->getActorList());
}

void DesignerPage::SelectActorOP::
clearBackstage()
{
	Context::Instance()->backstage->initFromActor(NULL);
}

//////////////////////////////////////////////////////////////////////////
// class DesignerPage::ArrangeActorOP
//////////////////////////////////////////////////////////////////////////

DesignerPage::ArrangeActorOP::
ArrangeActorOP(DesignerPage* editPanel, wxgui::AbstractEditCMPT* callback)
	: wxgui::ArrangeSpriteOP<SelectActorOP>(editPanel, editPanel, Context::Instance()->property, callback, false)
{
}


void DesignerPage::ArrangeActorOP::
translateSprite(const f2Vec2& delta)
{
	wxgui::ArrangeSpriteOP<SelectActorOP>::
		translateSprite(delta);
	refreshThumbnail();
}

void DesignerPage::ArrangeActorOP::
rotateSprite(const f2Vec2& dst)
{
	wxgui::ArrangeSpriteOP<SelectActorOP>::
		rotateSprite(dst);
	refreshThumbnail();
}

void DesignerPage::ArrangeActorOP::
scaleSprite(const f2Vec2& currPos)
{
	wxgui::ArrangeSpriteOP<SelectActorOP>::
		scaleSprite(currPos);
	refreshThumbnail();
}

void DesignerPage::ArrangeActorOP::
refreshThumbnail()
{
	LibraryPanel* library = Context::Instance()->library;
	library->getScenePage()->refreshSceneThumbnail();
	library->getScenePage()->Refresh();
}