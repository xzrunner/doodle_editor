#include "BreakableSprite.h"
#include "CommonSprite.h"
#include "MeshSprite.h"
#include "ObstaclesInfoLoader.h"

#include "Tools/connect_id_defs.h"

using namespace motox;

BreakableSprite::BreakableSprite(b2World* world, const d2d::TextureInfo& texInfo,
								 ObstaclesInfoLoader& obstaclesInfo,
								 int meshCombinationID)
	: m_world(world)
	, m_textureInfo(texInfo)
	, m_obstaclesInfo(obstaclesInfo)
	, m_meshCombinationID(meshCombinationID)
{
}

BreakableSprite::~BreakableSprite()
{
}

void BreakableSprite::breakToPieces(const d2d::Vector& pos,
									std::vector<IObstacleSprite*>& pieces)
{
	if (m_children.empty()) return;

	assert(m_physics);

	if (m_canBreakToCommon)
		breakToCommon(pieces);
	else
		breakToMeshes(pos, pieces);

	delete m_physics, m_physics = NULL;
}

void BreakableSprite::breakToCommon(std::vector<IObstacleSprite*>& pieces)
{
	for (size_t i = 0, n = m_children.size(); i < n; ++i)
	{
 	//	//////////////////////////////////////////////////////////////////////////
		//// break to piece
		////////////////////////////////////////////////////////////////////////////
 	//	CommonSprite* child = dynamic_cast<CommonSprite*>(m_children[i]->sprite);
 	//	assert(child);
 
 	//	child->m_physics = d2d::BodyFactory::createPolygons(m_world, m_textureInfo.getRegion(child->m_texID)->loops);
 	//	initPartPhysics(child, m_children[i]->offset, m_children[i]->delta, true);
 
 	//	pieces.push_back(child);

		//////////////////////////////////////////////////////////////////////////
		// break to breakable
		//////////////////////////////////////////////////////////////////////////
		BreakableSprite* breakable = new BreakableSprite(m_world, m_textureInfo, m_obstaclesInfo, m_meshCombinationID);
		breakable->m_canBreakToCommon = false;
		ObstaclesInfoLoader::CombineData* data = m_obstaclesInfo.m_combinesData[m_meshCombinationID];
		for (size_t j = 0, m = data->entries.size(); j < m; ++j)
		{
			CombinationSprite::Part* part = new CombinationSprite::Part;
			assert(data->entries[i].id < m_textureInfo.regionSize() + m_obstaclesInfo.m_meshesData.size());

			MeshSprite* sprite = new MeshSprite(m_children[i]->scale);
			sprite->m_meshID = data->entries[j].id - m_textureInfo.regionSize();
			sprite->m_mesh = m_obstaclesInfo.m_meshesData[sprite->m_meshID]->mesh;

			part->sprite = sprite;
			part->offset = data->entries[i].pos;
			part->delta = data->entries[i].angle;
			part->scale = data->entries[i].scale * m_children[i]->scale;

			breakable->m_children.push_back(part);
		}
		breakable->m_physics = d2d::BodyFactory::createPolygons(m_world, data->fixtures, m_children[i]->scale);
		initPartPhysics(breakable, m_children[i]->offset, m_children[i]->delta, false);
		breakable->update();
		pieces.push_back(breakable);
	}
}

void BreakableSprite::breakToMeshes(const d2d::Vector& pos, std::vector<IObstacleSprite*>& pieces)
{
	size_t breakPos = 0;
	float minDis = d2d::FLOAT_MAX;
	for (size_t i = 0, n = m_children.size() - 1; i < n; ++i)
	{
		d2d::Vector mid = (m_children[i]->sprite->getPosition() + m_children[i+1]->sprite->getPosition()) * 0.5f;
		float dis = d2d::getDistance(pos, mid);
		if (dis < minDis)
		{
			minDis = dis;
			breakPos = i;
		}
	}

	std::vector<Part*> left, right;
	for (size_t i = 0; i <= breakPos; ++i)
		left.push_back(m_children[i]);
	for (size_t i = breakPos + 1, n = m_children.size(); i < n; ++i)
		right.push_back(m_children[i]);
	assert(!left.empty() && !right.empty());
	pieces.push_back(combineMeshes(left));
	pieces.push_back(combineMeshes(right));
}

