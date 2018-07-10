#ifndef _FEDITOR_CHAINS_FILE_ADAPTER_H_
#define _FEDITOR_CHAINS_FILE_ADAPTER_H_
#include "TextFileAdapter.h"

namespace FEDITOR
{
	class ChainShape;

	class ChainsFileAdapter : public TextFileAdapter
	{
	public:
		~ChainsFileAdapter();

		virtual void load(const std::string& filename);

	public:
		std::vector<ChainShape*> m_chains;

	}; // ChainsFileAdapter
}

#endif // _FEDITOR_CHAINS_FILE_ADAPTER_H_