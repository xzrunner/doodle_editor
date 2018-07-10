#include "Model.h"
#include "Blackboard.h"
#include "UICtrlsMgr.h"
#include "../Utility.h"
#include "../../../Dataset/PointShape.h"
#include "../../../Dataset/ChainShape.h"
#include "../../../Dataset/ChainBody.h"
#include "../../../Dataset/Sprite.h"
#include "../../../Dataset/Layer.h"
#include "../../../Dataset/LayersMgr.h"
#include "../../../File/FileNameParser.h"
#include "../../../File/ActorMotionAdapter.h"

using namespace FEDITOR;
using namespace FEDITOR::MOTOX::JOINT;

Model::Model(const AbstractBlackboard* blackboard, b2World* world)
	: m_joints(world, static_cast<Blackboard*>(const_cast<AbstractBlackboard*>(blackboard))->m_jointParams)
{
	m_blackboard = static_cast<Blackboard*>(const_cast<AbstractBlackboard*>(blackboard));
	m_layer = NULL;
	m_bgSprite = NULL;
	initLayers(world);
}

Model::~Model()
{

}

void Model::handleEvent(const Event& event)
{
	switch (event.getID())
	{
	case Blackboard::e_OpenHead:
	case Blackboard::e_OpenBody:
	case Blackboard::e_OpenBigArm:
	case Blackboard::e_OpenSmallArm:
	case Blackboard::e_OpenBigLeg:
	case Blackboard::e_OpenSmallLeg:
	case Blackboard::e_OpenMotorbike:
		if (FileNameParser::isType(event.getInfo(), FileNameParser::e_loops))
		{
			m_parts.loadPartTypeFromFile(event.getID(), event.getInfo());
			pushEvent(event);
		}
		break;
	case Blackboard::e_OpenFrontWheel:
	case Blackboard::e_OpenBackWheel:
		if (FileNameParser::isType(event.getInfo(), FileNameParser::e_circle))
		{
			m_parts.loadPartTypeFromFile(event.getID(), event.getInfo());
			pushEvent(event);
		}
		break;
	case Blackboard::e_SetPartsAlive:
		m_parts.setAlive(m_blackboard->m_partsAlive == 1);
		break;

	case Blackboard::e_CreateJoint:
		m_joints.createJoint(m_blackboard->m_chooseJointID, m_parts, m_jointPos->m_pos);
		break;
	case Blackboard::e_CreateWheelsJoint:
		m_joints.createWheelsJoint(m_parts);
		break;

	case Blackboard::e_ResetJointNeck:
	case Blackboard::e_ResetJointShoulder:
	case Blackboard::e_ResetJointElbow:
	case Blackboard::e_ResetJointHip:
	case Blackboard::e_ResetJointKnee:
		m_joints.setJointParams(event.getID() - Blackboard::e_ResetJointNeck);
		break;
	case Blackboard::e_SaveWholeParams:
		storeToFileOnlyJoints("actor_motion.txt");
		break;

	case Blackboard::e_OpenWhole:
		loadFromFile(event.getInfo());
		break;
	case Blackboard::e_SaveWhole:
		storeToFile("actor_motion.txt");
		break;
	}
}

Body* Model::getGround()
{
	return m_bgSprite->getBody();
}

void Model::initLayers(b2World* world)
{
	initBackgroundLayer(world);
	initEditedLayer();
	initTempLayer();
}

void Model::initBackgroundLayer(b2World* world)
{
	const float hWidth = SCREEN_WIDTH * 0.5f,
		hHeight = SCREEN_HEIGHT * 0.5f;

	Layer* background = new Layer(Layer::e_lowermost);

	m_bgSprite = new Sprite(MOTOX::SCALE_SCREEN_TO_PHYSICS);

	ChainShape* vertical = new ChainShape;
	vertical->m_vertices.push_back(f2Vec2(0.0f, hHeight));
	vertical->m_vertices.push_back(f2Vec2(0.0f, - hHeight));
	m_bgSprite->pushShape(vertical);

	ChainShape* horizontal = new ChainShape;
	horizontal->m_vertices.push_back(f2Vec2(- hWidth, 0.0f));
	horizontal->m_vertices.push_back(f2Vec2(hWidth, 0.0f));
	m_bgSprite->pushShape(horizontal);

	std::vector<f2Vec2> vertices;
	vertices.push_back(f2Vec2(-hWidth, -hHeight));
	vertices.push_back(f2Vec2( hWidth, -hHeight));
	vertices.push_back(f2Vec2( hWidth,  hHeight));
	vertices.push_back(f2Vec2(-hWidth,  hHeight));
	m_bgSprite->setBody(new ChainBody(world, vertices, true, MOTOX::SCALE_SCREEN_TO_PHYSICS));

	background->addSprite(m_bgSprite);

	m_layers->addLayer(background);
}

void Model::initEditedLayer()
{
	m_layer = new Layer(Layer::e_middle);
	m_parts.initSprites(m_layer);
	m_layers->addLayer(m_layer);
}

void Model::initTempLayer()
{
	Layer* upperLayer = new Layer(Layer::e_uppermost);

	upperLayer->m_style.m_pointStyle.size = 10;

	Sprite* joint = new Sprite;
	m_jointPos = new PointShape;
	joint->pushShape(m_jointPos);
	upperLayer->addSprite(joint);

	m_layers->addLayer(upperLayer);
}

void Model::loadFromFile(const std::string& filename)
{
	ActorMotionAdapter am;
	am.load(filename);

	m_parts.loadFromFileAdapter(am);
	m_joints.loadFromFileAdapter(am);
	for (size_t i = 0; i < JOINTS_TYPE_COUNT; ++i)
		m_joints.createJoint(i, m_parts, am.m_joints[i].anchor);
	m_joints.createWheelsJoint(m_parts);

	for (int i = e_JointTypeNeck; i <= e_JointTypeKnee; ++i)
		m_joints.setJointParams(i);
}

void Model::storeToFile(const std::string& filename) const
{
	std::ofstream fout(filename.c_str());
	m_parts.storeToTextFile(fout);
	m_joints.storeToTextFile(fout);
	fout.close();
}

void Model::storeToFileOnlyJoints(const std::string& filename) const
{
	ActorMotionAdapter adapter;
	adapter.load(filename);

	std::ofstream fout(filename.c_str());
	for (size_t i = 0, n = adapter.m_parts.size(); i < n; ++i)
	{
		const ActorMotionAdapter::Part& src = adapter.m_parts[i];
		fout << src.filename << '\n' 
			<< src.pos << " " << src.angle << '\n';
	}
	for (size_t i = 0, n = adapter.m_joints.size(); i < n; ++i)
	{
		const ActorMotionAdapter::Joint& src = adapter.m_joints[i];
		fout << m_joints.getJointParams(i) << " " << src.anchor << '\n';
	}
	fout.close();
}