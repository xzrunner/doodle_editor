#ifndef _FEDITOR_FILL_FILE_ADAPTER_H_
#define _FEDITOR_FILL_FILE_ADAPTER_H_
#include "TextFileAdapter.h"

namespace FEDITOR
{
	class ChainShape;

	class FillFileAdapter : public TextFileAdapter
	{
	public:
		~FillFileAdapter();

		virtual void load(const std::string& filename);

	public:
		struct Region
		{
			std::string filename;
			ChainShape* shape;
		};

	public:
		std::vector<Region*> m_regions;

	}; // FillFileAdapter
}

#endif // _FEDITOR_FILL_FILE_ADAPTER_H_