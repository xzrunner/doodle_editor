#include "SpriteDraw.h"
#include "GL10.h"
#include "SpriteBatch.h"

#include "Dataset/ISprite.h"
#include "Dataset/ISymbol.h"
#include "Dataset/ImageSprite.h"

using namespace wxgui;

void SpriteDraw::drawSprite(const ISprite* sprite)
{
	GL10::PushMatrix();

	GL10::Translatef(sprite->getPosition().x, sprite->getPosition().y, 1.0f);

	GL10::Rotatef(sprite->getAngle() * TRANS_RAD_TO_DEG, 0, 0, 1);

	bool xMirror, yMirror;
	sprite->getMirror(xMirror, yMirror);
	const float xScale = xMirror ? -sprite->getScale() : sprite->getScale(),
		yScale = yMirror ? -sprite->getScale() : sprite->getScale();
	GL10::Scalef(xScale, yScale, 1.0f);

	sprite->getSymbol().draw();

	GL10::PopMatrix();
}

void SpriteDraw::drawSprite(const ISymbol* symbol, const f2Vec2& pos,
							float angle/* = 0.0f*/, float scale/* = 1.0f*/)
{
	GL10::PushMatrix();
	GL10::Translatef(pos.x, pos.y, 1.0f);
	GL10::Scalef(scale, scale, 1.0f);
	GL10::Rotatef(angle * TRANS_RAD_TO_DEG, 0, 0, 1);
	symbol->draw();
	GL10::PopMatrix();
}

void SpriteDraw::drawSprites(const std::vector<ISprite*>& sprites,
							 SpriteBatch& batch)
{
	GL10::Enable(GL10::GL_BLEND);
	GL10::BlendFunc(GL10::GL_SRC_ALPHA, GL10::GL_ONE_MINUS_SRC_ALPHA);

	batch.clear();
	for (size_t i = 0, n = sprites.size(); i < n; ++i)
	{
// 		ImageSprite* sprite = dynamic_cast<ImageSprite*>(sprites[i]);
// 		if (sprite)
// 			batch.add(sprite);
// 		else
			SpriteDraw::drawSprite(static_cast<ISprite*>(sprites[i]));
	}
	batch.onDraw();

	GL10::Disable(GL10::GL_BLEND);
}

void SpriteDraw::begin(const ISprite* sprite)
{
	GL10::PushMatrix();
	GL10::Translatef(sprite->getPosition().x, sprite->getPosition().y, 1.0f);
	GL10::Rotatef(sprite->getAngle() * TRANS_RAD_TO_DEG, 0, 0, 1);
}

void SpriteDraw::end(const ISprite* sprite)
{
	GL10::PopMatrix();
}