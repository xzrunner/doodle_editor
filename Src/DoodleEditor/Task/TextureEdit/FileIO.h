#ifndef _DEDITOR_TEXTURE_EDIT_FILE_IO_H_
#define _DEDITOR_TEXTURE_EDIT_FILE_IO_H_

#include <wxGUI/wxGUI.h>

namespace deditor
{
	namespace texture_edit
	{
		class StagePanel;

		class FileIO
		{
		public:
			static void load(std::ifstream& fin, StagePanel* editPanel);
			static void store(std::ofstream& fout, StagePanel* editPanel);

		}; // FileIO
	}
}

#endif // _DEDITOR_TEXTURE_EDIT_FILE_IO_H_