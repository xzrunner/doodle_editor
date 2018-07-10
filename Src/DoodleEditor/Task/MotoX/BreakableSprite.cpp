#include "BreakableSprite.h"
#include "TypesDef.h"

using namespace deditor::motox;

BreakableSprite::BreakableSprite()
	: m_item(NULL)
{
}

BreakableSprite::BreakableSprite(const BreakableSprite& sprite)
	: wxgui::CombinationSprite(sprite)
	, m_item(sprite.m_item)
{
}

BreakableSprite::BreakableSprite(LibraryBreakableItem* symbol, bool useMeshes)
	: m_item(symbol)
{
	m_symbol = useMeshes ? const_cast<wxgui::CombinationSymbol*>(symbol->getMeshCombineSymbol())
		: const_cast<wxgui::CombinationSymbol*>(symbol->getSpriteCombineSymbol());

	buildBounding();
}

BreakableSprite::BreakableSprite(wxgui::CombinationSymbol* symbol)
	: wxgui::CombinationSprite(symbol)
	, m_item(NULL)
{
	buildBounding();
}

BreakableSprite* BreakableSprite::clone()
{
	return new BreakableSprite(*this);
}

void BreakableSprite::breakToPiecesOld(std::vector<wxgui::ISprite*>& pieces,
									   const f2Vec2& pos) const
{
 	assert(m_body);
 
 	const std::vector<wxgui::ISprite*>& children = m_symbol->getChildren();
 	for (size_t i = 0, n = children.size(); i < n; ++i)
 	{
		wxgui::ISprite* child = children[i];
		wxgui::ISprite* sprite;
		if (dynamic_cast<wxgui::ImageSprite*>(child))
		{
			sprite = new BreakableSprite(m_item, true);
			sprite->setTransform(child->getPosition(), child->getAngle());
			sprite->setScale(child->getScale());

			initPartPhysics(sprite, false);
		}
		else
		{
			sprite = children[i]->clone();
			initPartPhysics(sprite, true);
		}

 		pieces.push_back(sprite);
 	}
}

void BreakableSprite::breakToPieces(std::vector<wxgui::ISprite*>& pieces,
									const f2Vec2& pos) const
{
	assert(m_body);

	const std::vector<wxgui::ISprite*>& children = m_symbol->getChildren();
	if (children.empty()) return;

	// break all to ImageSprite
	if (dynamic_cast<wxgui::ImageSprite*>(children[0]))
	{
		for (size_t i = 0, n = children.size(); i < n; ++i)
		{
			wxgui::ISprite* child = children[i];
			assert(dynamic_cast<wxgui::ImageSprite*>(child));

			wxgui::ISprite* sprite = new BreakableSprite(m_item, true);
 			sprite->setTransform(child->getPosition(), child->getAngle());
 			sprite->setScale(child->getScale());

			initPartPhysics(sprite, false);

			pieces.push_back(sprite);
		}
	}
	// only break at pos
	else
	{
		size_t breakPos = 0;
		float minDis = FLOAT_MAX;
		for (size_t i = 0, n = children.size() - 1; i < n; ++i)
		{
			f2Vec2 mid = (children[i]->getPosition() + children[i+1]->getPosition()) * 0.5f;
			float dis = f2Math::getDistance(pos, mid);
			if (dis < minDis)
			{
				minDis = dis;
				breakPos = i;
			}
		}

		std::vector<wxgui::ISprite*> left, right;
		for (size_t i = 0; i <= breakPos; ++i)
			left.push_back(children[i]);
		for (size_t i = breakPos + 1, n = children.size(); i < n; ++i)
			right.push_back(children[i]);
		assert(!left.empty() && !right.empty());
		pieces.push_back(combineMeshes(left));
		pieces.push_back(combineMeshes(right));
	}
}

const wxString& BreakableSprite::getFilepath() const
{
	return m_item->getFilepath();
}

wxgui::ISprite* BreakableSprite::combineMeshes(const std::vector<wxgui::ISprite*>& meshes) const
{
	wxgui::ISprite* sprite;
	if (meshes.size() == 1)
	{
		sprite = meshes[0]->clone();
		sprite->setScale(m_scale);
		initPartPhysics(sprite, true);
	}
	else
	{
		wxgui::CombinationSymbol* symbol = new wxgui::CombinationSymbol(meshes);
		sprite = new BreakableSprite(symbol);
		sprite->setScale(m_scale);
		initPartPhysics(sprite, false);
	}

	return sprite;
}

void BreakableSprite::initPartPhysics(wxgui::ISprite* part, bool isPiece) const
{
	part->loadBodyFromFile();
	part->setTransform(m_pos + part->getPosition(), m_angle + part->getAngle());

	b2Vec2 velocity = m_body->getBody()->GetLinearVelocity();
	float32 angularVelocity = m_body->getBody()->GetAngularVelocity();

	b2Body* body = part->getBody()->getBody();
	body->SetUserData(new int(isPiece ? PIECE_ID : BREAKABLE_ID));
	body->SetAngularVelocity(angularVelocity);
	b2Vec2 velocityChild = velocity + b2Cross(angularVelocity, 
		body->GetWorldCenter() - m_body->getBody()->GetWorldCenter());
	body->SetLinearVelocity(velocityChild);
}