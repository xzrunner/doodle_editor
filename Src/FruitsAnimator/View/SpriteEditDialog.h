#ifndef _FRUITS_ANIMATOR_SPRITE_EDIT_DIALOG_H_
#define _FRUITS_ANIMATOR_SPRITE_EDIT_DIALOG_H_

#include <wx/wx.h>
#include <wxGUI/wxGUI.h>

namespace FRUITS_ANIMATOR
{
	class Sprite;

	class SpriteEditDialog : public wxDialog
	{
	public:
		SpriteEditDialog(wxWindow* parent, Sprite* sprite);
		~SpriteEditDialog();

	private:
		void initLayout();

		void buildToolBar(wxSizer* topSizer);
		void buildEditPanel(wxSizer* topSizer);

		void onMergeMesh(wxCommandEvent& event);
		void onSeparateMesh(wxCommandEvent& event);
		void onUpdateMeshState(wxUpdateUIEvent& event);

	private:
		Sprite* m_sprite;
		wxgui::EditPanel* m_editPanel;

		wxButton *m_btnMerge, *m_btnSeparate;

	}; // SpriteEditDialog
}

#endif // _FRUITS_ANIMATOR_SPRITE_EDIT_DIALOG_H_