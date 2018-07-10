#include "UICtrlsMgr.h"
#include "Blackboard.h"
#include "../../EditComponent/CmptMgr.h"
#include "../../EditComponent/CmptTypeID.h"
#include "glui/glui.h"

using namespace FEDITOR;
using namespace FEDITOR::MOTOX::JOINT;

int UICtrlsMgr::m_openPartType = 0;

GLUI_FileBrowser* UICtrlsMgr::m_common_fb = NULL;

UICtrlsMgr::UICtrlsMgr(Blackboard* blackboard)
{
	m_blackboard = blackboard;
}

void UICtrlsMgr::createUIControls(CmptMgr& cmptMgr, ShortcutKeyListener* shortcutLsn)
{
	buildSettingPanel(cmptMgr);
	buildPartsPanel();
	buildJointsPanel();
	buildMotionsPanel();
}

void UICtrlsMgr::onModelEvent(const Event& event)
{
	switch (event.getID())
	{
	case Blackboard::e_OpenHead:
	case Blackboard::e_OpenBody:
	case Blackboard::e_OpenBigArm:
	case Blackboard::e_OpenSmallArm:
	case Blackboard::e_OpenBigLeg:
	case Blackboard::e_OpenSmallLeg:
	case Blackboard::e_OpenFrontWheel:
	case Blackboard::e_OpenBackWheel:
	case Blackboard::e_OpenMotorbike:
		m_textureLoadChoose[event.getID() - Blackboard::e_OpenHead]->disable();
		break;
	}
}

void UICtrlsMgr::callback(int id)
{
	switch (id)
	{
	case e_OpenPart:
		if (m_openPartType == OPEN_WHOLE_ID) m_eventList.push(Event(Blackboard::e_OpenWhole, m_common_fb->get_file()));
		else m_eventList.push(Event(Blackboard::e_OpenHead + m_openPartType, m_common_fb->get_file()));
		break;
	default:
		m_eventList.push(Event(id));
		break;
	}
}

void UICtrlsMgr::buildSettingPanel(CmptMgr& cmptMgr)
{
	GLUI_Rollout* setting_panel = new GLUI_Rollout(m_root, "Setting", true);

	cmptMgr.createUIControls(setting_panel, e_PhysTaskSettingCmpt);

	GLUI_Checkbox* alive = new GLUI_Checkbox(setting_panel, "Set all parts alive", &m_blackboard->m_partsAlive, 
		Blackboard::e_SetPartsAlive, callback);
}

void UICtrlsMgr::buildPartsPanel()
{
	GLUI_Rollout* parts_panel = new GLUI_Rollout(m_root, "Parts", false);

	GLUI_Panel* tmp_panel = new GLUI_Panel(parts_panel, "", false);
	GLUI_Panel* name_panel = new GLUI_Panel(tmp_panel, "Name");
	name_panel->set_w(BTN_WIDTH);

	new GLUI_Column(tmp_panel, false);
	GLUI_Panel* curr_panel = new GLUI_Panel(tmp_panel, "Choose");
	GLUI_RadioGroup* choose_panel = new GLUI_RadioGroup(curr_panel, &m_openPartType);

	GLUI_StaticText* text;
	// player's head
	text = new GLUI_StaticText(name_panel, "head");
	text->set_w(BTN_WIDTH);
	m_textureLoadChoose[e_TextureHead] = new GLUI_RadioButton(choose_panel, "");
	// player's body
	text = new GLUI_StaticText(name_panel, "body");
	text->set_w(BTN_WIDTH);
	m_textureLoadChoose[e_TextureBody] = new GLUI_RadioButton(choose_panel, "");
	// player's big arm
	text = new GLUI_StaticText(name_panel, "big arm");
	text->set_w(BTN_WIDTH);
	m_textureLoadChoose[e_TextureBigArm] = new GLUI_RadioButton(choose_panel, "");
	// player's small arm
	text = new GLUI_StaticText(name_panel, "small arm");
	text->set_w(BTN_WIDTH);
	m_textureLoadChoose[e_TextureSmallArm] = new GLUI_RadioButton(choose_panel, "");
	// player's big leg
	text = new GLUI_StaticText(name_panel, "big leg");
	text->set_w(BTN_WIDTH);
	m_textureLoadChoose[e_TextureBigLeg] = new GLUI_RadioButton(choose_panel, "");
	// player's small leg
	text = new GLUI_StaticText(name_panel, "small leg");
	text->set_w(BTN_WIDTH);
	m_textureLoadChoose[e_TextureSmallLeg] = new GLUI_RadioButton(choose_panel, "");
	// moto's front wheel
	text = new GLUI_StaticText(name_panel, "front wheel");
	text->set_w(BTN_WIDTH);
	m_textureLoadChoose[e_TextureFrontWheel] = new GLUI_RadioButton(choose_panel, "");
	// moto's back wheel
	text = new GLUI_StaticText(name_panel, "back wheel");
	text->set_w(BTN_WIDTH);
	m_textureLoadChoose[e_TextureBackWheel] = new GLUI_RadioButton(choose_panel, "");
	// moto's body
	text = new GLUI_StaticText(name_panel, "moto body");
	text->set_w(BTN_WIDTH);
	m_textureLoadChoose[e_TextureMotorcar] = new GLUI_RadioButton(choose_panel, "");
	// the whole
	text = new GLUI_StaticText(name_panel, "the whole");
	text->set_w(BTN_WIDTH);
	m_textureLoadChoose[e_TextureMotorcar + 1] = new GLUI_RadioButton(choose_panel, "");

	GLUI_Panel* open_panel = new GLUI_Panel(parts_panel, "Open");
	m_common_fb = new GLUI_FileBrowser(open_panel, "", false, e_OpenPart, callback);

	new GLUI_Button(parts_panel, "Save The Whole", Blackboard::e_SaveWhole, callback);
}

