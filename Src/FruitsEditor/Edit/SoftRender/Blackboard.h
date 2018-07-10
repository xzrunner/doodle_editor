#ifndef _FEDITOR_SOFT_RENDER_BLACKBOARD_H_
#define _FEDITOR_SOFT_RENDER_BLACKBOARD_H_
#include "FruitsEditor/Edit/AbstractBlackboard.h"
#include "Fruits3D/Tools/f3Types.h"

namespace FEDITOR
{
	namespace SOFT_RENDER
	{
		class Blackboard : public AbstractBlackboard
		{
		public:
			enum
			{
				e_OpenMode = EVENT_ID_BASE_PRIVATE_BLACKBOARD
			};

		public:
			Blackboard();

		public:
			F3D::f3Vec4 m_camPos, m_camDir;

		}; // Blackboard

		inline Blackboard::Blackboard()
		{
			m_camPos.set(0, 0, -100, 1);
			m_camDir.set(0, 0, 0, 1);
		}
	}
}

#endif // _FEDITOR_SOFT_RENDER_BLACKBOARD_H_