#ifndef _FEDITOR_SKATER_FILE_ADAPTER_H_
#define _FEDITOR_SKATER_FILE_ADAPTER_H_
#include "TextFileAdapter.h"

namespace FEDITOR
{
	class SkaterFileAdapter : public TextFileAdapter
	{
	public:
		~SkaterFileAdapter();

		virtual void load(const std::string& filename);

	public:
		struct Entry
		{
			std::string filename;
			f2Vec2 pos;
			float angle;
			float xScale, yScale;
			f2Vec2 leftLow, rightTop;
		}; // Entry

		struct Batch
		{
			std::vector<Entry*> entries;
		}; // Layer

	public:
		std::vector<Batch*> m_data;

	}; // SkaterFileAdapter
}

#endif // _FEDITOR_SKATER_FILE_ADAPTER_H_