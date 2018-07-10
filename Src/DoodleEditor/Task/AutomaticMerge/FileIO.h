#ifndef _DEDITOR_AUTOMATIC_MERGE_FILE_IO_H_
#define _DEDITOR_AUTOMATIC_MERGE_FILE_IO_H_

#include "ToolbarPanel.h"

#include <wxGUI/wxGUI.h>

namespace deditor
{
	namespace automatic_merge
	{
		class StagePanel;

		class FileIO
		{
		public:
			static void load(std::ifstream& fin, StagePanel* stage, 
				wxgui::LibraryPanel* libraryPanel);
			static void store(const char* filename, StagePanel* stage, 
				ToolbarPanel::IMG_TYPE type);

		private:
			static void storeImage(const char* filename, StagePanel* stage, 
				ToolbarPanel::IMG_TYPE type);
			static void storePosInfo(const char* filename, StagePanel* stage);

		private:
			class StoreSpriteVisitor : public IVisitor
			{
			public:
				StoreSpriteVisitor(std::ofstream& fout, int height);
				virtual ~StoreSpriteVisitor();

				virtual void visit(IObject* object, bool& bFetchNext);

			private:
				std::ofstream& m_fout;
				int m_height;

				std::vector<wxgui::ImageSprite*> m_data;

			}; // StoreSpriteVisitor

		}; // FileIO
	}
}

#endif // _DEDITOR_AUTOMATIC_MERGE_FILE_IO_H_