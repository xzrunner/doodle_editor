#include "ObstacleBridgeData.h"

using namespace deditor::motox;

const float BridgeData::OVERLAP_RATIO = 0.0f;

BridgeData::BridgeData(b2World* world, b2Body* ground, wxgui::ImageSymbol* symbol)
	: m_world(world)
	, m_ground(ground)
{
	m_tileWidth = symbol->getWidth();
	m_tileHeight = symbol->getHeight();
}

BridgeData::~BridgeData()
{
	clear();
}

void BridgeData::assemblyVertexArray(std::vector<f2Vec2>& vertices, std::vector<f2Vec2>& texCoords)
{
	vertices.resize(m_bodies.size() * 2 * 3);
	texCoords.resize(m_bodies.size() * 2 * 3);

	int index = 0;
	for (size_t i = 0, n = m_bodies.size(); i < n; ++i)
	{
		b2Body* body = m_bodies[i];

		const b2Vec2& pos = body->GetPosition();
		f2Vec2 quad[4];
		wxgui::Math::computeQuadNodes(f2Vec2(pos.x * BOX2D_SCALE_FACTOR, pos.y * BOX2D_SCALE_FACTOR), 
			body->GetAngle(), 1.0f, m_tileWidth, m_tileHeight, quad);

		vertices[index] = quad[0];
		texCoords[index].set(0, 0);
		++index;
		vertices[index] = quad[3];
		texCoords[index].set(1, 0);
		++index;
		vertices[index] = quad[2];
		texCoords[index].set(1, 1);
		++index;

		vertices[index] = quad[0];
		texCoords[index].set(0, 0);
		++index;
		vertices[index] = quad[2];
		texCoords[index].set(1, 1);
		++index;
		vertices[index] = quad[1];
		texCoords[index].set(0, 1);		
		++index;
	}
}

void BridgeData::build(const f2Vec2& start, const f2Vec2& end)
{
	clear();

	f2Vec2 bStart = start / BOX2D_SCALE_FACTOR,
		bEnd = end / BOX2D_SCALE_FACTOR;

	const float width = m_tileWidth - 6,
		height = m_tileHeight - 2;

	const int size = std::floor(f2Math::getDistance(bStart, bEnd) / (width / BOX2D_SCALE_FACTOR * (1 - OVERLAP_RATIO * 2)));
	if (size < 2) return;

	const float angle = f2Math::getLineAngle(bStart, bEnd);
	const float tileLen = width / BOX2D_SCALE_FACTOR;

	b2PolygonShape shape;
	shape.SetAsBox(width / BOX2D_SCALE_FACTOR * 0.5f, height / BOX2D_SCALE_FACTOR * 0.5f);

	b2FixtureDef fd;
	fd.shape = &shape;
	fd.density = 1.0f;
	fd.friction = 1.0f;

	b2RevoluteJointDef rjd;
	rjd.collideConnected = false;

	b2Body* prevBody = m_ground;
	for (size_t i = 0; i < size; ++i)
	{
		b2BodyDef bd;
		bd.type = b2_dynamicBody;
		const float x = bStart.x + ((0.5f - OVERLAP_RATIO) + (1 - OVERLAP_RATIO) * i) * tileLen * cos(angle),
			y = bStart.y + ((0.5f - OVERLAP_RATIO) + (1 - OVERLAP_RATIO) * i) * tileLen * sin(angle);
		bd.position.Set(x, y);
		bd.angle = angle;
		b2Body* body = m_world->CreateBody(&bd);
		m_bodies.push_back(body);
		body->CreateFixture(&fd);

		b2Vec2 anchor(bStart.x + (1 - OVERLAP_RATIO * 2) * tileLen * i * cos(angle), bStart.y + (1 - OVERLAP_RATIO * 2) * tileLen * i * sin(angle));
		rjd.Initialize(prevBody, body, anchor);
		b2RevoluteJoint* joint = (b2RevoluteJoint*)m_world->CreateJoint(&rjd);
		m_joints.push_back(joint);

		prevBody = body;
	}
	rjd.Initialize(prevBody, m_ground, b2Vec2(bEnd.x, bEnd.y));
	b2RevoluteJoint* joint = (b2RevoluteJoint*)m_world->CreateJoint(&rjd);
	m_joints.push_back(joint);
}

//void BridgeData::draw(float radius) const
//{
//	unsigned int id;
//	float width, height;
//	m_symbol->getTextureInfo(id, width, height);
//
//	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
//
//	glBindTexture(GL_TEXTURE_2D, id);
//	const float h_width = width * 0.5f,
//		h_height = height * 0.5f;
//	for (size_t i = 0, n = m_bodies.size(); i < n; ++i)
//	{
//		glPushMatrix();
//
//		glTranslatef(m_bodies[i]->GetPosition().x * BOX2D_SCALE_FACTOR, m_bodies[i]->GetPosition().y * BOX2D_SCALE_FACTOR, 1.0f);
//		glRotatef(m_bodies[i]->GetAngle() * TRANS_RAD_TO_DEG, 0, 0, 1);
//
//		glBegin(GL_TRIANGLES);
//			// right down
//			glTexCoord2f(0.0f, 0.0f); glVertex3f(-h_width, -h_height, -1);
//			glTexCoord2f(1.0f, 0.0f); glVertex3f( h_width, -h_height, -1);
//			glTexCoord2f(1.0f, 1.0f); glVertex3f( h_width,  h_height, -1);
//			// left up
//			glTexCoord2f(0.0f, 0.0f); glVertex3f(-h_width, -h_height, -1);
//			glTexCoord2f(1.0f, 1.0f); glVertex3f( h_width,  h_height, -1);
//			glTexCoord2f(0.0f, 1.0f); glVertex3f(-h_width,  h_height, -1);
//		glEnd();
//
//		glPopMatrix();
//	}
//
//	wxgui::Render::drawCircle(m_start, radius, f2Colorf(0.8f, 0.2f, 0.2f));
//	wxgui::Render::drawCircle(m_end, radius, f2Colorf(0.8f, 0.2f, 0.2f));
//}

void BridgeData::clear()
{
	for (size_t i = 0, n = m_joints.size(); i < n; ++i)
		m_world->DestroyJoint(m_joints[i]);
	for (size_t i = 0, n = m_bodies.size(); i < n; ++i)
		m_world->DestroyBody(m_bodies[i]);
	m_joints.clear();
	m_bodies.clear();
}