#include "ObstacleSoftData.h"
#include "TypesDef.h"

using namespace deditor::motox;

//////////////////////////////////////////////////////////////////////////
// class SoftData
//////////////////////////////////////////////////////////////////////////

SoftData::SoftData(b2World* world)
	: m_world(world)
{
}

SoftData::~SoftData()
{
	clear();
}

void SoftData::clear()
{
	for (size_t i = 0, n = m_joints.size(); i < n; ++i)
		m_world->DestroyJoint(m_joints[i]);
	m_joints.clear();

	for (size_t i = 0, n = m_nodes.size(); i < n; ++i)
	{
		m_world->DestroyBody(m_nodes[i]->body);
		delete m_nodes[i];
	}
	m_nodes.clear();
}

f2Vec2 SoftData::Node::
getPosition() const
{
	f2Vec2 ret;
	ret.x = body->GetPosition().x * BOX2D_SCALE_FACTOR;
	ret.y = body->GetPosition().y * BOX2D_SCALE_FACTOR;
	return ret;
}

//////////////////////////////////////////////////////////////////////////
// class SoftPolyData
//////////////////////////////////////////////////////////////////////////

SoftPolyData::SoftPolyData(b2World* world)
	: SoftData(world)
	, m_row(0)
	, m_col(0)
{
}

void SoftPolyData::build(const SoftDataDef& def, const f2Vec2& center)
{
	clear();

	m_row = def.height / def.edge;
	m_col = def.width / def.edge;

	b2PolygonShape shape;
	shape.SetAsBox(def.nodeHalfEdge, def.nodeHalfEdge);
	b2BodyDef bd;
	bd.type = b2_dynamicBody;
	const float xOffset = (-def.width * 0.5f + center.x) / BOX2D_SCALE_FACTOR,
		yOffset = (-def.height * 0.5f + center.y) / BOX2D_SCALE_FACTOR;
	const float wGrid = (float) def.width / (m_col - 1) / BOX2D_SCALE_FACTOR,
		hGrid = (float) def.height / (m_row - 1) / BOX2D_SCALE_FACTOR;
	for (size_t i = 0; i < m_row; ++i)
	{
		for (size_t j = 0; j < m_col; ++j)
		{
			Node* node = new Node;

			node->texCoords.x = (float)j / (m_col - 1);
			node->texCoords.y = (float)i / (m_row - 1);

			bd.position.Set(xOffset + wGrid * j, yOffset + hGrid * i);
			node->body = m_world->CreateBody(&bd);
			node->body->CreateFixture(&shape, 0.0f);
			node->body->SetUserData(new int(CARTON_ID));

			m_nodes.push_back(node);
		}
	}

	b2DistanceJointDef jd;
	b2Vec2 p1, p2, d;
	jd.collideConnected = true;
	jd.frequencyHz = def.frequencyHz;
	jd.dampingRatio = def.dampingRatio;
	for (size_t i = 0; i < m_row; ++i)
	{
		for (size_t j = 1; j < m_col; ++j)
		{
			jd.bodyA = m_nodes[i * m_col + j - 1]->body;
			jd.bodyB = m_nodes[i * m_col + j]->body;
			// 			if (!connectCenter)
			// 			{
			// 				jd.localAnchorA.Set(halfEdge, 0.0f);
			// 				jd.localAnchorB.Set(-halfEdge, 0.0f);
			// 			}
			p1 = jd.bodyA->GetWorldPoint(jd.localAnchorA);
			p2 = jd.bodyB->GetWorldPoint(jd.localAnchorB);
			d = p2 - p1;
			jd.length = d.Length();
			b2Joint* joint = m_world->CreateJoint(&jd);
			m_joints.push_back(joint);
		}
	}
	for (size_t i = 0; i < m_col; ++i)
	{
		for (size_t j = 1; j < m_row; ++j)
		{
			jd.bodyA = m_nodes[(j - 1) * m_col + i]->body;
			jd.bodyB = m_nodes[j * m_col + i]->body;
			// 			if (!connectCenter)
			// 			{
			// 				jd.localAnchorA.Set(0.0f, halfEdge);
			// 				jd.localAnchorB.Set(0.0f, -halfEdge);
			// 			}
			p1 = jd.bodyA->GetWorldPoint(jd.localAnchorA);
			p2 = jd.bodyB->GetWorldPoint(jd.localAnchorB);
			d = p2 - p1;
			jd.length = d.Length();
			b2Joint* joint = m_world->CreateJoint(&jd);
			m_joints.push_back(joint);
		}
	}
	for (size_t i = 0; i < m_row - 1; ++i)
	{
		for (size_t j = 0; j < m_col - 1; ++j)
		{
			Node *leftLow = m_nodes[m_col * i + j],
				*leftUp = m_nodes[m_col * i + m_col + j],
				*rightLow = m_nodes[m_col * i + j + 1],
				*rightUp = m_nodes[m_col * i + m_col + j + 1];
			{
				jd.bodyA = leftLow->body;
				jd.bodyB = rightUp->body;
				p1 = jd.bodyA->GetWorldPoint(jd.localAnchorA);
				p2 = jd.bodyB->GetWorldPoint(jd.localAnchorB);
				d = p2 - p1;
				jd.length = d.Length();
				b2Joint* joint = m_world->CreateJoint(&jd);
				m_joints.push_back(joint);
			}
			{
				jd.bodyA = leftUp->body;
				jd.bodyB = rightLow->body;
				p1 = jd.bodyA->GetWorldPoint(jd.localAnchorA);
				p2 = jd.bodyB->GetWorldPoint(jd.localAnchorB);
				d = p2 - p1;
				jd.length = d.Length();
				b2Joint* joint = m_world->CreateJoint(&jd);
				m_joints.push_back(joint);
			}
		}
	}
}

