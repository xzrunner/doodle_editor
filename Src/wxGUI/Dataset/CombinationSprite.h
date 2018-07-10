#ifndef _WX_GUI_COMBINATION_SPRITE_H_
#define _WX_GUI_COMBINATION_SPRITE_H_

#include "ISprite.h"

#include "CombinationSymbol.h"

namespace wxgui
{
	class CombinationSymbol;

	class CombinationSprite : public ISprite
	{
	public:
		CombinationSprite();
		CombinationSprite(const CombinationSprite& sprite);
		CombinationSprite(CombinationSymbol* symbol);
		virtual ~CombinationSprite();

		//
		// IObject interface
		//
		virtual CombinationSprite* clone();

		//
		// ISprite interface
		//
		virtual const CombinationSymbol& getSymbol() const;
		virtual void setSymbol(ISymbol* symbol);
		virtual void loadBodyFromFile();

	protected:
		virtual void buildBounding();

	protected:
		CombinationSymbol* m_symbol;

	}; // CombinationSprite
}

#endif // _WX_GUI_COMBINATION_SPRITE_H_