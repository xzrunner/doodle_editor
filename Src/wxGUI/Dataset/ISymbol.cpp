#include "ISymbol.h"

#include "Tools/FileNameTools.h"

using namespace wxgui;

bool ISymbol::loadFromFile(const wxString& filepath)
{
	m_filepath = FilenameTools::getExistFilepath(filepath);
	if (m_filepath == wxEmptyString)
	{
		m_name = wxT("error");
		m_bitmap = NULL;
		return false;
	}

	m_name = FilenameTools::getFilename(filepath);
	m_bitmap = NULL;
	loadResources();
	return true;
}