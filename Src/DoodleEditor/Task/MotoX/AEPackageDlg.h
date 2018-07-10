#ifndef _DEDITOR_MOTOX_ACTOR_EDIT_PACKAGE_DIALOG_H_
#define _DEDITOR_MOTOX_ACTOR_EDIT_PACKAGE_DIALOG_H_

#include "AEPackageImpl.h"

#include <wx/wx.h>

namespace deditor
{
	namespace motox
	{
		class LibraryActorItem;

		class AEPackageDlg : public wxDialog
		{
		public:
			AEPackageDlg(wxWindow* parent, const LibraryActorItem& params);

		private:
			void initLayout();

			void onLoadFromAutomaticFile(wxCommandEvent& event);
			void onStoreToBinFile(wxCommandEvent& event);

		private:
			AEPackageImpl m_packImpl;

		}; // AEPackageDlg
	}
}

#endif // _DEDITOR_MOTOX_ACTOR_EDIT_PACKAGE_DIALOG_H_