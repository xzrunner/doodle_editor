#ifndef _FEDITOR_FILE_NAME_PARSER_H_
#define _FEDITOR_FILE_NAME_PARSER_H_
#include <Fruits2D/Fruits2D.h>

namespace FEDITOR
{
	class FileNameParser
	{
	public:
		enum Type
		{
			e_unknown = 0,
			e_composeImgs,	// Compose Images
			e_img,			// jpeg, png
			e_loops,		// ExtractEdge
			e_chains,		// MotoX -> Level -> track chains
			e_circle,		// MotoX wheels
			e_tris,			// colored regions
			e_fill,			// FillColor
			e_motoxSprites,	// MotoX -> Level -> sprites
			e_monster,		// Special -> Monster
			e_skater		// Special -> Skater
		};

		static Type getFileType(const std::string& filename);
		static std::string getFileExtension(Type type);

		static bool isType(const std::string& filename, Type type);

	}; // FileNameParser
}

#endif // _FEDITOR_FILE_NAME_PARSER_H_