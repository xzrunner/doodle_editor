#ifndef _GAME_FRUITS_OUTPUT_PAGE_BASE_H_
#define _GAME_FRUITS_OUTPUT_PAGE_BASE_H_

namespace GAME_FRUITS
{
	class InterimData;

	class OutputPageBase
	{
	public:
		OutputPageBase();
		virtual ~OutputPageBase() {}

		virtual void storeToInterimData(InterimData& interim) const = 0;
		virtual void loadFromInterimData(const InterimData& interim) = 0;

		void setDirty(bool isDirty);
		bool isDirty() const;

	protected:
		bool m_isDirty;

	}; // OutputPageBase

	inline OutputPageBase::OutputPageBase()
	{
		m_isDirty = false;
	}

	inline void OutputPageBase::setDirty(bool isDirty)
	{
		m_isDirty = isDirty;
	}

	inline bool OutputPageBase::isDirty() const
	{
		return m_isDirty;
	}
}

#endif // _GAME_FRUITS_OUTPUT_PAGE_BASE_H_