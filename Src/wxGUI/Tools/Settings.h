#ifndef _WX_GUI_SETTINGS_H_
#define _WX_GUI_SETTINGS_H_

#include <wx/wx.h>

#include <set>

namespace wxgui
{
	class Settings
	{
	public:

		static bool bZoomOnlyUseMouseWheel;

		static int ctlPosSize;
		static bool bDisplayTrisEdge, bDisplayPolyBound;

		enum DrawType
		{
			e_DrawBoth = 0,
			e_DrawPhysics,
			e_DrawImage
		};
		static DrawType drawType;

		static std::set<wxString> RESOURCE_PATH;

	}; // Settings
}

#endif // _WX_GUI_SETTINGS_H_