#ifndef _FEDITOR_COMPOSE_IMAGES_ADAPTER_H_
#define _FEDITOR_COMPOSE_IMAGES_ADAPTER_H_
#include "TextFileAdapter.h"

namespace FEDITOR
{
	class ComposeImagesAdapter : public TextFileAdapter
	{
	public:
		virtual void load(const std::string& filename);

	public:
		struct Entry
		{
			std::string filename;
			float x, y;
			float angle;
		};

	public:
		std::vector<Entry> m_entries;

	}; // ComposeImagesAdapter
}

#endif // _FEDITOR_COMPOSE_IMAGES_ADAPTER_H_