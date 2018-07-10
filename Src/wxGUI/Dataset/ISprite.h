#ifndef _WX_GUI_INTERFACE_SPRITE_H_
#define _WX_GUI_INTERFACE_SPRITE_H_

#include <wx/wx.h>
#include <Fruits2D/Fruits2D.h>

namespace wxgui
{
	class ISymbol;
	class IBody;

	class ISprite : public f2Sprite
	{
	public:
		ISprite();
		virtual ~ISprite();

		//
		// IObject interface
		//
		virtual ISprite* clone() { return NULL; }

		//
		// f2Sprite interface
		//
		virtual void setTransform(const f2Vec2& position, float angle);
		virtual void setScale(float scale);

		virtual const ISymbol& getSymbol() const = 0;
		virtual void setSymbol(ISymbol* symbol) = 0;
		virtual void loadBodyFromFile() = 0;

		void updateEachFrame();
		IBody* getBody() const;

	protected:
		virtual void buildBounding() = 0;

	protected:
		IBody* m_body;

	}; // ISprite

	class SpriteCmp
	{
	public:
		enum Type
		{
			e_file,
			e_x,
			e_y
		};

	public:
		SpriteCmp(Type type = e_file);

		bool operator() (const ISprite* s0, const ISprite* s1) const;

	private:
		Type m_type;

	}; // SpriteCmp
}

#endif // _WX_GUI_INTERFACE_SPRITE_H_