#include "FilenameTools.h"
#include "Settings.h"

#include <wx/filename.h>

using namespace wxgui;

wxString FilenameTools::getFilenameAddTag(const wxString& filename, const wxString& tag, 
										   const wxString& extension)
{
	wxString fixed;
	int start = filename.find_last_of('_');
	if (start != -1)
	{
		wxString check = filename.substr(start + 1, filename.find_last_of('.') - start - 1);
		if (check == tag)
			fixed = filename;
		else
			fixed = filename.substr(0, filename.find_last_of('.')) + wxT("_" + tag + "." + extension);
	}
	else
	{
		fixed = filename.substr(0, filename.find_last_of('.')) + wxT("_" + tag + "." + extension);
	}
	return fixed;
}

wxString FilenameTools::getFilenameTag(const wxString& filepath)
{
	const size_t start = filepath.find_last_of('_') + 1,
		end = filepath.find_last_of('.');
	return filepath.substr(start, end - start);
}

wxString FilenameTools::getFilename(const wxString& filepath)
{
	const size_t start = filepath.find_last_of('\\') + 1,
		end = filepath.find_last_of('.');
	return filepath.substr(start, end - start);
}

wxString FilenameTools::getFilenameWithExtension(const wxString& filepath)
{
	return filepath.substr(filepath.find_last_of('\\') + 1);
}

wxString FilenameTools::getFilePathExceptExtension(const wxString& filepath)
{
	return filepath.substr(0, filepath.find_last_of('.'));
}

wxString FilenameTools::getExtension(const wxString& filepath)
{
	return filepath.substr(filepath.find_last_of('.') + 1);
}

wxString FilenameTools::getFileDir(const wxString& filepath)
{
	return filepath.substr(0, filepath.find_last_of('\\'));
}

bool FilenameTools::isExist(const wxString& filepath)
{
	return wxFileName::FileExists(filepath);
}

wxString FilenameTools::getExistFilepath(const wxString& filepath)
{
	wxString filepathFixed = filepath;
	if (!isExist(filepathFixed))
	{
		wxString filename = filepathFixed = getFilenameWithExtension(filepathFixed);
		if (!isExist(filepathFixed))
		{
			std::set<wxString>::iterator itr = Settings::RESOURCE_PATH.begin();
			for ( ; itr != Settings::RESOURCE_PATH.end(); ++itr)
			{
				filepathFixed = *itr + filename;
				if (isExist(filepathFixed))
					return filepathFixed;
			}
			return wxEmptyString;
		}
		else
		{
			return filepathFixed;
		}
	}
	else
	{
		return filepathFixed;
	}
}