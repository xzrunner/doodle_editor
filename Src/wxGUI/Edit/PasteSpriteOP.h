#ifndef _WX_GUI_PASTE_SPRITE_OP_H_
#define _WX_GUI_PASTE_SPRITE_OP_H_

#include "SelectSpritesOP.h"

#include "Dataset/SelectionSet.h"

namespace wxgui
{
	class ISprite;
	class SpritesPanelImpl;
	class PasteSpriteCMPT;

	class PasteSpriteOP : public SelectSpritesOP
	{
	public:
		PasteSpriteOP(EditPanel* editPanel, SpritesPanelImpl* spritesImpl,
			PropertySettingPanel* propertyPanel, PasteSpriteCMPT* cmpt = NULL);
		virtual ~PasteSpriteOP();

		virtual bool onKeyDown(int keyCode);
		virtual bool onMouseLeftDown(int x, int y);
		virtual bool onMouseLeftUp(int x, int y);
		virtual bool onMouseRightDown(int x, int y);
		virtual bool onMouseMove(int x, int y);

		virtual bool onDraw() const;
		virtual bool clear();

	private:
		void setMousePos(int x, int y);
		void fixPosOrthogonal();

	private:
		class SpriteBatch
		{
		public:
			SpriteBatch();
			~SpriteBatch();

			void loadFromSelection(const SpriteSelection& selection);

			void insertToSpritesImpl(SpritesPanelImpl* spritesImpl, const f2Vec2& pos,
				bool isHorMirror, bool isVerMirror);
			void draw(const f2Vec2& pos, bool isHorMirror, bool isVerMirror) const;

			const f2Vec2& getCenter() const { return m_center; }

			void clear();

			bool empty() const { return m_selected.empty(); }

		private:
			void computeCenter();

		private:
			std::vector<ISprite*> m_selected;
			f2Vec2 m_center;

		}; // SpriteBatch

	private:
		SpritesPanelImpl* m_spritesImpl;

		PasteSpriteCMPT* m_cmpt;

		SpriteSelection* m_selection;

		f2Vec2 m_pos;

		SpriteBatch m_batch;

	}; // PasteSpriteOP
}

#endif // _WX_GUI_PASTE_SPRITE_OP_H_