#include "ComplexBody.h"
#include "BodyData.h"

#include <Box2D/Box2D.h>

using namespace wxgui;

ComplexBody::ComplexBody(b2World* world, const std::vector<FixtureDataInfo>& fixtures, 
						 float scale /*= 1.0f*/)
	: IBody(world, scale)
{
	b2BodyDef bd;
	bd.type = b2_dynamicBody;
	m_body = world->CreateBody(&bd);

	for (size_t i = 0, n = fixtures.size(); i < n; ++i)
	{
		const FixtureDataInfo& info = fixtures[i];

		BodyData* data = BodyDataMgr::Instance()->getItem(info.filepath);
		if (data->type() == BodyData::e_polygon || data->type() == BodyData::e_mesh)
		{
			const float sinVal = sin(info.angle),
				cosVal = cos(info.angle);

			const std::vector<BodyData::FixtureData*>& fixturesData = data->getAllFixturesData();
			for (size_t j = 0, m = fixturesData.size(); j < m; ++j)
			{
				const BodyData::FixtureData* fixtureData = fixturesData[j];

				const size_t size = fixtureData->vertices.size();
				std::vector<b2Vec2> transList(size);
				for (size_t k = 0; k < size; ++k)
				{
					const float x = fixtureData->vertices[k].x * info.scale * scale / BOX2D_SCALE_FACTOR,
						y = fixtureData->vertices[k].y * info.scale * scale / BOX2D_SCALE_FACTOR;

					// todo: handle each scale
					transList[k].x = x * cosVal - y * sinVal + info.pos.x / BOX2D_SCALE_FACTOR;
					transList[k].y = x * sinVal + y * cosVal + info.pos.y / BOX2D_SCALE_FACTOR;
				}

				b2PolygonShape shape;
				shape.Set(&transList[0], size);

				b2FixtureDef fd;
				fd.shape = &shape;
				fd.friction = 0.5f;
				fixtureData->setFixtureDef(fd);

				m_body->CreateFixture(&fd);
			}
		}
		else if (data->type() == BodyData::e_circle)
		{
			b2FixtureDef fd;
			fd.density = 1;
			fd.restitution = 0.6f;

			b2CircleShape shape;
			shape.m_p.x = info.pos.x / BOX2D_SCALE_FACTOR;
			shape.m_p.y = info.pos.y / BOX2D_SCALE_FACTOR;
			shape.m_radius = data->getAllFixturesData()[0]->vertices[0].x * 0.5f * scale / BOX2D_SCALE_FACTOR;
			fd.shape = &shape;

			m_body->CreateFixture(&fd);
		}
	}
}

void ComplexBody::getAABB(f2AABB& aabb, const f2Vec2& position, float angle) const
{
	aabb.makeInfinite();
	for (b2Fixture* f = m_body->GetFixtureList(); f; f = f->GetNext())
	{
		b2PolygonShape* poly = dynamic_cast<b2PolygonShape*>(f->GetShape());
		if (poly)
		{
			for (size_t i = 0; i < poly->m_vertexCount; ++i)
			{
				const b2Vec2& p = poly->m_vertices[i];
				f2Vec2 transform = f2Math::rotateVector(f2Vec2(p.x, p.y), angle) + position;
				aabb.combine(transform);
			}
		}
		else 
		{
			b2Shape* shape = m_body->GetFixtureList()->GetShape();
			b2CircleShape* circle = dynamic_cast<b2CircleShape*>(shape);
			if (circle)
			{
				f2AABB part;
				part.xMin = position.x - circle->m_radius;
				part.xMax = position.x + circle->m_radius;
				part.yMin = position.y - circle->m_radius;
				part.yMax = position.y + circle->m_radius;

				aabb.combine(part);
			}
		}
	}
}