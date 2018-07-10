#ifndef _DEDITOR_MOTOX_PASTE_TILE_TEMPLATE_OP_H_
#define _DEDITOR_MOTOX_PASTE_TILE_TEMPLATE_OP_H_

#include <wxGUI/wxGUI.h>

namespace deditor
{
	namespace motox
	{
		class StagePanel;
		class LibraryTemplateList;
		class LibraryTemplateItem;
		class PasteTileTemplateCMPT;

		class PasteTileTemplateOP : public wxgui::ZoomViewOP
		{
		public:
			PasteTileTemplateOP(StagePanel* stagePanel, 
				wxgui::LibraryPanel* libraryPanel,
				PasteTileTemplateCMPT* cmpt);

			virtual bool onMouseLeftDown(int x, int y);
			virtual bool onMouseRightDown(int x, int y);
			virtual bool onMouseMove(int x, int y);

			virtual bool onDraw() const;
			virtual bool clear();

		private:
			void initSpritesFromBatch(const LibraryTemplateItem& batch);

			void computeSpritesPosition(const LibraryTemplateItem& batch, const f2Vec2& center);

			void fixedSpritePosition(const wxgui::ISprite& src, wxgui::ISprite& dst, 
				const f2Vec2& start, const f2Vec2& end, float currDis, float totDis);

			LibraryTemplateItem* randomTemplate() const;

		private:
	//		static const int INVALID_COORD = 0xffffffff;
			static const f2Vec2 INVALID_POS;

			bool isPosInvalid(const f2Vec2& pos) const {
				return pos == INVALID_POS;
	//			return pos.x == INVALID_COORD && pos.y == INVALID_COORD;
			}

		private:
			StagePanel* m_stagePanel;

			wxgui::LibraryPanel* m_libraryPanel;

			PasteTileTemplateCMPT* m_cmpt;

			LibraryTemplateItem* m_lastSelected;

			std::vector<wxgui::ISprite*> m_sprites;

		}; // PasteTileTemplateOP
	}
}

#endif // _DEDITOR_MOTOX_PASTE_TILE_TEMPLATE_OP_H_