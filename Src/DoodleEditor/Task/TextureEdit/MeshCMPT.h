#ifndef _DEDITOR_TEXTURE_EDIT_MESH_CMPT_H_
#define _DEDITOR_TEXTURE_EDIT_MESH_CMPT_H_

#include <wxGUI/wxGUI.h>

namespace deditor
{
	namespace texture_edit
	{
		class StagePanel;

		class MeshCMPT : public wxgui::AbstractEditCMPT
		{
		public:
			MeshCMPT(wxWindow* parent, const wxString& name,
				StagePanel* editPanel);

			int getNodeCaptureDistance() const;

		protected:
			virtual wxSizer* initLayout();

		private:
			void onCreateTextureBounding(wxCommandEvent& event);

			void onStoreSelectedMesh(wxCommandEvent& event);
			void storeSelectedMesh(const wxString& filepath);

		private:
			wxSlider* m_tolSlider;

		}; // MeshCMPT
	}
}

#endif // _DEDITOR_TEXTURE_EDIT_MESH_CMPT_H_