#include "BoundsContainer.h"
#include "File/LoopsFileAdapter.h"

using namespace FEDITOR;
using namespace FEDITOR::SKATER;

BoundsContainer::~BoundsContainer()
{
	std::map<std::string, LoopsFileAdapter*>::iterator itr;
	for (itr = m_mapNameToBound.begin(); itr != m_mapNameToBound.end(); ++itr)
		delete itr->second;
	m_mapNameToBound.clear();
}

LoopsFileAdapter* BoundsContainer::insert(const std::string& filename)
{
	LoopsFileAdapter* adapter = new LoopsFileAdapter;
	adapter->load(filename);
	LoopsFileAdapter* tmp = query(adapter->m_imgFilename);
	if (!tmp)
	{
		m_mapNameToBound.insert(std::make_pair(adapter->m_imgFilename, adapter));
		return adapter;
	}
	else
	{
		delete adapter;
		return tmp;
	}
}

LoopsFileAdapter* BoundsContainer::query(const std::string& filename) const
{
	std::map<std::string, LoopsFileAdapter*>::const_iterator itr 
		= m_mapNameToBound.find(filename);
	if (itr == m_mapNameToBound.end()) return NULL;
	else return itr->second;
}