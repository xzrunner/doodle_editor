#ifndef _WX_GUI_FILE_NAME_PARSER_H_
#define _WX_GUI_FILE_NAME_PARSER_H_

#include <wx/wx.h>

namespace wxgui
{
	class FileNameParser
	{
	public:
		enum Type
		{
			e_unknown = 0,
			// shape
			e_polyline,
			e_circle,
			e_polygon,
			// symbol
			e_image,
			e_mesh,
			e_combination
		};

		static Type getFileType(const wxString& filename);
		static wxString getFileTag(Type type);

		static bool isType(const wxString& filename, Type type);

	}; // FileNameParser
}

#endif // _WX_GUI_FILE_NAME_PARSER_H_