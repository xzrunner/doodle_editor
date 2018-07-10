#ifndef _FEDITOR_CIRCLE_FILE_ADAPTER_H_
#define _FEDITOR_CIRCLE_FILE_ADAPTER_H_
#include "TextFileAdapter.h"

namespace FEDITOR
{
	class CircleFileAdapter : public TextFileAdapter
	{
	public:

		virtual void load(const std::string& filename);

	public:
		std::string m_imgFilename;
		int m_width, m_height;

	}; // CircleFileAdapter
}

#endif // _FEDITOR_CIRCLE_FILE_ADAPTER_H_