#ifndef _WX_GUI_SHAPE_SPRITE_H_
#define _WX_GUI_SHAPE_SPRITE_H_

#include "ISprite.h"

#include "ShapeSymbol.h"

namespace wxgui
{
	class ShapeSymbol;

	class ShapeSprite : public ISprite
	{
	public:
		ShapeSprite();
		ShapeSprite(const ShapeSprite& sprite);
		ShapeSprite(ShapeSymbol* symbol);
		virtual ~ShapeSprite();

		//
		// IObject interface
		//
		virtual ShapeSprite* clone();

		//
		// ISprite interface
		//
		virtual const ShapeSymbol& getSymbol() const;
		virtual void setSymbol(ISymbol* symbol);
		virtual void loadBodyFromFile();
		
	protected:
		virtual void buildBounding();

	private:
		ShapeSymbol* m_symbol;

	}; // ShapeSprite
}

#endif // _WX_GUI_SHAPE_SPRITE_H_