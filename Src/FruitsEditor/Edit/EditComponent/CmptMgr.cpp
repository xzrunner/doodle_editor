#include "CmptMgr.h"
#include "AbstractCmpt.h"

using namespace FEDITOR;

CmptMgr::~CmptMgr()
{
	CONTAINER::iterator itr = m_items.begin();
	for ( ; itr != m_items.end(); ++itr)
		delete itr->second;
}

void CmptMgr::push(AbstractCmpt* item)
{
	m_items.insert(std::make_pair(item->getType(), item));
}

void CmptMgr::createUIControls(GLUI_Node* parent, int type, ShortcutKeyListener* shortcutLsn/* = NULL*/)
{
	CONTAINER::const_iterator itr = m_items.find(type);
	if (itr != m_items.end())
		itr->second->createUIControls(parent, shortcutLsn);
}

void CmptMgr::handleUIEvent()
{
	CONTAINER::iterator itr = m_items.begin();
	for ( ; itr != m_items.end(); ++itr)
		itr->second->handleUIEvent();
}