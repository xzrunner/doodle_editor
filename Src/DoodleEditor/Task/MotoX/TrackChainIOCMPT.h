#ifndef _DEDITOR_MOTOX_TRACK_CHAIN_IO_CMPT_H_
#define _DEDITOR_MOTOX_TRACK_CHAIN_IO_CMPT_H_

#include <wxGUI/wxGUI.h>

namespace deditor
{
	namespace motox
	{
		class StagePanel;
		class ShapesPanelImpl;

		class TrackChainIOCMPT : public wxgui::AbstractEditCMPT
		{
		public:
			TrackChainIOCMPT(wxWindow* parent, const wxString& name,
				StagePanel* editPanel);

			static void packageToBin(const wxString& src, 
				const wxString& dst);

		protected:
			virtual wxSizer* initLayout();

		private:
			void onLoadText(wxCommandEvent& event);
			void onStoreText(wxCommandEvent& event);
			void onLoadBin(wxCommandEvent& event);
			void onStoreBin(wxCommandEvent& event);

			void loadFromTextFile(const wxString& filepath);
			void storeToTextFile(const wxString& filepath) const;
			void loadFromBinFile(const wxString& filepath);
			void storeToBinFile(const wxString& filepath) const;

			static void storeToBinFile(const std::vector<std::vector<f2Vec2> >& vertices,
				const wxString& filepath);

		private:
			static const wxString TRACK_FILE_TAG;

		private:
			ShapesPanelImpl* m_shapesImpl;

			wxTextCtrl* m_currFilenameCtrl;

		}; // TrackChainIOCMPT
	}
}

#endif // _DEDITOR_MOTOX_TRACK_CHAIN_IO_CMPT_H_