#ifndef _DEDITOR_MOTOX_TEMPLATE_EDIT_FILE_ADAPTER_H_
#define _DEDITOR_MOTOX_TEMPLATE_EDIT_FILE_ADAPTER_H_

#include <wx/wx.h>

#include <Fruits2D/Fruits2D.h>

namespace deditor
{
	namespace motox
	{
		class TEFileAdapter
		{
		public:
			struct Entry
			{
				std::string filepath;

				f2Vec2 pos;
				float angle;
				float scale;
			};

		public:
			~TEFileAdapter();

		public:
			void resolve(const wxString& filepath);

		public:
			std::vector<Entry> m_data;

		}; // TEFileAdapter
	}
}

#endif // _DEDITOR_MOTOX_TEMPLATE_EDIT_FILE_ADAPTER_H_