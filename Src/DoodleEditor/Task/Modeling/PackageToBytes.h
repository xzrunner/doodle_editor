#ifndef _DEDITOR_MEDELING_PACKAGE_TO_BYTES_H_
#define _DEDITOR_MEDELING_PACKAGE_TO_BYTES_H_

#include <wxGUI/wxGUI.h>

namespace deditor
{
	namespace modeling
	{
		class BodyData;
		class JointData;

		class PaskageToBytes
		{
		public:
			static void packBody(const BodyData& data, std::ofstream& fout);

			static void packJoint(const JointData& data, std::ofstream& fout,
				const std::vector<BodyData*>& bodies);

		private:
			static int queryBodyIndex(const BodyData* body, 
				const std::vector<BodyData*>& bodies);

		}; // PaskageToBytes
	}
}

#endif // _DEDITOR_MEDELING_PACKAGE_TO_BYTES_H_