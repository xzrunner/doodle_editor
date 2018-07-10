#ifndef _FEDITOR_LOOPS_FILE_ADAPTER_H_
#define _FEDITOR_LOOPS_FILE_ADAPTER_H_
#include "TextFileAdapter.h"

namespace FEDITOR
{
	class ChainShape;

	class LoopsFileAdapter : public TextFileAdapter
	{
	public:
		~LoopsFileAdapter();

		virtual void load(const std::string& filename);

	public:
		std::string m_imgFilename;
		int m_coordsType;
		std::vector<ChainShape*> m_loops;

	}; // LoopsFileAdapter
}

#endif // _FEDITOR_LOOPS_FILE_ADAPTER_H_