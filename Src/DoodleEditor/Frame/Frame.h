#ifndef _DEDITOR_FRAME_H_
#define _DEDITOR_FRAME_H_

#include <wx/wx.h>

namespace deditor
{
	class BaseTask;

	class Frame : public wxFrame
	{
	public:
		Frame(const wxString& title);

	private:
		void onNew(wxCommandEvent& event);
		void onOpen(wxCommandEvent& event);
		void onSave(wxCommandEvent& event);
		void onSaveAs(wxCommandEvent& event);

		void onQuit(wxCommandEvent& event);
		void onAbout(wxCommandEvent& event);

		void onManualComposeTaskMenu(wxCommandEvent& event);
		void onCompressPicturesTaskMenu(wxCommandEvent& event);
		void onAutomaticMergeTaskMenu(wxCommandEvent& event);
		void onBoundaryExtractionTaskMenu(wxCommandEvent& event);
		void onShapeEditTaskMenu(wxCommandEvent& event);
		void onTextureEditTaskMenu(wxCommandEvent& event);
		void onPolygonFillingMenu(wxCommandEvent& event);

		void onDrawingMenu(wxCommandEvent& event);
		void onModelingMenu(wxCommandEvent& event);
		void onAnimationMenu(wxCommandEvent& event);
		void onParticleMenu(wxCommandEvent& event);

		void onSkaterTaskMenu(wxCommandEvent& event);
		void onMotoXTaskMenu(wxCommandEvent& event);
		void onShootBubbleTaskMenu(wxCommandEvent& event);
		void onMonsterTaskMenu(wxCommandEvent& event);
		void onMagicDefenceTaskMenu(wxCommandEvent& event);
		void onHillClimbTaskMenu(wxCommandEvent& event);

		void onSettingOperatingMenu(wxCommandEvent& event);
		void onSettingViewMenu(wxCommandEvent& event);

		void onPreview(wxCommandEvent& event);

		void initMenuBar();

		wxMenu* initFileBar();

		wxMenu* initCommonTaskBar();
		wxMenu* initSimpleTaskBar();
		wxMenu* initComplexTaskBar();
		wxMenu* initLevelTaskBar();

		wxMenu* initViewBar();
		wxMenu* initSettingsBar();
		wxMenu* initHelpBar();

		void setCurrFilename();

	private:
		BaseTask* m_task;

		wxString m_currFilename;

		DECLARE_EVENT_TABLE()

	}; // Frame
}

#endif // _DEDITOR_FRAME_H_