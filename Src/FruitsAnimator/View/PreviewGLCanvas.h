#ifndef _FRUITS_ANIMATOR_PREVIEW_GL_CANVAS_H_
#define _FRUITS_ANIMATOR_PREVIEW_GL_CANVAS_H_

#include <wxGUI/wxGUI.h>
#include <wx/wx.h>
#include <Fruits2D/Fruits2D.h>

namespace FRUITS_ANIMATOR
{
	class Sprite;
	class LayersMgr;
	class LibraryPanel;

	class PreviewGLCanvas : public wxgui::GLCanvas
	{
	public:
		struct PlaySetting
		{
			bool isCirculate;
			bool isStop;

			PlaySetting()
			{
				isCirculate = true;
				isStop = false;
			}
		};

	public:
		PreviewGLCanvas(wxgui::EditPanel* editPanel, LayersMgr* layers, 
			LibraryPanel* library, int fps = 24);

		PlaySetting& getPlaySetting();

	protected:
		virtual void initGL();
		virtual void onDraw();

		void onTimer(wxTimerEvent& event);

	private:
		void drawStageData();

		void getCurrSprites(std::vector<Sprite*>& sprites) const;
		void getTweenSprites(const std::vector<Sprite*>& start, const std::vector<Sprite*>& end, 
			std::vector<Sprite*>& tween, float process) const;
		bool isTweenMatched(Sprite& s0, Sprite& s1) const;
		void getTweenSprite(Sprite* start, Sprite* end, Sprite* tween, float process) const;

	private:
		enum
		{
			TIMER_ID = 1000
		};

	private:
		LayersMgr* m_layersMgr;

		LibraryPanel* m_library;

		wxTimer m_timer;
		int m_currFrame;

		PlaySetting m_setting;

		DECLARE_EVENT_TABLE()

	}; // PreviewGLCanvas
}

#endif // _FRUITS_ANIMATOR_PREVIEW_GL_CANVAS_H_