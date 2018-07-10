#ifndef _WX_GUI_COMBINATION_FILE_ADAPTER_H_
#define _WX_GUI_COMBINATION_FILE_ADAPTER_H_

#include "IFileAdapter.h"

#include <Fruits2D/Fruits2D.h>

namespace wxgui
{
	class CombinationFileAdapter : public IFileAdapter
	{
	public:
		struct Entry
		{
			std::string filepath;

			f2Vec2 pos;
			float angle;
			float scale;
			bool xMirror, yMirror;
		};

	public:
		virtual void load(const char* filename);

	public:
		std::vector<Entry> m_data;

	}; // CombinationFileAdapter
}

#endif // _WX_GUI_COMBINATION_FILE_ADAPTER_H_