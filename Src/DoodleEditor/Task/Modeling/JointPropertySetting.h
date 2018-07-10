#ifndef _DEDITOR_MODELING_JOINT_PROPERTY_SETTING_H_
#define _DEDITOR_MODELING_JOINT_PROPERTY_SETTING_H_

#include <wxGUI/wxGUI.h>

namespace deditor
{
	namespace modeling
	{
		class JointData;
		class RevoluteJoint;
		class PrismaticJoint;
		class DistanceJoint;
		class WheelJoint;

		class JointPropertySetting : public wxgui::IPropertySetting
		{
		public:
			JointPropertySetting(wxgui::EditPanel* editPanel, JointData* joint);

			virtual void updatePanel(wxgui::PropertySettingPanel* panel);

			virtual void onPropertyGridChange(const wxString& name, const wxAny& value);
			virtual void updatePropertyGrid(wxgui::PropertySettingPanel* panel);
			virtual void enablePropertyGrid(wxgui::PropertySettingPanel* panel, bool bEnable);

		private:
			void createPropertyPanel(RevoluteJoint* joint, wxPropertyGrid* pg);
			void updatePropertyPanel(RevoluteJoint* joint, wxPropertyGrid* pg);
			void onPropertyGridChange(RevoluteJoint* joint,
				const wxString& name, const wxAny& value);

			void createPropertyPanel(PrismaticJoint* joint, wxPropertyGrid* pg);
			void updatePropertyPanel(PrismaticJoint* joint, wxPropertyGrid* pg);
			void onPropertyGridChange(PrismaticJoint* joint,
				const wxString& name, const wxAny& value);

			void createPropertyPanel(DistanceJoint* joint, wxPropertyGrid* pg);
			void updatePropertyPanel(DistanceJoint* joint, wxPropertyGrid* pg);
			void onPropertyGridChange(DistanceJoint* joint,
				const wxString& name, const wxAny& value);

			void createPropertyPanel(WheelJoint* joint, wxPropertyGrid* pg);
			void updatePropertyPanel(WheelJoint* joint, wxPropertyGrid* pg);
			void onPropertyGridChange(WheelJoint* joint,
				const wxString& name, const wxAny& value);

		private:
			JointData* m_joint;

		}; // JointPropertySetting
	}
}

#endif // _DEDITOR_MODELING_JOINT_PROPERTY_SETTING_H_