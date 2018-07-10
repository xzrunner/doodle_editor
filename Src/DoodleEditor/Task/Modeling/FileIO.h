#ifndef _DEDITOR_MODELING_FILE_IO_H_
#define _DEDITOR_MODELING_FILE_IO_H_

#include <wxGUI/wxGUI.h>
#include <json/json.h>

namespace deditor
{
	namespace modeling
	{
		class StagePanel;
		class BodyData;
		class FixtureData;
		class JointData;

		class FileIO
		{
		public:
			static void load(std::ifstream& fin, StagePanel* stage,
				wxgui::LibraryPanel* libraryPanel);
			static void store(std::ofstream& fout, StagePanel* stage);

		private:
			static Json::Value b2j(BodyData* body);
			static Json::Value b2j(FixtureData* fixture);
			static Json::Value b2j(JointData* joint, 
				const std::map<BodyData*, int>& bodyIndexMap);

	//		static BodyData* j2bBody(Json::Value bodyValue, StagePanel* stage);
			static BodyData* j2bBody(Json::Value bodyValue);
 			static FixtureData* j2bFixture(Json::Value fixtureValue);
 			static JointData* j2bJoint(Json::Value jointValue, 
				const std::vector<BodyData*>& bodies);

			friend class FileApapter;

		}; // FileIO
	}
}

#endif // _DEDITOR_MODELING_FILE_IO_H_