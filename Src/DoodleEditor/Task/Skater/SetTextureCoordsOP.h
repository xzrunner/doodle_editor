#ifndef _DEDITOR_SKATER_SET_TEXTURE_COORDS_OP_H_
#define _DEDITOR_SKATER_SET_TEXTURE_COORDS_OP_H_

#include <wxGUI/wxGUI.h>

namespace deditor
{
	namespace skater
	{
		class SetTextureCoordsOP : public wxgui::ZoomViewOP
		{
		public:
			SetTextureCoordsOP(wxgui::EditPanel* editPanel, wxgui::ImageSprite* sprite);

			virtual bool onMouseLeftDown(int x, int y);
			virtual bool onMouseDrag(int x, int y);

			virtual bool onDraw() const;
			virtual bool clear();

		private:
			void setSelectedEdgePos(const f2Vec2& pos);

		private:
			enum EDGE_ID
			{
				e_null,
				e_left,
				e_right,
				e_down,
				e_up
			};

		private:
			wxgui::ImageSprite* m_sprite;
			float* m_userData;

			EDGE_ID m_selected;

		}; // SetTextureCoordsOP
	}
}

#endif // _DEDITOR_SKATER_SET_TEXTURE_COORDS_OP_H_