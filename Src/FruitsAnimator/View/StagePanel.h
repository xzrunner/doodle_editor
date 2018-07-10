#ifndef _FRUITS_ANIMATOR_STAGE_PANEL_H_
#define _FRUITS_ANIMATOR_STAGE_PANEL_H_

#include <wx/wx.h>
#include <wx/dnd.h>
#include <Fruits2D/Fruits2D.h>
#include <wxGUI/wxGUI.h>

namespace FRUITS_ANIMATOR
{
	class Sprite;
	class LibraryPanel;
	class TimeLinePanel;
	class KeyFrame;

	class StagePanel : public wxgui::EditPanel, public wxgui::MultiSpritesImpl
	{
	public:
		StagePanel(wxWindow* parent, LibraryPanel* libraryPanel, 
			TimeLinePanel* timeLinePanel);

		//
		// wxgui::MultiSpritesImpl interface
		//
		virtual void traverseSprites(IVisitor& visitor, 
			wxgui::TraverseType type = wxgui::e_allExisting,
			bool order = true) const;
		virtual void removeSprite(f2Sprite* sprite);
		virtual void insertSprite(f2Sprite* sprite) {}
		virtual void clear();

		void insertSymbol(int index, wxCoord x, wxCoord y);
		void insertSkeleton(int index, wxCoord x, wxCoord y);
		void loadCurrFrameSprites();

		void resetCanvas();

	private:
		class DragSymbolTarget : public wxTextDropTarget
		{
		public:
			DragSymbolTarget(StagePanel* panel);

			virtual bool OnDropText(wxCoord x, wxCoord y, const wxString& data);

		private:
			StagePanel* m_panel;

		}; // DragTileTarget

	private:
		LibraryPanel* m_libraryPanel;
		TimeLinePanel* m_timeLinePanel;

		std::vector<Sprite*> m_sprites;

	}; // StagePanel
}

#endif // _FRUITS_ANIMATOR_STAGE_PANEL_H_