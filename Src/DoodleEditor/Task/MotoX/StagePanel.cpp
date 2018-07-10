#include "StagePanel.h"
#include "StageCanvas.h"
#include "Actor.h"
#include "LibraryPanel.h"
#include "LibraryTemplateItem.h"
#include "LibraryActorItem.h"
#include "TypesDef.h"
#include "BreakableSprite.h"

#include "Frame/defs.h"

using namespace deditor::motox;

StagePanel::StagePanel(wxWindow* parent, LibraryPanel* libraryPanel)
	: EditPanel(parent)
	, wxgui::MultiSpritesImpl(this)
	, ShapesPanelImpl(parent)
	, m_libraryPanel(libraryPanel)
	, m_actor(NULL)
	, m_worldReverse(NULL)
	, m_ground(NULL)
	, m_groundReverse(NULL)
{
	m_canvas = new StageCanvas(this);

	m_worldReverse = createWorld(f2Vec2(0.0f, 10.0f));

	ShapesPanelImpl::setWorld(PhysicsPanelImpl::m_world, m_worldReverse);

	SetDropTarget(new DragSymbolTarget(this));

	for (size_t i = 0; i < 26; ++i)
		m_keyState[i] = false;

	loadGround();
}

StagePanel::~StagePanel()
{
	delete m_actor;
}

void StagePanel::onKeyDown(wxKeyEvent& event)
{
	wxgui::EditPanel::onKeyDown(event);

	int keyCode = event.GetKeyCode();
	if (keyCode >= 'A' && keyCode <= 'Z')
		m_keyState[keyCode - 'A'] = true;
}

void StagePanel::onKeyUp(wxKeyEvent& event)
{
	wxgui::EditPanel::onKeyUp(event);

	int keyCode = event.GetKeyCode();
	if (keyCode >= 'A' && keyCode <= 'Z')
		m_keyState[keyCode - 'A'] = false;
}

void StagePanel::traverseSprites(IVisitor& visitor, 
								 wxgui::TraverseType type/* = wxgui::e_allExisting*/,
								 bool order/* = true*/) const
{
	std::vector<wxgui::Layer*> layers;

	switch (type)
	{
	case wxgui::e_editable:
		m_layersMgr->traverseEditableLayers(FetchAllVisitor<wxgui::Layer>(layers));
		break;
	case wxgui::e_visible:
		m_layersMgr->traverseVisibleLayers(FetchAllVisitor<wxgui::Layer>(layers));
		break;
	case wxgui::e_selectable:
		m_layersMgr->traverseSelectableLayers(FetchAllVisitor<wxgui::Layer>(layers));
		break;
	case wxgui::e_allExisting:
		m_layersMgr->traverseAllLayers(FetchAllVisitor<wxgui::Layer>(layers));
		break;
	default:
		assert(0);
		return;
	}

	bool bStop = false;
	for (size_t i = 0, n = layers.size(); i < n && !bStop; ++i)
	{
		const std::vector<wxgui::ISprite*>& sprites = layers[i]->getSprites();
		if (order)
		{
			std::vector<wxgui::ISprite*>::const_iterator itr = sprites.begin();
			for ( ; itr != sprites.end() && !bStop; ++itr)
			{
				bool hasNext = true;
				visitor.visit(*itr, hasNext);
				if (!hasNext) bStop = true;
			}
		}
		else
		{
			std::vector<wxgui::ISprite*>::const_reverse_iterator itr = sprites.rbegin();
			for ( ; itr != sprites.rend() && !bStop; ++itr)
			{
				bool hasNext = true;
				visitor.visit(*itr, hasNext);
				if (!hasNext) bStop = true;
			}
		}
	}

	if (order)
	{
		std::vector<wxgui::ISprite*>::const_iterator itr = m_physicsSprites.begin();
		for ( ; itr != m_physicsSprites.end() && !bStop; ++itr)
		{
			bool hasNext = true;
			visitor.visit(*itr, hasNext);
			if (!hasNext) bStop = true;
		}
	}
	else
	{
		std::vector<wxgui::ISprite*>::const_reverse_iterator itr = m_physicsSprites.rbegin();
		for ( ; itr != m_physicsSprites.rend() && !bStop; ++itr)
		{
			bool hasNext = true;
			visitor.visit(*itr, hasNext);
			if (!hasNext) bStop = true;
		}
	}
}

void StagePanel::removeSprite(wxgui::ISprite* sprite)
{
	if (sprite->getBody())
	{
		for (size_t i = 0, n = m_physicsSprites.size(); i < n; ++i)
		{
			if (m_physicsSprites[i] == sprite)
			{
				m_physicsSprites.erase(m_physicsSprites.begin() + i);
				sprite->release();
				break;
			}
		}
	}
	else
	{
		wxgui::Layer* layer = m_layersMgr->getEditedLayer();
		if (layer)
		{
			layer->remove(sprite);
			sprite->release();
		}
	}
}

