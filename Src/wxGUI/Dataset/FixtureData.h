#ifndef _WX_GUI_FIXTURE_DATA_H_
#define _WX_GUI_FIXTURE_DATA_H_

#include <wx/wx.h>
#include <Fruits2D/Fruits2D.h>

namespace wxgui
{
	struct FixtureDataInfo
	{
		wxString filepath;
		f2Vec2 pos;
		float angle;
		float scale;
	}; // FixtureDataInfo
}

#endif // _WX_GUI_FIXTURE_DATA_H_