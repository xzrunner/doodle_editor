#include "SymbolFactory.h"
#include "ImageSymbol.h"
#include "ShapeSymbol.h"
#include "MeshSymbol.h"
#include "CombinationSymbol.h"

#include "Tools/FileNameTools.h"
#include "tools/FileNameParser.h"

using namespace wxgui;

ISymbol* SymbolFactory::create(const wxString& filepath)
{
	wxString ext = FilenameTools::getExtension(filepath);

	if (ext == "png" || ext == "jpg" || ext == "bmp")
		return new ImageSymbol;

	if (ext == "txt")
	{
		wxString tag = FilenameTools::getFilenameTag(filepath);
		if (FileNameParser::isType(filepath, FileNameParser::e_polygon))
			return new ShapeSymbol;
		else if (FileNameParser::isType(filepath, FileNameParser::e_mesh))
			return new MeshSymbol;
		else if (FileNameParser::isType(filepath, FileNameParser::e_combination))
			return new CombinationSymbol;
	}

	return NULL;
}