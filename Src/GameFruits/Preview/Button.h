#ifndef _GAME_FRUITS_PREVIEW_BUTTON_H_
#define _GAME_FRUITS_PREVIEW_BUTTON_H_
#include <wx/wx.h>

namespace GAME_FRUITS
{
	class Scene;

	namespace PREVIEW
	{
		class MainDialog;
		class Scene;

		class Button
		{
		public:
			Button(MainDialog* main, wxBitmap* bitmap, int x, int y);

			void addChangeSceneAction(bool isDownChange, GAME_FRUITS::Scene* toScene);
			void addScaleSizeAction(bool isDownChange, float scale);
			void addChangeImageAction(bool isDownChange, const wxString& bmpPath);

			void onPaint(wxDC& dc) const;

			void onMouseDown(int x, int y);
			void onMouseUp(int x, int y);

		private:
			bool isContain(int x, int y) const;

		private:
			MainDialog* m_main;

			wxBitmap* m_bitmap;
			int m_x, m_y;

			bool m_isDownChangeScene;
			GAME_FRUITS::Scene* m_toScene;

			bool m_isDownScaleSize;
			wxBitmap* m_scaledBmp;
			bool m_isDrawScaled;

			bool m_isDownChangeImage;
			wxBitmap* m_anotherBmp;
			bool m_isDrawAnother;

		}; // Button
	}
}

#endif // _GAME_FRUITS_PREVIEW_BUTTON_H_