void UICtrlsMgr::buildJointsPanel()
{
	GLUI_Rollout* joints_panel = new GLUI_Rollout(m_root, "Joints", true);

	GLUI_Panel* choose_panel = new GLUI_Panel(joints_panel, "", false);
	GLUI_Listbox* joint_list = new GLUI_Listbox(choose_panel, "Choose: ", &m_blackboard->m_chooseJointID);
	joint_list->add_item(e_JointTypeNeck, "neck");
	joint_list->add_item(e_JointTypeShoulder, "shoulder");
	joint_list->add_item(e_JointTypeElbow, "elbow");
	joint_list->add_item(e_JointTypeHip, "hip");
	joint_list->add_item(e_JointTypeKnee, "knee");
	joint_list->add_item(e_JointTypeHand, "hand");
	joint_list->add_item(e_JointTypeFoot, "foot");

	GLUI_Panel* btn_panel = new GLUI_Panel(joints_panel, "", false);
	GLUI_Button* pos_btn = new GLUI_Button(btn_panel, "Pos", Blackboard::e_SetJointPos, callback);
	pos_btn->set_w(BTN_WIDTH);
	new GLUI_Column(btn_panel, false);
	GLUI_Button* create_btn = new GLUI_Button(btn_panel, "Create", Blackboard::e_CreateJoint, callback);
	create_btn->set_w(BTN_WIDTH);

	new GLUI_Button(joints_panel, "Create Wheels Joint", Blackboard::e_CreateWheelsJoint, callback);
}

void UICtrlsMgr::buildMotionsPanel()
{
	GLUI_Rollout* motions_panel = new GLUI_Rollout(m_root, "Motions", true);

	createJointUIItem(motions_panel, "neck", e_JointTypeNeck, Blackboard::e_ResetJointNeck);
	createJointUIItem(motions_panel, "shoulder", e_JointTypeShoulder, Blackboard::e_ResetJointShoulder);
	createJointUIItem(motions_panel, "elbow", e_JointTypeElbow, Blackboard::e_ResetJointElbow);
	createJointUIItem(motions_panel, "hip", e_JointTypeHip, Blackboard::e_ResetJointHip);
	createJointUIItem(motions_panel, "knee", e_JointTypeKnee, Blackboard::e_ResetJointKnee);

	new GLUI_Button(motions_panel, "Save", Blackboard::e_SaveWholeParams, callback);
}

void UICtrlsMgr::createJointUIItem(GLUI_Panel* parent, const std::string& name, size_t jointType, size_t ui)
{
	GLUI_Rollout* joint_panel = new GLUI_Rollout(parent, name.c_str(), false);

	GLUI_Panel* setting_panel = new GLUI_Panel(joint_panel, "setting");
	new GLUI_Checkbox(setting_panel, "enable limit", &m_blackboard->m_jointParams[jointType].enableLimit, ui, callback);
	new GLUI_Column(setting_panel, false);
	new GLUI_Checkbox(setting_panel, "enable motor", &m_blackboard->m_jointParams[jointType].enableMotor, ui, callback);

	GLUI_Panel* speed_panel = new GLUI_Panel(joint_panel, "speed");
	GLUI_Spinner* positive_speed = new GLUI_Spinner(speed_panel, "positive", &m_blackboard->m_jointParams[jointType].positive_speed, ui, callback);
	positive_speed->set_float_limits(0, 10);
	GLUI_Spinner* negative_speed = new GLUI_Spinner(speed_panel, "negative", &m_blackboard->m_jointParams[jointType].negative_speed, ui, callback);
	negative_speed->set_float_limits(-10, 0);

	GLUI_Panel* angle_panel = new GLUI_Panel(joint_panel, "angle");
	GLUI_Spinner* left_angle = new GLUI_Spinner(angle_panel, "left", &m_blackboard->m_jointParams[jointType].left_angle, ui, callback);
	left_angle->set_float_limits(-1, 1);
	GLUI_Spinner* mid_angle = new GLUI_Spinner(angle_panel, "mid", &m_blackboard->m_jointParams[jointType].mid_angle, ui, callback);
	mid_angle->set_float_limits(-1, 1);
	GLUI_Spinner* right_angle = new GLUI_Spinner(angle_panel, "right", &m_blackboard->m_jointParams[jointType].right_angle, ui, callback);
	right_angle->set_float_limits(-1, 1);

	GLUI_Panel* torque_panel = new GLUI_Panel(joint_panel, "torque");
	GLUI_Spinner* max_torque = new GLUI_Spinner(torque_panel, "max", &m_blackboard->m_jointParams[jointType].max_torque, ui, callback);
	max_torque->set_float_limits(0, 200);
}