IObstacleSprite* BreakableSprite::combineMeshes(const std::vector<Part*>& pieces)
{
	std::vector<std::vector<d2d::Vector> > fixtures;
	for (size_t i = 0, n = pieces.size(); i < n; ++i)
	{
		MeshSprite* meshSprite = static_cast<MeshSprite*>(pieces[i]->sprite);

		//////////////////////////////////////////////////////////////////////////
		// Probably
		//////////////////////////////////////////////////////////////////////////

		ObstaclesInfoLoader::MeshData* data = m_obstaclesInfo.m_meshesData[meshSprite->m_meshID];

		std::vector<d2d::Vector> loop(4);
		loop[0] = d2d::Vector(data->left, data->low);
		loop[1] = d2d::Vector(data->right, data->low);
		loop[2] = d2d::Vector(data->right, data->top);
		loop[3] = d2d::Vector(data->left, data->top);
		if (pieces[i]->scale == 1.0f)
		{
			for (size_t j = 0; j < 4; ++j)
			{
				d2d::Vector trans;
				d2d::rotateVector(loop[j], pieces[i]->delta, trans);
				trans += pieces[i]->offset;
				loop[j] = trans;
			}
		}
		else
		{
			for (size_t j = 0; j < 4; ++j)
			{
				d2d::Vector trans;
				d2d::rotateVector(loop[j] * pieces[i]->scale, pieces[i]->delta, trans);
				trans += pieces[i]->offset;
				loop[j] = trans;
			}
		}
		fixtures.push_back(loop);

		//////////////////////////////////////////////////////////////////////////
		// Accurate
		//////////////////////////////////////////////////////////////////////////
 
// 		d2d::Mesh* mesh = m_obstaclesInfo.m_meshesData[meshSprite->m_meshID]->mesh;
// 		int index = 0;
// 		for (size_t j = 0, m = mesh->m_vertices.size() / 3; j < m; ++j)
// 		{
// 			std::vector<d2d::Vector> loop(3);
// 			for (size_t k = 0; k < 3; ++k)
// 			{
// 				d2d::Vector trans;
// 				d2d::rotateVector(d2d::Vector(mesh->m_vertices[index].x, mesh->m_vertices[index].y) * pieces[i]->scale, 
// 					pieces[i]->delta, trans);
// 				trans += pieces[i]->offset;
// 				loop[k] = trans;
// 				++index;
// 			}
// 			fixtures.push_back(loop);
// 		}
	}

	IObstacleSprite* sprite;
	if (pieces.size() == 1)
	{
		pieces[0]->sprite->retain();
		sprite = pieces[0]->sprite;
		sprite->m_physics = d2d::BodyFactory::createPolygons(m_world, fixtures);
		initPartPhysics(sprite, pieces[0]->offset, pieces[0]->delta, true);
	}
	else
	{
		BreakableSprite* breakable = new BreakableSprite(m_world, 
			m_textureInfo, m_obstaclesInfo, m_meshCombinationID);
		breakable->m_canBreakToCommon = false;

		for (size_t i = 0, n = pieces.size(); i < n; ++i)
			pieces[i]->retain();
		breakable->m_children = pieces;

		sprite = breakable;
		sprite->m_physics = d2d::BodyFactory::createPolygons(m_world, fixtures);
		initPartPhysics(sprite, d2d::Vector(), 0, false);
		sprite->update();
	}

	return sprite;
}

void BreakableSprite::initPartPhysics(IObstacleSprite* part, const d2d::Vector& offset, 
									  float delta, bool isPiece) const
{
	part->setTransform(m_location + offset, m_angle + delta);

	b2Vec2 velocity = m_physics->getBody()->GetLinearVelocity();
	float32 angularVelocity = m_physics->getBody()->GetAngularVelocity();

	b2Body* body = part->m_physics->getBody();
	body->SetUserData(new int(isPiece ? PIECE_ID : BREAKABLE_ID));
	body->SetAngularVelocity(angularVelocity);
	b2Vec2 velocityChild = velocity + b2Cross(angularVelocity, 
		body->GetWorldCenter() - m_physics->getBody()->GetWorldCenter());
	body->SetLinearVelocity(velocityChild);
}