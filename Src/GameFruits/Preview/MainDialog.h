#ifndef _GAME_FRUITS_PREVIEW_MAIN_DIALOG_H_
#define _GAME_FRUITS_PREVIEW_MAIN_DIALOG_H_
#include <wx/wx.h>

namespace GAME_FRUITS
{
	class Scene;

	namespace PREVIEW
	{
		class Scene;

		class MainDialog : public wxDialog
		{
		public:
			MainDialog(wxWindow* parent);
			~MainDialog();

			void loadFromScene(GAME_FRUITS::Scene* scene);

		private:
			void onMouse(wxMouseEvent& event);
			void onPaint(wxPaintEvent& event);

		private:
			Scene* m_scene;

			DECLARE_EVENT_TABLE()

		}; // PreviewDialog
	}
}

#endif // _GAME_FRUITS_PREVIEW_MAIN_DIALOG_H_