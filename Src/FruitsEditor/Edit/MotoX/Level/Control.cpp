#include "Control.h"
#include "Blackboard.h"
#include "View.h"
#include "Model.h"
#include "DrawTrackChainCB.h"
#include "EditTrackChainCB.h"
#include "PasteSpriteCB.h"
#include "ContactListener.h"
#include "../Utility.h"
#include "../../KeyboardTest.h"
#include "../../EditComponent/LayersMgrCmpt.h"
#include "../../EditComponent/LayersIOCmpt.h"
#include "../../EditComponent/PhysTaskSettingCmpt.h"
#include "../../EditComponent/NodeCaptureCmpt.h"
#include "../../EditOperation/DrawPolylineOp.h"
#include "../../EditOperation/EditPolylineOp.h"
#include "../../EditOperation/ArrangeSpriteOp.h"
#include "../../EditOperation/ArrangeSpritePhysOp.h"
#include "../../EditOperation/ArrangeSpriteCommonOp.h"
#include "../../EditOperation/PasteSpriteOp.h"
#include "../../../Dataset/BodyFactory.h"
#include "../../../Dataset/Sprite.h"
#include "../../../Dataset/Layer.h"
#include "../../../File/FileNameParser.h"

using namespace FEDITOR;
using namespace FEDITOR::MOTOX::LEVEL;

Control::Control()
{
	m_worldReverse = createWorld(f2Vec2(0.0f, 10.0f));

	m_view = new View(MOTOX::SCALE_SCREEN_TO_PHYSICS);
	m_model = new Model(m_view->getBlackboard(), getWorld(), m_worldReverse);

	BodyFactory::setWorld(getWorld());

	m_lsn = new ContactListener(dynamic_cast<Model*>(m_model), dynamic_cast<Blackboard*>(m_view->getBlackboard()));
	getWorld()->SetContactListener(m_lsn);
	m_worldReverse->SetContactListener(m_lsn);
}

Control::~Control()
{
}

void Control::onKeyboard(unsigned char key, int x, int y)
{
	AbstractControl::onKeyboard(key, x, y);

	switch (key)
	{
	case 's' : case 'S':
		if (KeyBoardTest::isAltPress())
		{
			Event event(Blackboard::e_SaveTrackChain);
			m_model->handleEvent(event);
		}
		break;
	}
}

void Control::onMouseLeftDown(int x, int y)
{
	Layer* editable = m_layersMgrCmpt->getCertainTypeLayer(LayersMgrCmpt::e_EditedLayer);
	Model* model = dynamic_cast<Model*>(m_model);
	TrackChains& track = model->getTrackChains();
	if (editable && track.getBody())
	{
		Sprite* selected = editable->queryByPos(transPosScrToPoj(x, y));
		if (selected)
		{
			if (selected->getBody())
			{
				b2Body* body = selected->getBody()->getBody();
				ArrangeSpriteCommonOp* as = dynamic_cast<ArrangeSpriteCommonOp*>(m_editOp);
				if (!as || as->getWorld() != body->GetWorld())
				{
					delete m_editOp;
					if (body->GetWorld() == getWorld())
						m_editOp = new ArrangeSpriteCommonOp(this, editable, getWorld(), track.getBody(), ArrangeSpritePhysOp::e_MouseOn);
					else
						m_editOp = new ArrangeSpriteCommonOp(this, editable, m_worldReverse, track.getReverseBody(), ArrangeSpritePhysOp::e_MouseOn);
				}
			}
		}
	}

	m_editOp->onMouseLeftDown(x, y);
}

void Control::onMouseRightDown(int x, int y)
{
	if (m_editOp) 
	{
		bool handled = m_editOp->onMouseRightDown(x, y);
		if (!handled) 
		{
			Layer* editable = m_layersMgrCmpt->getCertainTypeLayer(LayersMgrCmpt::e_EditedLayer);
			Model* model = dynamic_cast<Model*>(m_model);
			TrackChains& track = model->getTrackChains();
			if (editable && track.getBody())
			{
				delete m_editOp;
				m_editOp = new ArrangeSpriteCommonOp(this, editable, m_worldReverse/*getWorld()*/, track.getReverseBody()/*track.getBody()*/, ArrangeSpritePhysOp::e_MouseOn);
			}
			else if (editable)
			{
				setArrangeSpriteOp();
			}
			else if (track.getBody())
			{
				delete m_editOp;
				m_editOp = new ArrangeSpritePhysOp(this, getWorld(), track.getBody(), ArrangeSpritePhysOp::e_MouseOn);
			}
			else
			{
				delete m_editOp, m_editOp = NULL;
			}
		}
	}
}

void Control::handleStep()
{
}

