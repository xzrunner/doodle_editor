#include "RegularGrids.h"
#include "Model.h"
#include "Blackboard.h"
#include "Triangle.h"
#include "Dataset/TextureRegion.h"
#include "Dataset/TriangleShape.h"
#include "Dataset/Sprite.h"
#include "Dataset/Texture.h"
#include "File/FileNameParser.h"
#include "File/ImgFileAdapter.h"
#include <Box2D/Box2D.h>

using namespace FEDITOR;
using namespace FEDITOR::SIMULATE_CLOTH;

RegularGrids::RegularGrids(Model& model)
	: m_model(model)
{
}

void RegularGrids::loadFromFile(const std::string& filename)
{
	if (FileNameParser::isType(filename, FileNameParser::e_img))
	{
		ImgFileAdapter fa;
		fa.m_sprite = m_model.m_bgSprite;
		fa.load(filename);

		m_model.m_bgTexture = TexturesMgr::Instance()->getItem(filename);
		build();
	}
}

void RegularGrids::build()
{
	if (m_model.m_bgTexture->getTexID() == 0) return;

	initParams();
	buildGround();
	m_model.clearGridsPhyData();
	buildBodies();
	buildNodes();
	buildJoints();
	buildDeformationSprite();
}

void RegularGrids::update()
{
	updateDeformationSprite();
}

void RegularGrids::initParams()
{
	m_rowCount = m_model.m_blackboard->m_row;
	m_colCount = m_model.m_blackboard->m_col;
	m_halfNodeEdge = m_model.m_blackboard->m_nodeHalfEdge;
	m_isBoundStatic = m_model.m_blackboard->m_boundStatic == 1;
	isConnectCenter = m_model.m_blackboard->m_connectNodeCenter == 1;
	m_totWidth = m_model.m_bgTexture->getWidth();
	m_totHeight = m_model.m_bgTexture->getHeight();
}

void RegularGrids::buildGround()
{
	if (!m_model.m_ground)
	{
		b2BodyDef bd;
		m_model.m_ground = m_model.m_world->CreateBody(&bd);
	}
	else 
	{
		m_model.m_ground->DestroyFixture(m_model.m_ground->GetFixtureList());
	}

	b2Vec2 loop[] = {
		b2Vec2(-m_totWidth, -m_totHeight),
		b2Vec2( m_totWidth, -m_totHeight),
		b2Vec2( m_totWidth,  m_totHeight),
		b2Vec2(-m_totWidth,  m_totHeight),
	};
	b2ChainShape shape;
	shape.CreateLoop(loop, 4);
	m_model.m_ground->CreateFixture(&shape, 0.0f);
}

void RegularGrids::buildBodies()
{
	b2PolygonShape shape;
	shape.SetAsBox(m_halfNodeEdge, m_halfNodeEdge);
	b2BodyDef bd;
	bd.type = b2_dynamicBody;
	const float xOffset = - m_totWidth * 0.5f,
		yOffset = - m_totHeight * 0.5f;
	const float wGrid = m_totWidth / (m_colCount - 1),
		hGrid = m_totHeight / (m_rowCount - 1);
	for (size_t i = 0; i < m_rowCount; ++i)
	{
		for (size_t j = 0; j < m_colCount; ++j)
		{
			bd.position.Set(wGrid * j + xOffset, hGrid * i + yOffset);

			if (m_isBoundStatic)
			{
				if (i == 0 || /*i == m_rowCount - 1 || */
					j == 0 || j == m_colCount - 1) 
					bd.type = b2_staticBody;
				else 
					bd.type = b2_dynamicBody;
			}
			b2Body* body = m_model.m_world->CreateBody(&bd);
			body->CreateFixture(&shape, 0.0f);
			m_model.m_bodies.push_back(body);
		}
	}
}

