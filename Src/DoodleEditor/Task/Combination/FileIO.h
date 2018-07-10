#ifndef _DEDITOR_COMBINATION_FILE_IO_H_
#define _DEDITOR_COMBINATION_FILE_IO_H_

#include <wxGUI/wxGUI.h>

namespace deditor
{
	namespace combination
	{
		class StagePanel;

		class FileIO
		{
		public:
			static void load(const wxgui::CombinationFileAdapter& adapter, 
				StagePanel* stage, wxgui::LibraryPanel* libraryPanel);
			static void store(std::ofstream& fout, StagePanel* stage);

		}; // FileIO
	}
}

#endif // _DEDITOR_COMBINATION_FILE_IO_H_