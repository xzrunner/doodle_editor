#ifndef _GAME_FRUITS_OUTPUT_DESIGNER_PAGE_H_
#define _GAME_FRUITS_OUTPUT_DESIGNER_PAGE_H_
#include "OutputPageBase.h"
#include <Fruits2D/Fruits2D.h>
#include <wx/wx.h>
#include <wx/dnd.h>

namespace GAME_FRUITS
{
	class Object;

	namespace OUTPUT
	{
		class DesignerPage : public wxWindow, public OutputPageBase
		{
		public:
			DesignerPage(wxWindow* parent);

			//
			// IScenePage interface
			//
			virtual void storeToInterimData(InterimData& interim) const;
			virtual void loadFromInterimData(const InterimData& interim);

			void addSprite(const wxString& path, int x, int y);

		private:
			void onSize(wxSizeEvent& event);
			void onMouse(wxMouseEvent& event);
			void onKey(wxKeyEvent& event);
			void onPaint(wxPaintEvent& event);

			void updateOrigin();

			void deleteSelected();

		private:
			class DragTileTarget : public wxTextDropTarget
			{
			public:
				DragTileTarget(DesignerPage* panel);

				virtual bool OnDropText(wxCoord x, wxCoord y, const wxString& data);

			private:
				DesignerPage* m_panel;

			}; // DragTileTarget

		private:
			static const int SCREEN_WIDTH = 800;
			static const int SCREEN_HEIGHT = 480;

		private:
//			VIEW::BACKSTAGE::DstPanel* m_funDstPanel;

			f2Vec2 m_origin;

//			Object* m_selected;
			f2Vec2 m_lastpos;

			DECLARE_EVENT_TABLE()

		}; // DesignerPage 
	}
}

#endif // _GAME_FRUITS_OUTPUT_DESIGNER_PAGE_H_