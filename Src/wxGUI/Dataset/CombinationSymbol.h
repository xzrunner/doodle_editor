#ifndef _WX_GUI_COMBINATION_SYMBOL_H_
#define _WX_GUI_COMBINATION_SYMBOL_H_

#include "ISymbol.h"

namespace wxgui
{
	class ISprite;

	class CombinationSymbol : public ISymbol
	{
	public:
		CombinationSymbol();
		CombinationSymbol(const std::vector<ISprite*>& children);
		virtual ~CombinationSymbol();

		//
		// IObject interface
		//	
		virtual CombinationSymbol* clone();

		//
		// ISerializable interface
		//
		virtual void loadFromTextFile(std::ifstream& fin);
		virtual void storeToTextFile(std::ofstream& fout) const;

		//
		// ISymbol interface
		//
		virtual void reloadTexture() const;
		virtual void draw() const;
		virtual float getWidth() const;
		virtual float getHeight() const;

 		const std::vector<ISprite*>& getChildren() const {
 			return m_sprites;
 		}
		const f2AABB& getBounding() const { return m_bounding; }

	protected:
		virtual void loadResources();

	private:
		void moveToCenter();

		void initBounding();

	private:
		std::vector<ISprite*> m_sprites;

		f2AABB m_bounding;

	}; // CombinationSymbol
}

#endif // _WX_GUI_COMBINATION_SYMBOL_H_