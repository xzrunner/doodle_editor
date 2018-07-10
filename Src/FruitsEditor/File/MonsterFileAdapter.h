#ifndef _FEDITOR_MONSTER_FILE_ADAPTER_H_
#define _FEDITOR_MONSTER_FILE_ADAPTER_H_
#include "TextFileAdapter.h"

namespace FEDITOR
{
	class MonsterFileAdapter : public TextFileAdapter
	{
	public:
		
		virtual void load(const std::string& filename);

	public:
		struct Item
		{
			std::string name;
			float col, row;
			float id;
		};

	public:
		int m_time;
		int m_length;
		int m_minEmptyGrid, m_maxEmptyGrid;
		
		std::vector<Item> m_items;

	}; // MonsterFileAdapter
}


#endif // _FEDITOR_MONSTER_FILE_ADAPTER_H_