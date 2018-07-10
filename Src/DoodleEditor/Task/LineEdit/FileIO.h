#ifndef _DEDITOR_LINE_EDIT_FILE_IO_H_
#define _DEDITOR_LINE_EDIT_FILE_IO_H_

#include <wxGUI/wxGUI.h>

namespace deditor
{
	namespace line_edit
	{
		class StagePanel;

		class FileIO
		{
		public:
			static void load(std::ifstream& fin, StagePanel* stage);
			static void store(std::ofstream& fout, StagePanel* stage);

		private:
			class StoreChainVisitor : public IVisitor
			{
			public:
				StoreChainVisitor(std::ofstream& fout);
				virtual ~StoreChainVisitor();

				virtual void visit(IObject* object, bool& bFetchNext);

			private:
				std::ofstream& m_fout;

				std::vector<wxgui::ChainShape*> m_data;

			}; // StoreItemVisitor

		}; // FileIO
	}
}

#endif // _DEDITOR_LINE_EDIT_FILE_IO_H_