#include "FileNameParser.h"

using namespace FEDITOR;

static const std::string EXT_COMPOSE = "_compose";
static const std::string EXT_LOOPS = "_loops";
static const std::string EXT_CHAINS = "_chains";
static const std::string TAG_CIRCLE = "_circle";
static const std::string EXT_TRIS =	"_tris";
static const std::string EXT_FILL = "_fill";
static const std::string EXT_MOTOX_SPRITES = "_sprites";
static const std::string EXT_MONSTER = "_monster";
static const std::string EXT_SKATER = "_skater";

FileNameParser::Type FileNameParser::getFileType(const std::string& filename)
{
	if (filename == "") return e_unknown;

	int pos = filename.find('.');
	if (pos == -1) return e_unknown;

	std::string ext = filename.substr(pos);
	if (ext == ".txt")
	{
		const std::string txtName = filename.substr(0, filename.find_last_of('.'));
		if (txtName.find('_') == -1) return e_unknown;

		const std::string txtExt = txtName.substr(txtName.find_last_of('_'));
		if (txtExt == EXT_COMPOSE) return e_composeImgs;
		else if (txtExt == EXT_LOOPS) return e_loops;
		else if (txtExt == EXT_CHAINS) return e_chains;
		else if (txtExt == TAG_CIRCLE) return e_circle;
		else if (txtExt == EXT_TRIS) return e_tris;
		else if (txtExt == EXT_FILL) return e_fill;
		else if (txtExt == EXT_MOTOX_SPRITES) return e_motoxSprites;
		else if (txtExt == EXT_MONSTER) return e_monster;
		else if (txtExt == EXT_SKATER) return e_skater;
		else return e_unknown;
	}
	else
	{
		std::transform(ext.begin(), ext.end(), ext.begin(), std::tolower);
		if (ext == ".jpg" || ext == ".png") return e_img;
		else return e_unknown;
	}
}

std::string FileNameParser::getFileExtension(Type type)
{
	std::string extension;
	switch (type)
	{
	case e_composeImgs:
		extension = EXT_COMPOSE;
		break;
	case e_loops:
		extension = EXT_LOOPS;
		break;
	case e_chains:
		extension = EXT_CHAINS;
		break;
	case e_circle:
		extension = TAG_CIRCLE;
		break;
	case e_tris:
		extension = EXT_TRIS;
		break;
	case e_fill:
		extension = EXT_FILL;
		break;
	case e_motoxSprites:
		extension = EXT_MOTOX_SPRITES;
		break;
	case e_monster:
		extension = EXT_MONSTER;
		break;
	case e_skater:
		extension = EXT_SKATER;
		break;
	}
	return extension;
}

bool FileNameParser::isType(const std::string& filename, Type type)
{
	FileNameParser::Type fileType = getFileType(filename);
	return fileType == type;
}