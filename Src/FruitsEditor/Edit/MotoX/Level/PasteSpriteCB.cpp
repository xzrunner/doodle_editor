#include "PasteSpriteCB.h"
#include "TypesDef.h"
#include "Model.h"
#include "Dataset/Sprite.h"
#include "Dataset/Layer.h"
#include <Box2D/Box2D.h>

using namespace FEDITOR;
using namespace FEDITOR::MOTOX::LEVEL;

PasteSpriteCB::PasteSpriteCB(Model* model)
{
	m_model = model;
}

void PasteSpriteCB::afterAddSprite(Sprite* sprite)
{
	if (sprite->getBody() && sprite->getBody()->getBody())
	{
		int* type = new int;
		*type = e_Stone;
		sprite->getBody()->getBody()->SetUserData(type);
	}

	m_model->addToBodySpriteMap(sprite);
}