void SoftPolyData::assemblyVertexArray(std::vector<f2Vec2>& vertices, std::vector<f2Vec2>& texCoords)
{
	if (m_row < 2 && m_col < 2) return;

	const size_t size = (m_row - 1) * (m_col - 1) * 2 * 3;
	vertices.resize(size);
	texCoords.resize(size);
	int index = 0;
	for (size_t i = 0; i < m_row - 1; ++i)
	{
		for (size_t j = 0; j < m_col - 1; ++j)
		{
			Node *leftLow = m_nodes[m_col * i + j],
				*leftUp = m_nodes[m_col * i + m_col + j],
				*rightLow = m_nodes[m_col * i + j + 1],
				*rightUp = m_nodes[m_col * i + m_col + j + 1];

			vertices[index] = leftLow->getPosition();
			texCoords[index] = leftLow->texCoords;
			++index;
			vertices[index] = rightLow->getPosition();
			texCoords[index] = rightLow->texCoords;
			++index;
			vertices[index] = leftUp->getPosition();
			texCoords[index] = leftUp->texCoords;
			++index;

			vertices[index] = rightLow->getPosition();
			texCoords[index] = rightLow->texCoords;
			++index;
			vertices[index] = rightUp->getPosition();
			texCoords[index] = rightUp->texCoords;
			++index;
			vertices[index] = leftUp->getPosition();
			texCoords[index] = leftUp->texCoords;
			++index;
		}
	}
}

//////////////////////////////////////////////////////////////////////////
// class SoftPolyData
//////////////////////////////////////////////////////////////////////////

SoftCircleData::SoftCircleData(b2World* world)
	: SoftData(world)
	, m_count(0)
	, m_texScale(1.0f)
{
}

