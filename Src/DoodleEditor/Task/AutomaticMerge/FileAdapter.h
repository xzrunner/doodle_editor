#ifndef _DEDITOR_AUTOMATIC_MERGE_FILE_ADAPTER_H_
#define _DEDITOR_AUTOMATIC_MERGE_FILE_ADAPTER_H_

#include "ToolbarPanel.h"

#include <wxGUI/wxGUI.h>

namespace deditor
{
	namespace automatic_merge
	{
		class FileAdapter
		{
		public:
			FileAdapter();
			~FileAdapter();

			void resolve(const wxString& filepath);

		public:
			struct Item
			{
				wxString filepath;
				int left, top;
				int width, height;
			};

		public:
			int m_width, m_height;
			std::vector<Item> m_data;

		}; // FileAdapter
	}
}

#endif // _DEDITOR_AUTOMATIC_MERGE_FILE_ADAPTER_H_