#include "FileNameParser.h"

#include <Fruits2D/Fruits2D.h>

using namespace wxgui;

static const wxString TAG_POLYLINE = "polyline";
static const wxString TAG_CIRCLE = "circle";
static const wxString TAG_POLYGON = "surface";

static const wxString TAG_MESH = "mesh";
static const wxString TAG_COMBINATION = "combination";

FileNameParser::Type FileNameParser::getFileType(const wxString& filename)
{
	if (filename.empty()) return e_unknown;

	int pos = filename.find('.');
	if (pos == -1) return e_unknown;

	std::string extension = filename.substr(pos);
	if (extension == ".txt")
	{
		const wxString txtName = filename.substr(0, filename.find_last_of('.'));
		if (txtName.find('_') == -1) return e_unknown;

		const wxString txtExtension = txtName.substr(txtName.find_last_of('_') + 1);
		if (txtExtension == TAG_POLYLINE) return e_polyline;
		else if (txtExtension == TAG_CIRCLE) return e_circle;
		else if (txtExtension == TAG_POLYGON) return e_polygon;
		else if (txtExtension == TAG_MESH) return e_mesh;
		else if (txtExtension == TAG_COMBINATION) return e_combination;
		else return e_unknown;
	}
	else
	{
		StringTools::toLower(extension);
		if (extension == ".jpg" || extension == ".png" || extension == ".bmp") return e_image;
		else return e_unknown;
	}
}

wxString FileNameParser::getFileTag(Type type)
{
	wxString extension;
	switch (type)
	{
	case e_polyline:
		extension = TAG_POLYLINE;
		break;
	case e_circle:
		extension = TAG_CIRCLE;
		break;
	case e_mesh:
		extension = TAG_MESH;
		break;
	case e_combination:
		extension = TAG_COMBINATION;
		break;
	}
	return extension;
}

bool FileNameParser::isType(const wxString& filename, Type type)
{
	FileNameParser::Type fileType = getFileType(filename);
	return fileType == type;
}