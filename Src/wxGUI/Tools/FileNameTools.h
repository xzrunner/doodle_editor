#ifndef _WX_GUI_FILENAME_TOOLS_H_
#define _WX_GUI_FILENAME_TOOLS_H_

#include <wx/wx.h>

namespace wxgui
{
	class FilenameTools
	{
	public:
		// add _* between end and '.', will not add if already has one
		static wxString getFilenameAddTag(const wxString& filename, const wxString& tag, 
			const wxString& extension);

		// get string between the last '_' and '.'
		static wxString getFilenameTag(const wxString& filepath);

		// get string between the last '\' and '.'
		static wxString getFilename(const wxString& filepath);

		// get string after the last '\'
		static wxString getFilenameWithExtension(const wxString& filepath);

		// get string from begin to '.'
		static wxString getFilePathExceptExtension(const wxString& filepath);

		// get string after '.'
		static wxString getExtension(const wxString& filepath);

		// get string from begin to the last '\'
		static wxString getFileDir(const wxString& filepath);

		//////////////////////////////////////////////////////////////////////////

		static bool isExist(const wxString& filepath);

		static wxString getExistFilepath(const wxString& filepath);

	}; // FilenameTools
}

#endif // _WX_GUI_FILENAME_TOOLS_H_