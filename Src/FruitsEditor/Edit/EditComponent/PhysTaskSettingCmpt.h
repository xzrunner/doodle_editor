#ifndef _FEDITOR_PHYS_TASK_SETTING_CMPT_H_
#define _FEDITOR_PHYS_TASK_SETTING_CMPT_H_
#include "AbstractCmpt.h"

namespace FEDITOR
{
	class PhysTaskSettingCmpt : public AbstractCmpt
	{
	public:
		PhysTaskSettingCmpt(CmptMgr& cmptMgr);

		virtual void createUIControls(GLUI_Node* parent, ShortcutKeyListener* shortcutLsn);
		virtual void handleUIEvent();

		bool isStepOpen() const;
		bool isDrawOpen() const;

		int getHz() const;
		int getVelocityIterations() const;
		int getPositionIterations() const;

	private:
		void smallLayoutUI(GLUI_Node* parent);
		void largeLayoutUI(GLUI_Node* parent);

	private:
		int m_stepFlag, m_drawFlag;

		int m_hz;
		int m_velocityIterations, m_positionIterations;

	}; // PhysTaskSettingCmpt

	inline bool PhysTaskSettingCmpt::isStepOpen() const
	{
		return m_stepFlag == 1;
	}

	inline bool PhysTaskSettingCmpt::isDrawOpen() const
	{
		return m_drawFlag == 1;
	}

	inline int PhysTaskSettingCmpt::getHz() const
	{
		return m_hz;
	}

	inline int PhysTaskSettingCmpt::getVelocityIterations() const
	{
		return m_velocityIterations;
	}

	inline int PhysTaskSettingCmpt::getPositionIterations() const
	{
		return m_positionIterations;
	}
}

#endif // _FEDITOR_PHYS_TASK_SETTING_CMPT_H_