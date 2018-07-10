#ifndef _DEDITOR_SKATER_FILE_IO_H_
#define _DEDITOR_SKATER_FILE_IO_H_

#include <wxGUI/wxGUI.h>

namespace deditor
{
	namespace skater
	{
		class StagePanel;

		class FileIO
		{
		public:
			static void load(std::ifstream& fin, StagePanel* stage, 
				wxgui::LibraryPanel* libraryPanel);
			static void store(std::ofstream& fout, StagePanel* stage);

		private:
			static void loadOld(std::ifstream& fin, StagePanel* stage, 
				wxgui::LibraryPanel* libraryPanel);
			static void loadNew(std::ifstream& fin, StagePanel* stage, 
				wxgui::LibraryPanel* libraryPanel);

			static void loadSprites(std::ifstream& fin, StagePanel* stage, 
				wxgui::LibraryPanel* libraryPanel);
			static void loadChains(std::ifstream& fin, StagePanel* stage);

		private:
			class StoreSpriteVisitor : public IVisitor
			{
			public:
				StoreSpriteVisitor(std::ofstream& fout);
				virtual ~StoreSpriteVisitor();

				virtual void visit(IObject* object, bool& bFetchNext);

			private:
				std::ofstream& m_fout;

				std::vector<wxgui::ISprite*> m_data;

			}; // StoreSpriteVisitor

			class StoreChainVisitor : public IVisitor
			{
			public:
				StoreChainVisitor(std::ofstream& fout);
				virtual ~StoreChainVisitor();

				virtual void visit(IObject* object, bool& bFetchNext);

			private:
				std::ofstream& m_fout;

				std::vector<wxgui::ChainShape*> m_data;

			}; // StoreChainVisitor

		}; // FileIO
	}
}

#endif // _DEDITOR_SKATER_FILE_IO_H_