void StagePanel::insertSprite(wxgui::ISprite* sprite)
{
	if (sprite->getBody())
	{
		sprite->getBody()->setAlive(true);
		m_physicsSprites.push_back(sprite);
		sprite->retain();
	}
	else
	{
		wxgui::Layer* layer = m_layersMgr->getEditedLayer();
		if (layer)
		{
			layer->insert(sprite);
			sprite->retain();
		}
	}
}

void StagePanel::clear()
{
	wxgui::EditPanel::clear();
	ShapesPanelImpl::clear();

	m_layersMgr->clear();
	for_each(m_physicsSprites.begin(), m_physicsSprites.end(), DeletePointerFunctor<wxgui::ISprite>());
	m_physicsSprites.clear();

	m_canvas->clear();
}

void StagePanel::insertSprite(int index, wxCoord x, wxCoord y)
{
	wxgui::ISymbol* symbol = m_libraryPanel->getSymbol(index);
	if (symbol)
	{
		f2Vec2 pos = transPosScreenToProject(x, y);
		wxgui::ISprite* sprite = wxgui::SpriteFactory::create(symbol);
		sprite->translate(pos);
		insertSprite(sprite);
		sprite->release();
	}
}

void StagePanel::EndContact(b2Contact* contact)
{
	b2Fixture* fixtureA = contact->GetFixtureA();
	b2Fixture* fixtureB = contact->GetFixtureB();

	void* dataA = fixtureA->GetBody()->GetUserData();
	void* dataB = fixtureB->GetBody()->GetUserData();
	if (dataA && dataB)
	{
		int idA = *static_cast<int*>(dataA);
		int idB = *static_cast<int*>(dataB);
		if (idA == MOTOR_WHEEL_ID && idB == CARTON_ID)
		{
			m_destoryCache.push_back(fixtureB->GetBody());
		}
		else if (idA == CARTON_ID && idB == MOTOR_WHEEL_ID)
		{
			m_destoryCache.push_back(fixtureA->GetBody());
		}
	}
}

void StagePanel::PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
{
	b2Fixture* fixtureA = contact->GetFixtureA();
	b2Fixture* fixtureB = contact->GetFixtureB();

	void* dataA = fixtureA->GetBody()->GetUserData();
	void* dataB = fixtureB->GetBody()->GetUserData();
	if (dataA && dataB)
	{
		int idA = *static_cast<int*>(dataA);
		int idB = *static_cast<int*>(dataB);
		if (idA == ACTOR_ID && idB == PIECE_ID
			|| idA == PIECE_ID && idB == ACTOR_ID
			|| idA == PIECE_ID && idB == PIECE_ID)
		{
			contact->SetEnabled(false);
		}
	}
}

void StagePanel::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse)
{
	float32 maxImpulse = 0.0f;
	b2Vec2 maxPos;

	int32 count = contact->GetManifold()->pointCount;
	for (int32 i = 0; i < count; ++i)
	{
		if (impulse->normalImpulses[i] > maxImpulse)
		{
			maxImpulse = impulse->normalImpulses[i];
			maxPos = contact->GetManifold()->points[i].localPoint;
		}
	}

	if (maxImpulse < 40.0f)
		return;

	f2Vec2 pos;
	pos.x = maxPos.x * BOX2D_SCALE_FACTOR;
	pos.y = maxPos.y * BOX2D_SCALE_FACTOR;

	b2Fixture* fixtureA = contact->GetFixtureA();
	b2Fixture* fixtureB = contact->GetFixtureB();

	void* dataA = fixtureA->GetBody()->GetUserData();
	void* dataB = fixtureB->GetBody()->GetUserData();
	if (dataA && dataB)
	{
		int idA = *static_cast<int*>(dataA);
		int idB = *static_cast<int*>(dataB);
		if (idA == BREAKABLE_ID)
			m_breakCache.push_back(std::make_pair(fixtureA->GetBody(), pos));
		else if (idB == BREAKABLE_ID)
			m_breakCache.push_back(std::make_pair(fixtureB->GetBody(), pos));
	}
}

