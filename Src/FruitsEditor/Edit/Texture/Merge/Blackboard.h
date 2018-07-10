#ifndef _FEDITOR_TEXTURE_MERGE_BLACKBOARD_H_
#define _FEDITOR_TEXTURE_MERGE_BLACKBOARD_H_
#include "Edit/AbstractBlackboard.h"

namespace FEDITOR
{
	namespace TEXTURE_MERGE
	{
		class Blackboard : public AbstractBlackboard
		{
		public:
			Blackboard();

			void getBgSize(int& width, int& height) const;

		public:
			enum
			{
				e_resetBg = EVENT_ID_BASE_PRIVATE_BLACKBOARD,

				e_openTexture,
				e_saveAsBmp,
				e_saveAsPng,
				e_saveAsJpg
			};

			enum
			{
				SCOPE_EDGE_32 = 0,
				SCOPE_EDGE_64,
				SCOPE_EDGE_128,
				SCOPE_EDGE_256,
				SCOPE_EDGE_512,
				SCOPE_EDGE_1024
			};

		public:
			int m_widthType, m_heightType;

		}; // Blackboard

		inline Blackboard::Blackboard()
		{
			m_widthType = m_heightType = SCOPE_EDGE_128;
		}

		inline void Blackboard::getBgSize(int& width, int& height) const
		{
			width = static_cast<int>(32 * pow(2.0f, m_widthType));
			height = static_cast<int>(32 * pow(2.0f, m_heightType));
		}
	}
}

#endif // _FEDITOR_TEXTURE_MERGE_BLACKBOARD_H_