#ifndef _DEDITOR_COMPRESS_PICTURE_BATCH_SETTING_DIALOG_H_
#define _DEDITOR_COMPRESS_PICTURE_BATCH_SETTING_DIALOG_H_

#include <wx/wx.h>

namespace deditor
{
	namespace compress_pictures
	{
		struct CompressParams;

		class BatchSettingDialog : public wxDialog
		{
		public:
			BatchSettingDialog(wxWindow* parent);

			void getCompressParams(CompressParams& params) const;
			wxString getOutputExt() const;

		private:
			void initLayout();

			void initJpgPanel(wxSizer* topSizer);
			void initPngPanel(wxSizer* topSizer); 

		private:
			wxSpinCtrl* m_jpgSpin;
			wxChoice *m_pngColorChoice, *m_pngSpeedChoice;

			wxTextCtrl* m_extCtrl;

		}; // BatchSettingDialog
	}
}

#endif // _DEDITOR_COMPRESS_PICTURE_BATCH_SETTING_DIALOG_H_