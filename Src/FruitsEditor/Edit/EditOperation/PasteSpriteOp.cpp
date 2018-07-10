#include "PasteSpriteOp.h"
#include "IPasteSpriteCB.h"
#include "../../Dataset/Sprite.h"
#include "../../Dataset/Layer.h"
#include "../../Dataset/Texture.h"
#include "../../Dataset/Body.h"
#include "../../File/ImgFileAdapter.h"

using namespace FEDITOR;

PasteSpriteOp::PasteSpriteOp(AbstractControl* task, Layer* templayer, Layer* dstLayer,
							 const std::string& filename, bool toInteger/* = false*/, IPasteSpriteCB* callback/* = NULL*/,
							 float xScale/* = 1.0f*/, float yScale/* = 1.0f*/, int batchNum/* = 0*/, int batchRadius/* = 0*/)
	: AbstractOp(task)
{
	m_templayer = templayer;
	m_dstLayer = dstLayer;

	m_callback = callback;

	m_filename = filename;
	m_toInteger = toInteger;
	m_xScale = xScale;
	m_yScale = yScale;

	m_batchNum = batchNum;
	m_batchRadius = batchRadius;

	m_sprite = new Sprite;
	m_sprite->setScale(m_xScale, m_yScale);
	m_sprite->loadFromUnknownFile(filename);
	m_sprite->setBody(NULL);
	m_templayer->addSprite(m_sprite);
}

PasteSpriteOp::~PasteSpriteOp()
{
	m_templayer->clearSprites();
	if (m_callback) delete m_callback;
}

void PasteSpriteOp::onMouseLeftDown(int x, int y)
{
	f2Vec2 pos = getMousePos(x, y);
	if (m_toInteger) pos.toInteger();
	addSprite(pos, 0);
}

bool PasteSpriteOp::onMouseRightDown(int x, int y)
{
	return false;
}

void PasteSpriteOp::onMouseMove(int x, int y)
{
	f2Vec2 pos = getMousePos(x, y);
	if (m_toInteger) pos.toInteger();
	m_sprite->setTransform(pos, 0);	
}

void PasteSpriteOp::onMouseDrag(int x, int y)
{
	if (m_batchNum == 0 && m_batchRadius == 0) return;

	for (size_t i = 0; i < m_batchNum; ++i)
	{
		int radius = m_batchRadius * Random::getNum0To1();
		int nx = x + radius * sin(Random::getRadian()),
			ny = y + radius * cos(Random::getRadian());

		addSprite(getMousePos(nx, ny), Random::getRadian());
	}
}

void PasteSpriteOp::addSprite(f2Vec2& pos, float angle)
{
	Sprite* sprite = new Sprite;
	sprite->setScale(m_xScale, m_yScale);

	sprite->loadFromUnknownFile(m_filename);

	Body* body = sprite->getBody();
	if (body) body->setAlive(true);

	if (m_toInteger) pos.toInteger();
	sprite->setTransform(pos, 0);

	m_dstLayer->addSprite(sprite);

	if (m_callback) m_callback->afterAddSprite(sprite);
}