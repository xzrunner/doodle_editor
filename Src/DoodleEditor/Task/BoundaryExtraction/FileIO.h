#ifndef _DEDITOR_BOUNDARY_EXTRACTION_FILE_IO_H_
#define _DEDITOR_BOUNDARY_EXTRACTION_FILE_IO_H_

#include <wxGUI/wxGUI.h>

namespace deditor
{
	namespace boundary_extraction
	{
		class LibraryPanel;
		class LibraryItem;

		class FileIO
		{
		public:
			static void load(std::ifstream& fin, LibraryPanel* library);
			static void store(std::ofstream& fout, LibraryPanel* library);

			static void loadItemShapes(LibraryItem* item);

		public:
			class StoreItemVisitor : public IVisitor
			{
			public:
				StoreItemVisitor(std::ofstream& fout);
				virtual ~StoreItemVisitor();

				virtual void visit(IObject* object, bool& bFetchNext);

			private:
				void storeChainShapes(const LibraryItem* item) const;

			private:
				std::ofstream& m_fout;

				std::vector<LibraryItem*> m_data;

			}; // StoreItemVisitor

		}; // FileIO
	}
}

#endif // _DEDITOR_BOUNDARY_EXTRACTION_FILE_IO_H_