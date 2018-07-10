#ifndef _FEDITOR_TEXT_FILE_ADAPTER_H_
#define _FEDITOR_TEXT_FILE_ADAPTER_H_
#include <Fruits2D/Fruits2D.h>

namespace FEDITOR
{
	class TextFileAdapter
	{
	public:

		virtual void load(const std::string& filename) = 0;

	}; // TextFileAdapter
}

#endif // _FEDITOR_TEXT_FILE_ADAPTER_H_