void StagePanel::update(wxCommandEvent& event)
{
	wxgui::PhysicsPanelImpl::update(event);

	const float timeStep = 1.0f / 60;
	m_worldReverse->Step(timeStep, 8, 3);

	if (m_actor)
	{
		m_actor->driving(m_keyState);
		m_actor->update();
		Refresh();
	}

	bool bRefresh = false;
	for (size_t i = 0, n = m_physicsSprites.size(); i < n; ++i)
	{
		wxgui::ISprite* physics = m_physicsSprites[i];
		if (physics->getBody()->getBody()->IsAwake())
			bRefresh = true;
		physics->updateEachFrame();

// 		if (fabs(physics->getPosition().y) > SCREEN_HEIGHT * 2)
// 		{
// 			removeSprite(physics);
// 			--i;
// 			--n;
// 		}
	}
	if (bRefresh) Refresh();

	//////////////////////////////////////////////////////////////////////////
	for (size_t i = 0, n = m_destoryCache.size(); i < n; ++i)
	{
		b2Body* body = m_destoryCache[i];

		std::vector<b2Joint*> joints;
		for (b2JointEdge* j = body->GetJointList(); j; j = j->next)
			joints.push_back(j->joint);

		for (size_t j = 0, m = joints.size(); j < m; ++j)
			PhysicsPanelImpl::m_world->DestroyJoint(joints[j]);
	}
	m_destoryCache.clear();
	//////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////
	for (size_t i = 0, n = m_breakCache.size(); i < n ;++i)
	{
		b2Body* body = m_breakCache[i].first;

		for (size_t j = 0, m = m_physicsSprites.size(); j < m; ++j)
		{
			if (m_physicsSprites[j]->getBody()->getBody() == body)
			{
				BreakableSprite* sprite = dynamic_cast<BreakableSprite*>(m_physicsSprites[j]);
				assert(sprite);
				std::vector<wxgui::ISprite*> pieces;
				sprite->breakToPieces(pieces, m_breakCache[i].second);

				removeSprite(m_physicsSprites[j]);
				for (size_t i = 0, n = pieces.size(); i < n; ++i)
				{
					insertSprite(pieces[i]);
					pieces[i]->release();
				}

				break;
			}
		}
	}
	m_breakCache.clear();
	//////////////////////////////////////////////////////////////////////////
}

void StagePanel::drawPhysics()
{
	glBindTexture(GL_TEXTURE_2D, NULL);
	glEnableClientState(GL_VERTEX_ARRAY);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	getWorld()->DrawDebugData();
	m_worldReverse->DrawDebugData();
	glDisable(GL_BLEND);

	glDisableClientState(GL_VERTEX_ARRAY);
}

void StagePanel::insertActor(int index, wxCoord x, wxCoord y)
{
	wxgui::BodyFactory::setWorld(wxgui::PhysicsPanelImpl::m_world);

	if (m_actor) 
		delete m_actor, m_actor = NULL;

	LibraryActorItem* item = dynamic_cast<LibraryActorItem*>(m_libraryPanel->getSymbol(index));
	if (item)
	{
		m_actor = new Actor(wxgui::PhysicsPanelImpl::m_world, *item);
		m_actor->setLocation(transPosScreenToProject(x, y));
	}
}

void StagePanel::insertTemplate(int index, wxCoord x, wxCoord y)
{
	LibraryTemplateItem* item = dynamic_cast<LibraryTemplateItem*>(m_libraryPanel->getSymbol(index));
	if (!item || item->m_sprites.empty()) return;
	
	f2Vec2 pos = transPosScreenToProject(x, y);
	for (size_t i = 0, n = item->m_sprites.size(); i < n; ++i)
	{
		wxgui::ISprite* sprite = item->m_sprites[i]->clone();
		f2Vec2 p = pos + (sprite->getPosition() - item->m_center);
		sprite->setTransform(p, sprite->getAngle());
		insertSprite(sprite);
	}
}

void StagePanel::loadGround()
{
	b2BodyDef def;
	def.type = b2_staticBody;

	m_ground = PhysicsPanelImpl::m_world->CreateBody(&def);
	m_groundReverse = m_worldReverse->CreateBody(&def);

	std::vector<b2Vec2> vertices;
	vertices.push_back(b2Vec2(-1000, -100));
	vertices.push_back(b2Vec2( 3000, -100));

	b2ChainShape shape;
	shape.CreateChain(&vertices[0], vertices.size());

	m_ground->CreateFixture(&shape, 1.0f);
	m_groundReverse->CreateFixture(&shape, 1.0f);
}

//////////////////////////////////////////////////////////////////////////
// class StagePanel::DragSymbolTarget
//////////////////////////////////////////////////////////////////////////

StagePanel::DragSymbolTarget::DragSymbolTarget(StagePanel* stagePanel)
{
	m_stagePanel = stagePanel;
}

bool StagePanel::DragSymbolTarget::OnDropText(wxCoord x, wxCoord y, const wxString& data)
{
	wxString sType = data.substr(0, data.find(","));
	wxString sIndex = data.substr(data.find(",") + 1);

	long index;
	sIndex.ToLong(&index);

	if (sType == LibraryPanel::ACTOR_LIST_NAME)
		m_stagePanel->insertActor(index, x, y);
	else if (sType == LibraryPanel::TEMPLATE_LIST_NAME)
		m_stagePanel->insertTemplate(index, x, y);

	return true;
}