void SoftCircleData::build(const SoftDataDef& def, const f2Vec2& center)
{
	clear();

	const float radius = std::min(def.width, def.height) * 0.5f;
//	m_count = 2 * PI * radius / def.edge;
	m_count = 16;

	const float angleStep = (PI * 2.0f) / m_count;
	const float sinHalfAngle = sin(angleStep * 0.5f);
	const float subCircleRadius = sinHalfAngle * radius / (1.0f + sinHalfAngle);

	b2CircleShape circleShape;
	circleShape.m_radius = (radius - subCircleRadius * 2.0) * 0.5 / BOX2D_SCALE_FACTOR;

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &circleShape;
	fixtureDef.density = 1.0f;
	fixtureDef.restitution = 0.05f;
	fixtureDef.friction = 1.0f;

	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;

	Node* centerNode = new Node;
	centerNode->texCoords.x = centerNode->texCoords.y = 0.5f;
	bodyDef.position.Set(center.x / BOX2D_SCALE_FACTOR, center.y / BOX2D_SCALE_FACTOR);
	centerNode->body = m_world->CreateBody(&bodyDef);
	centerNode->body->CreateFixture(&fixtureDef);
	m_nodes.push_back(centerNode);

	circleShape.m_radius = subCircleRadius / BOX2D_SCALE_FACTOR;
	for (size_t i = 0; i < m_count; ++i)
	{
		Node* node = new Node;

		float angle = 2 * PI / m_count * i;
		float cosVal = cos(angle), sinVal = sin(angle);

		node->texCoords.x = 0.5f + 0.5f * cosVal;
		node->texCoords.y = 0.5f + 0.5f * sinVal;

		bodyDef.position.x = (center.x + (radius - subCircleRadius) * cosVal) / BOX2D_SCALE_FACTOR;
		bodyDef.position.y = (center.y + (radius - subCircleRadius) * sinVal) / BOX2D_SCALE_FACTOR;
		node->body = m_world->CreateBody(&bodyDef);
		node->body->CreateFixture(&fixtureDef);

		m_nodes.push_back(node);
	}

	m_texScale = radius / (radius - subCircleRadius);

	b2DistanceJointDef jd;
	b2Vec2 p1, p2, d;
	jd.collideConnected = true;
	jd.frequencyHz = def.frequencyHz;
	jd.dampingRatio = def.dampingRatio;
	for (size_t i = 0; i < m_count; ++i)
	{
		{
			jd.bodyA = m_nodes[1 + i]->body;
			jd.bodyB = m_nodes[0]->body;
			p1 = jd.bodyA->GetWorldPoint(jd.localAnchorA);
			p2 = jd.bodyB->GetWorldPoint(jd.localAnchorB);
			d = p2 - p1;
			jd.length = d.Length();
			b2Joint* joint = m_world->CreateJoint(&jd);
			m_joints.push_back(joint);
		}
		{
			jd.bodyA = m_nodes[1 + i]->body;
			jd.bodyB = (i == m_count - 1) ? m_nodes[1]->body : m_nodes[1 + i + 1]->body;
			p1 = jd.bodyA->GetWorldPoint(jd.localAnchorA);
			p2 = jd.bodyB->GetWorldPoint(jd.localAnchorB);
			d = p2 - p1;
			jd.length = d.Length();
			b2Joint* joint = m_world->CreateJoint(&jd);
			m_joints.push_back(joint);
		}
	}
}

void SoftCircleData::assemblyVertexArray(std::vector<f2Vec2>& vertices, std::vector<f2Vec2>& texCoords)
{
	if (m_count < 3) return;

	const size_t size = m_count * 3;
	vertices.resize(size);
	texCoords.resize(size);
	int index = 0;
	for (size_t i = 0; i < m_count; ++i)
	{
		vertices[index] = m_nodes[0]->getPosition() + (m_nodes[1 + i]->getPosition() - m_nodes[0]->getPosition()) * m_texScale;
		texCoords[index] = m_nodes[1 + i]->texCoords;
		++index;

		int next = (i == m_count - 1) ? 1 : 1 + i + 1;
		vertices[index] = m_nodes[0]->getPosition() + (m_nodes[next]->getPosition() - m_nodes[0]->getPosition()) * m_texScale;
		texCoords[index] = m_nodes[next]->texCoords;
		++index;

		vertices[index] = m_nodes[0]->getPosition();
		texCoords[index] = m_nodes[0]->texCoords;
		++index;
	}
}
