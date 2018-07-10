#ifndef _DEDITOR_MONSTER_FILE_IO_H_
#define _DEDITOR_MONSTER_FILE_IO_H_

#include <wxGUI/wxGUI.h>

namespace deditor
{
	namespace monster
	{
		class StagePanel;
		class ToolbarPanel;

		class FileIO
		{
		public:
			static void load(std::ifstream& fin, StagePanel* stage, 
				wxgui::LibraryPanel* libraryPanel, ToolbarPanel* toolbar);
			static void store(std::ofstream& fout, StagePanel* stage);

		private:
			class StoreSpriteVisitor : public IVisitor
			{
			public:
				StoreSpriteVisitor(std::ofstream& fout, StagePanel* stage);
				virtual ~StoreSpriteVisitor();

				virtual void visit(IObject* object, bool& bFetchNext);

			private:
				StagePanel* m_stage;

				std::ofstream& m_fout;

				std::vector<wxgui::ISprite*> m_data;

			}; // StoreSpriteVisitor

		}; // FileIO
	}
}

#endif // _DEDITOR_MONSTER_FILE_IO_H_