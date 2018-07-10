#include "ArrangeSpriteCB.h"
#include "Model.h"

using namespace FEDITOR;
using namespace FEDITOR::TEXTURE_MERGE;

ArrangeSpriteCB::ArrangeSpriteCB(Model* model)
{
	m_model = model;
}

void ArrangeSpriteCB::deleteSprite(Sprite* sprite)
{
	m_model->deleteTexture(sprite);
}