void RegularGrids::buildNodes()
{
	m_model.m_tris.clear();

	std::vector<Node*> nodes;
	const float w = 1.0f / (m_colCount - 1),
		h = 1.0f / (m_rowCount - 1);
	for (size_t i = 0; i < m_rowCount; ++i)
	{
		for (size_t j = 0; j < m_colCount; ++j)
		{
			Node* node = new Node;

			node->body = m_model.m_bodies[i * m_colCount + j];
			node->isTop = (i == m_rowCount - 1 && j != 0 && j != m_colCount - 1);
			node->texCoords.x = w * j;
			node->texCoords.y = h * i;

			nodes.push_back(node);
		}
	}

	for (size_t i = 0; i < m_rowCount - 1; ++i)
	{
		for (size_t j = 0; j < m_colCount - 1; ++j)
		{
			Node *leftTop = nodes[(i + 1) * m_colCount + j],
				*leftLow = nodes[i * m_colCount + j],
				*rightTop = nodes[(i + 1) * m_colCount + j + 1],
				*rightLow = nodes[i * m_colCount + j + 1];
			Triangle *tri0= new Triangle,
				*tri1 = new Triangle;
			tri0->nodes[0] = leftLow;
			tri0->nodes[1] = rightLow;
			tri0->nodes[2] = rightTop;
			tri1->nodes[0] = leftLow;
			tri1->nodes[1] = rightTop;
			tri1->nodes[2] = leftTop;
			m_model.m_tris.push_back(tri0);
			m_model.m_tris.push_back(tri1);
		}
	}
}

void RegularGrids::buildJoints()
{
	b2DistanceJointDef jd;
	b2Vec2 p1, p2, d;
	jd.frequencyHz = m_model.m_blackboard->m_frequencyHz;
	jd.dampingRatio = m_model.m_blackboard->m_dampingRatio;
	// joints grids
	for (size_t i = 0; i < m_rowCount; ++i)
	{
		for (size_t j = 1; j < m_colCount; ++j)
		{
			jd.bodyA = m_model.m_bodies[i * m_colCount + j - 1];
			jd.bodyB = m_model.m_bodies[i * m_colCount + j];
			if (!isConnectCenter)
			{
				jd.localAnchorA.Set(m_halfNodeEdge, 0.0f);
				jd.localAnchorB.Set(-m_halfNodeEdge, 0.0f);
			}
			p1 = jd.bodyA->GetWorldPoint(jd.localAnchorA);
			p2 = jd.bodyB->GetWorldPoint(jd.localAnchorB);
			d = p2 - p1;
			jd.length = d.Length();
			b2Joint* joint = m_model.m_world->CreateJoint(&jd);
			m_model.m_joints.push_back(joint);
		}
	}
	for (size_t i = 0; i < m_colCount; ++i)
	{
		for (size_t j = 1; j < m_rowCount; ++j)
		{
			jd.bodyA = m_model.m_bodies[(j - 1) * m_colCount + i];
			jd.bodyB = m_model.m_bodies[j * m_colCount + i];
			if (!isConnectCenter)
			{
				jd.localAnchorA.Set(0.0f, m_halfNodeEdge);
				jd.localAnchorB.Set(0.0f, -m_halfNodeEdge);
			}
			p1 = jd.bodyA->GetWorldPoint(jd.localAnchorA);
			p2 = jd.bodyB->GetWorldPoint(jd.localAnchorB);
			d = p2 - p1;
			jd.length = d.Length();
			b2Joint* joint = m_model.m_world->CreateJoint(&jd);
			m_model.m_joints.push_back(joint);
		}
	}
	// joints to ground
	{
		jd.bodyA = m_model.m_ground;
		jd.bodyB = m_model.m_bodies[0 * m_colCount + 0];
		jd.localAnchorA.Set(-m_totWidth, -m_totHeight);
		if (!isConnectCenter) jd.localAnchorB.Set(-m_halfNodeEdge, -m_halfNodeEdge);
		p1 = jd.bodyA->GetWorldPoint(jd.localAnchorA);
		p2 = jd.bodyB->GetWorldPoint(jd.localAnchorB);
		d = p2 - p1;
		jd.length = d.Length();
		b2Joint* joint = m_model.m_world->CreateJoint(&jd);
		m_model.m_joints.push_back(joint);
	}
	{
		jd.bodyA = m_model.m_ground;
		jd.bodyB = m_model.m_bodies[0 * m_colCount + m_colCount - 1];
		jd.localAnchorA.Set(m_totWidth, -m_totHeight);
		if (!isConnectCenter) jd.localAnchorB.Set(m_halfNodeEdge, -m_halfNodeEdge);
		p1 = jd.bodyA->GetWorldPoint(jd.localAnchorA);
		p2 = jd.bodyB->GetWorldPoint(jd.localAnchorB);
		d = p2 - p1;
		jd.length = d.Length();
		b2Joint* joint = m_model.m_world->CreateJoint(&jd);
		m_model.m_joints.push_back(joint);
	}
	{
		jd.bodyA = m_model.m_ground;
		jd.bodyB = m_model.m_bodies[(m_rowCount - 1) * m_colCount + 0];
		jd.localAnchorA.Set(-m_totWidth, m_totHeight);
		if (!isConnectCenter) jd.localAnchorB.Set(-m_halfNodeEdge, m_halfNodeEdge);
		p1 = jd.bodyA->GetWorldPoint(jd.localAnchorA);
		p2 = jd.bodyB->GetWorldPoint(jd.localAnchorB);
		d = p2 - p1;
		jd.length = d.Length();
		b2Joint* joint = m_model.m_world->CreateJoint(&jd);
		m_model.m_joints.push_back(joint);
	}
	{
		jd.bodyA = m_model.m_ground;
		jd.bodyB = m_model.m_bodies[(m_rowCount - 1) * m_colCount + m_colCount - 1];
		jd.localAnchorA.Set(m_totWidth, m_totHeight);
		if (!isConnectCenter) jd.localAnchorB.Set(m_halfNodeEdge, m_halfNodeEdge);
		p1 = jd.bodyA->GetWorldPoint(jd.localAnchorA);
		p2 = jd.bodyB->GetWorldPoint(jd.localAnchorB);
		d = p2 - p1;
		jd.length = d.Length();
		b2Joint* joint = m_model.m_world->CreateJoint(&jd);
		m_model.m_joints.push_back(joint);
	}
}

