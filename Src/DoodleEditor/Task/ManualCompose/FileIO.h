#ifndef _DEDITOR_MANUAL_COMPOSE_FILE_IO_H_
#define _DEDITOR_MANUAL_COMPOSE_FILE_IO_H_

#define JUNYONG_FORMAT

#include <wxGUI/wxGUI.h>

namespace deditor
{
	class ManualComposeFileAdapter;

	namespace manual_compose
	{
		class StagePanel;

		class FileIO
		{
		public:
			static void load(const ManualComposeFileAdapter& fileAdapter, StagePanel* stage, 
				wxgui::LibraryPanel* libraryPanel);
			static void store(std::ofstream& fout, StagePanel* stage);

		private:
			class StoreSpriteVisitor : public IVisitor
			{
			public:
#ifdef JUNYONG_FORMAT
				StoreSpriteVisitor(std::ofstream& fout, int width, int height);
#endif
				StoreSpriteVisitor(std::ofstream& fout);
				virtual ~StoreSpriteVisitor();

				virtual void visit(IObject* object, bool& bFetchNext);

			private:
				std::ofstream& m_fout;

				std::vector<wxgui::ISprite*> m_data;

#ifdef JUNYONG_FORMAT
				int m_width, m_height;
#endif

			}; // StoreSpriteVisitor

		}; // FileIO
	}
}

#endif // _DEDITOR_MANUAL_COMPOSE_FILE_IO_H_