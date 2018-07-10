#ifndef _DEDITOR_POLYGON_EDIT_FILE_IO_H_
#define _DEDITOR_POLYGON_EDIT_FILE_IO_H_

#include <wxGUI/wxGUI.h>

namespace deditor
{
	namespace polygon_edit
	{
		class StagePanel;

		class FileIO
		{
		public:
			static void load(const wxString& filepath, StagePanel* stage);
			static void store(const wxString& filepath, StagePanel* stage);

		public:
			static void filterPolygonLayer(std::vector<wxgui::Layer*>& layers);

		}; // FileIO
	}
}

#endif // _DEDITOR_POLYGON_EDIT_FILE_IO_H_