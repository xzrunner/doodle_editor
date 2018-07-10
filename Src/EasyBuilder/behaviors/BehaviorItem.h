#ifndef _EASY_BUILDER_BEHAVIOR_ITEM_H_
#define _EASY_BUILDER_BEHAVIOR_ITEM_H_

#include "BehaviorDefs.h"

namespace ebuilder
{
	class BehaviorItem : public wxgui::ListItem
	{
	public:
		BehaviorItem(const wxString& name, BehaviorType type)
			: m_type(type)
		{
			m_name = name;
		}

		virtual BehaviorItem* clone() {
			return NULL;
		}

 		const BehaviorType& type() const {
 			return m_type;
 		}

	private:
		const BehaviorType m_type;

	}; // BehaviorItem
}

#endif // _EASY_BUILDER_BEHAVIOR_ITEM_H_