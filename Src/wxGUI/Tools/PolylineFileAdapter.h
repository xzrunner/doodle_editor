#ifndef _WX_GUI_POLYGON_FILE_ADAPTER_H_
#define _WX_GUI_POLYGON_FILE_ADAPTER_H_

#include "IFileAdapter.h"

#include <wxGUI/wxGUI.h>

namespace wxgui
{
	class PolylineFileAdapter : public IFileAdapter
	{
	public:
		PolylineFileAdapter(std::vector<ChainShape*>& chains);

		virtual void load(const char* filename);
		virtual void store(const char* filename);

		void setImgPath(const wxString& path) {
			m_imgPath = path;
		}

	public:
		wxString m_imgPath;
		std::vector<ChainShape*>& m_chains;

	}; // PolylineFileAdapter
}

#endif // _WX_GUI_POLYGON_FILE_ADAPTER_H_