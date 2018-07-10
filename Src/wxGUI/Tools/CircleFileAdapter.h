#ifndef _WX_GUI_CIRCLE_FILE_ADAPTER_H_
#define _WX_GUI_CIRCLE_FILE_ADAPTER_H_

#include "IFileAdapter.h"

#include <wx/wx.h>

namespace wxgui
{
	class CircleFileAdapter : public IFileAdapter
	{
	public:
		virtual void load(const char* filename);

	public:
		wxString m_imgPath;
		int m_width, m_height;

	}; // CircleFileAdapter
}

#endif // _WX_GUI_CIRCLE_FILE_ADAPTER_H_