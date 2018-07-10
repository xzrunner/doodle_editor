#ifndef _DEDITOR_MODELING_FILE_ADAPTER_H_
#define _DEDITOR_MODELING_FILE_ADAPTER_H_

#include <wxGUI/wxGUI.h>
#include <json/json.h>

namespace deditor
{
	namespace modeling
	{
		class BodyData;
		class JointData;

		class FileApapter
		{
		public:
			~FileApapter();

			void resolve(const wxString& filepath);

			BodyData* queryBody(size_t index) const;

			BodyData* queryBody(const wxString& name) const;
			JointData* queryJoint(const wxString& name) const;

		private:
			void clear();

		private:
			std::vector<BodyData*> m_bodies;

			std::map<wxString, BodyData*> m_nameBodyMap;
			std::map<wxString, JointData*> m_nameJointMap;

		}; // FileApapter
	}
}

#endif // _DEDITOR_MODELING_FILE_ADAPTER_H_