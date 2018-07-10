#ifndef _FEDITOR_MOTOX_JOINT_UI_CTRLS_MGR_H_
#define _FEDITOR_MOTOX_JOINT_UI_CTRLS_MGR_H_
#include "../../AbstractUICtrlsMgr.h"
#include "../ActorDefs.h"

class GLUI_FileBrowser;
class GLUI_RadioButton;
class GLUI_Panel;

namespace FEDITOR
{
	namespace MOTOX
	{
		namespace JOINT
		{
			class Blackboard;

			class UICtrlsMgr : public AbstractUICtrlsMgr
			{
			public:
				UICtrlsMgr(Blackboard* blackboard);

				virtual void createUIControls(CmptMgr& cmptMgr, ShortcutKeyListener* shortcutLsn); 
				virtual void onModelEvent(const Event& event);

			private:
				static void callback(int id);

				enum
				{
					e_OpenPart = EVENT_ID_BASE_PRIVATE_UI_CTRLS_MGR
				};

			private:
				void buildSettingPanel(CmptMgr& cmptMgr);
				void buildPartsPanel();
				void buildJointsPanel();
				void buildMotionsPanel();

				void createJointUIItem(GLUI_Panel* parent, const std::string& name, size_t jointType, size_t ui);

			private:
				static const size_t TEXTURE_COUNT = 9;

				enum TextureType
				{
					e_TextureHead,
					e_TextureBody,
					e_TextureBigArm,
					e_TextureSmallArm,
					e_TextureBigLeg,
					e_TextureSmallLeg,
					e_TextureFrontWheel,
					e_TextureBackWheel,
					e_TextureMotorcar
				};

			private:
				Blackboard* m_blackboard;

				static int m_openPartType;
					// 0 head
					// 1 body
					// 2 big arm
					// 3 small arm
					// 4 big leg
					// 5 small leg
					// 6 front wheel
					// 7 back wheel
					// 8 motorcar
					// 9 the whole
				static const int OPEN_WHOLE_ID = 9;

				GLUI_RadioButton* m_textureLoadChoose[TEXTURE_COUNT + 1];

				static GLUI_FileBrowser* m_common_fb;

			}; // UICtrlsMgr 
		}
	}
}

#endif // _FEDITOR_MOTOX_JOINT_UI_CTRLS_MGR_H_