void Control::handleUIEvent()
{
	while (m_view->hasNextEvent())
	{
		Event event = m_view->getNextEvent();
		switch (event.getID())
		{
		case Blackboard::e_SetMouseDrag:
			if (m_editOp) delete m_editOp;
			m_editOp = new ArrangeSpritePhysOp(this, getWorld(), 
				static_cast<Model*>(m_model)->getTrackChains().getBody(), ArrangeSpritePhysOp::e_MouseOn);
			break;

		case Blackboard::e_OpenBgTexture:
			m_model->handleEvent(event);
			break;
		case Blackboard::e_OpenTrackChain:
			m_model->handleEvent(event);
			break;
		case Blackboard::e_OpenTileSprite:
			openTile(event.getInfo());
			break;
		case Blackboard::e_OpenMotorbike:
			m_model->handleEvent(event);
			break;
		case Blackboard::e_OpenAllSprites:
			m_model->handleEvent(event);
			break;

		case Blackboard::e_DrawTrackChain:
			if (m_editOp) delete m_editOp;
			m_editOp = new DrawPolylineOp(this, m_captureCmpt,
				new DrawTrackChainCB(static_cast<Model*>(m_model)->getTrackChains()));
			break;
		case Blackboard::e_EditTrackChain:
			if (m_editOp) delete m_editOp;
			m_editOp = new EditPolylineOP(this, static_cast<Model*>(m_model)->getTrackChainsLayer(), 
				m_captureCmpt, new EditTrackChainCB(static_cast<Model*>(m_model)->getTrackChains()));
			break;
		case Blackboard::e_SaveTrackChain:
			m_model->handleEvent(event);
			break;
		case Blackboard::e_SetTrackFriction:
			m_model->handleEvent(event);
			break;

		case Blackboard::e_SetGravityDir:
			{
				Blackboard* bb = static_cast<Blackboard*>(m_view->getBlackboard());
				if (bb->m_chooseWorldType == 0)
					BodyFactory::setWorld(getWorld());
				else
					BodyFactory::setWorld(m_worldReverse);
			}
			break;

		case Blackboard::e_SetMotoFriction:
		case Blackboard::e_SetMotoDensity:
		case Blackboard::e_SetPlayerDensity:
		case Blackboard::e_SetMotoSpeed:
		case Blackboard::e_SetMotoAcc:
		case Blackboard::e_SetMotoTorque:
		case Blackboard::e_SetMotoDamping:
		case Blackboard::e_SetMotoHz:
		case Blackboard::e_SetMotoMaxMotorTorque:
			m_model->handleEvent(event);
			break;

		case Blackboard::e_SaveSprites:
			m_model->handleEvent(event);
			break;

		case LayersMgrCmpt::e_ChangeEditableLayer:
			setArrangeSpriteOp();
			m_model->getLayersMgr().getSelection().clear();
			break;
		}
	}
}

void Control::createEditCmpt()
{
	AbstractPhysCtrl::createEditCmpt();

	m_layersMgrCmpt = new LayersMgrCmpt(m_model->getLayersMgr(), m_view->getCmptMgr(), m_view->getBlackboard());
//	m_layersIOCmpt = new LayersIOCmpt(m_model->getLayersMgr(), m_view->getCmptMgr(), "motox_level_compose");
	m_captureCmpt = new NodeCaptureCmpt(m_model->getLayersMgr(), m_view->getCmptMgr(), MOTOX::SCALE_SCREEN_TO_PHYSICS);

	setArrangeSpriteOp();
}

void Control::update()
{
	AbstractPhysCtrl::update();

	if (m_physSetting->isStepOpen())
	{
		const float timeStep = 1.0f / m_physSetting->getHz();
		m_worldReverse->Step(timeStep, m_physSetting->getVelocityIterations(), m_physSetting->getPositionIterations());
	}

	m_model->getLayersMgr().updateEachFrame();

	m_model->handleEvent(Event(Blackboard::e_UpdateActor));

	m_lsn->deletePhysics();
}

void Control::display() const
{
	AbstractPhysCtrl::display();
	
	if (m_physSetting->isDrawOpen())
	{
		m_worldReverse->DrawDebugData();
	}

	Blackboard* bb = static_cast<Blackboard*>(m_view->getBlackboard());
	if (bb->m_cameraFocusMoto == 1)
	{
		f2Vec2 pos = static_cast<Model*>(m_model)->getActorPos();
		m_view->setCameraPos(pos);
	}
}

void Control::openTile(const std::string& filename)
{
	FileNameParser::Type type = FileNameParser::getFileType(filename);
	if (type != FileNameParser::e_img && type != FileNameParser::e_loops) return;

	Layer *tempLayer = m_layersMgrCmpt->getCertainTypeLayer(LayersMgrCmpt::e_TempLayer),
		*editedLayer = m_layersMgrCmpt->getCertainTypeLayer(LayersMgrCmpt::e_EditedLayer);
	if (tempLayer && editedLayer)
	{
		if (m_editOp) delete m_editOp;
		Blackboard* bb = static_cast<Blackboard*>(m_view->getBlackboard());
		PasteSpriteCB* callback = new PasteSpriteCB(dynamic_cast<Model*>(m_model));
		float scale = SCALE_SCREEN_TO_PHYSICS * bb->m_spriteScale;
		if (bb->m_flagSpriteMirror == 1) scale = -scale;
		if (bb->m_batchState == 1)
			m_editOp = new PasteSpriteOp(this, tempLayer, editedLayer, filename, false, callback, scale, scale, bb->m_batchNum, bb->m_batchRandomRadius);
		else
			m_editOp = new PasteSpriteOp(this, tempLayer, editedLayer, filename, false, callback, scale, scale);
	}
}

void Control::setArrangeSpriteOp()
{
	delete m_editOp;
	m_editOp = new ArrangeSpriteOp(this, m_layersMgrCmpt->getCertainTypeLayer(LayersMgrCmpt::e_EditedLayer));
}