void RegularGrids::buildDeformationSprite()
{
	// shapes
	m_model.m_deformationSprite->clearShapes();
	for (size_t i = 0, n = m_model.m_tris.size(); i < n; ++i)
	{
		TriangleShape* shape = new TriangleShape;
		m_model.m_deformationSprite->pushShape(shape);
	}
	// textures
	m_model.m_deformationSprite->clearTextureRegions();
	for (size_t i = 0, n = m_model.m_tris.size(); i < n; ++i)
	{
		TextureRegion* region = new TextureRegion;
		region->filename = m_model.m_bgTexture->getFilename();
		m_model.m_deformationSprite->pushTextureRegion(region);
	}

	updateDeformationSprite();
}

void RegularGrids::updateDeformationSprite()
{
	if (m_model.m_tris.empty()) return;

	size_t size;
	// shapes
	const float width = m_model.m_bgTexture->getWidth(),
		height = m_model.m_bgTexture->getHeight();
	const std::vector<Shape*>& shapes = m_model.m_deformationSprite->getAllShapes();
	size = m_model.m_tris.size();
	assert(shapes.size() == size);
	for (size_t i = 0, n = m_model.m_tris.size(); i < n; ++i)
	{
		TriangleShape* shape = static_cast<TriangleShape*>(shapes[i]);
		assert(shape);
		const Triangle* tri = m_model.m_tris[i];
		f2Vec2 triPos[3];
		for (size_t j = 0; j < 3; ++j)
		{
			const Node* node = tri->nodes[j];
			b2Vec2 pos = node->body->GetPosition();
			if (pos.y > height * 0.5f) pos.y = height * 0.5f;
			triPos[j].set(pos.x, pos.y);
		}
		shape->setPos(triPos);
	}
	// textures
	const std::vector<TextureRegion*>& textures = m_model.m_deformationSprite->getAllTextureRegions();
	size = m_model.m_tris.size();
	assert(textures.size() == size);
	for (size_t i = 0; i < size; ++i)
	{
		TextureRegion* region = textures[i];

		Texture* texture = TexturesMgr::Instance()->getItem(region->filename);
		const float width = texture->getWidth(),
			height = texture->getHeight();

		const Triangle* tri = m_model.m_tris[i];
		for (size_t j = 0; j < 3; ++j)
		{
			const Node* node = tri->nodes[j];

			if (node->isTop)
			{
				float x = (node->body->GetPosition().x + width * 0.5f) / width,
					y = (node->body->GetPosition().y + height * 0.5f) / height;
				if (y > 1.0f) y = 1.0f;
				region->srcRegion[j].set(x, y);
			}
			else
			{
				region->srcRegion[j].set(node->texCoords.x, node->texCoords.y);
			}
			b2Vec2 pos = node->body->GetPosition();
			if (pos.y > height * 0.5f) pos.y = height * 0.5f;
			region->dstRegion[j].set(pos.x, pos.y);
		}
	}
}