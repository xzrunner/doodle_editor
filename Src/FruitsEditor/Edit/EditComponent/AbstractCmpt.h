#ifndef _FEDITOR_ABSTRACT_CMPT_H_
#define _FEDITOR_ABSTRACT_CMPT_H_
#include "CmptMgr.h"

class GLUI_Node;

namespace FEDITOR
{
	class CmptMgr;

	class AbstractCmpt
	{
	public:
		AbstractCmpt(int type, CmptMgr& cmptMgr);

		virtual void createUIControls(GLUI_Node* parent, ShortcutKeyListener* shortcutLsn) = 0;
		virtual void handleUIEvent() = 0;

		int getType() const;

	protected:
		CmptMgr& m_cmptMgr;

	private:
		int m_type;

	}; // AbstractCmpt

	inline AbstractCmpt::AbstractCmpt(int type, CmptMgr& cmptMgr)
		: m_cmptMgr(cmptMgr)
	{
		m_type = type;
		cmptMgr.push(this);
	}

	inline int AbstractCmpt::getType() const
	{
		return m_type;
	}
}

#endif // _FEDITOR_ABSTRACT_CMPT_H_