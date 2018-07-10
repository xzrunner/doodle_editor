#include "SpriteFactory.h"
#include "ImageSprite.h"
#include "ShapeSprite.h"
#include "MeshSprite.h"
#include "CombinationSprite.h"

using namespace wxgui;

ISprite* SpriteFactory::create(ISymbol* symbol)
{
	ImageSymbol* image = dynamic_cast<ImageSymbol*>(symbol);
	if (image) return new ImageSprite(image);

	ShapeSymbol* shape = dynamic_cast<ShapeSymbol*>(symbol);
	if (shape) return new ShapeSprite(shape);

	MeshSymbol* mesh = dynamic_cast<MeshSymbol*>(symbol);
	if (mesh) return new MeshSprite(mesh);

	CombinationSymbol* combination = dynamic_cast<CombinationSymbol*>(symbol);
	if (combination) return new CombinationSprite(combination);

	return NULL;
}