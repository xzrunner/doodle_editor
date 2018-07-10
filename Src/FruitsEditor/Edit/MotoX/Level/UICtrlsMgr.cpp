#include "UICtrlsMgr.h"
#include "Blackboard.h"
#include "../../EditComponent/CmptMgr.h"
#include "../../EditComponent/CmptTypeID.h"
#include "../../ShortcutKeyListener.h"
#include "glui/glui.h"

using namespace FEDITOR;
using namespace FEDITOR::MOTOX::LEVEL;

int UICtrlsMgr::m_openFileType = 0;

GLUI_FileBrowser* UICtrlsMgr::m_common_fb = NULL;

UICtrlsMgr::UICtrlsMgr(Blackboard* blackboard)
{
	m_blackboard = blackboard;
}

void UICtrlsMgr::createUIControls(CmptMgr& cmptMgr, ShortcutKeyListener* shortcutLsn)
{
	cmptMgr.createUIControls(m_root, e_LayersMgrCmpt);

	buildSettingPanel(cmptMgr);
	buildOpenPanel();
	buildTrackChainPanel(cmptMgr);
	buildTilesPanel();
	buildActorSettingPanel();

//	cmptMgr.createUIControls(m_root, e_LayersIOCmpt);

	shortcutLsn->registerEventList(&m_eventList);
	shortcutLsn->registerKeyEvent('d', Blackboard::e_DrawTrackChain);
	shortcutLsn->registerKeyEvent('e', Blackboard::e_EditTrackChain);
}

void UICtrlsMgr::callback(int id)
{
	switch (id)
	{
	case e_OpenFile:
		switch (m_openFileType)
		{
		case 0:
			m_eventList.push(Event(Blackboard::e_OpenBgTexture, m_common_fb->get_file()));
			break;
		case 1:
			m_eventList.push(Event(Blackboard::e_OpenBgShapes, m_common_fb->get_file()));
			break;
		case 2:
			m_eventList.push(Event(Blackboard::e_OpenTrackChain, m_common_fb->get_file()));
			break;
		case 3:
			m_eventList.push(Event(Blackboard::e_OpenTileSprite, m_common_fb->get_file()));
			break;
		case 4:
			m_eventList.push(Event(Blackboard::e_OpenMotorbike, m_common_fb->get_file()));
			break;
		case 5:
			m_eventList.push(Event(Blackboard::e_OpenAllSprites, m_common_fb->get_file()));
			break;
		}
		break;
	default:
		m_eventList.push(Event(id));
	}
}

void UICtrlsMgr::buildSettingPanel(CmptMgr& cmptMgr)
{
	GLUI_Rollout* panel = new GLUI_Rollout(m_root, "Settings", false);

	cmptMgr.createUIControls(panel, e_PhysTaskSettingCmpt);

	new GLUI_Checkbox(panel, "Camera Focus on Moto", &m_blackboard->m_cameraFocusMoto);

	GLUI_Spinner* gravity = new GLUI_Spinner(panel, "Gravity", &m_blackboard->m_gravity, Blackboard::e_SetGravity, callback);
	gravity->set_float_limits(10, 50);

	new GLUI_Button(panel, "Mouse Drag", Blackboard::e_SetMouseDrag, callback);
}

void UICtrlsMgr::buildOpenPanel()
{
	GLUI_Rollout* panel = new GLUI_Rollout(m_root, "Open", false);

	GLUI_RadioGroup* choose = new GLUI_RadioGroup(panel, &m_openFileType);
	new GLUI_RadioButton(choose, "BG Picture (*.jpg, *.png)");
	new GLUI_RadioButton(choose, "BG Shapes (.)");
	new GLUI_RadioButton(choose, "Track Chains (*_chains.txt)");
	new GLUI_RadioButton(choose, "Tile Sprites (*.png, *_loops.txt)");
	new GLUI_RadioButton(choose, "Motorbike (motox_joints.txt)");
	new GLUI_RadioButton(choose, "All Sprites (*.txt)");

	m_common_fb = new GLUI_FileBrowser(panel, "", false, e_OpenFile, callback);
}

void UICtrlsMgr::buildTrackChainPanel(CmptMgr& cmptMgr)
{
	GLUI_Rollout* panel = new GLUI_Rollout(m_root, "Track Chain", false);
	
	cmptMgr.createUIControls(panel, e_NodeCaptureCmpt);

	GLUI_Panel* editPanel = new GLUI_Panel(panel, "", false);

	GLUI_Button* btn = new GLUI_Button(editPanel, "Draw (D)", Blackboard::e_DrawTrackChain, callback);
	btn->set_w(BTN_WIDTH);
	new GLUI_Column(editPanel, false);
	btn = new GLUI_Button(editPanel, "Edit (E)", Blackboard::e_EditTrackChain, callback);
	btn->set_w(BTN_WIDTH);
	new GLUI_Column(editPanel, false);
	btn = new GLUI_Button(editPanel, "Save (Alt+S)", Blackboard::e_SaveTrackChain, callback);
	btn->set_w(BTN_WIDTH);

	GLUI_Spinner* friction = new GLUI_Spinner(panel, "friction", &m_blackboard->m_trackFriction, Blackboard::e_SetTrackFriction, callback);
	friction->set_float_limits(0, 4);
}

void UICtrlsMgr::buildTilesPanel()
{
	GLUI_Rollout* panel = new GLUI_Rollout(m_root, "Tiles", false);

	GLUI_Panel* gravityPanel = new GLUI_Panel(panel, "Gravity");
	GLUI_RadioGroup* choose = new GLUI_RadioGroup(gravityPanel, 
		&m_blackboard->m_chooseWorldType, Blackboard::e_SetGravityDir, callback);
	new GLUI_RadioButton(choose, "normal");
	new GLUI_Column(choose, false);
	new GLUI_RadioButton(choose, "reverse");

	GLUI_Panel* scalePanel = new GLUI_Panel(panel, "Scale");
	Blackboard* bb = static_cast<Blackboard*>(m_blackboard);
	bb->m_scaleSpinner = new GLUI_Spinner(scalePanel, "scale", &m_blackboard->m_spriteScale);
	bb->m_scaleSpinner->set_float_limits(0.1f, 10.0f);
	bb->m_mirrorCheckbox = new GLUI_Checkbox(scalePanel, "mirror", &m_blackboard->m_flagSpriteMirror);
	new GLUI_Button(scalePanel, "Reset", Blackboard::e_ResetScale, callback);

	GLUI_Panel* batchPanel = new GLUI_Panel(panel, "Random Batch");
	GLUI_Spinner* num = new GLUI_Spinner(batchPanel, "num", &m_blackboard->m_batchNum);
	num->set_int_limits(1, 10);
	GLUI_Spinner* radius = new GLUI_Spinner(batchPanel, "radius", &m_blackboard->m_batchRandomRadius);
	radius->set_int_limits(1, 100);
	new GLUI_Checkbox(batchPanel, "Open", &m_blackboard->m_batchState);

	GLUI_Panel* settingPanel = new GLUI_Panel(panel, "Setting");
	new GLUI_Checkbox(settingPanel, "Stop Instant: ", &m_blackboard->m_stopInstant);

	new GLUI_Button(panel, "Save All Sprites", Blackboard::e_SaveSprites, callback);
}

void UICtrlsMgr::buildActorSettingPanel()
{
	GLUI_Rollout* panel = new GLUI_Rollout(m_root, "Actor Setting", false);

	GLUI_Spinner* friction = new GLUI_Spinner(panel, "friction", &m_blackboard->m_motoFriction, Blackboard::e_SetMotoFriction, callback);
	friction->set_float_limits(0, 4);
	// 	GLUI_Spinner* moto_density = new GLUI_Spinner(panel, "moto density", &m_blackboard->m_motoDensity, Blackboard::e_SetMotoDensity, callback);
	// 	moto_density->set_float_limits(0.5f, 10.0f);
	// 	GLUI_Spinner* player_density = new GLUI_Spinner(panel, "player density", &m_blackboard->m_motoDensity, Blackboard::e_SetPlayerDensity, callback);
	// 	player_density->set_float_limits(0.5f, 5.0f);
	GLUI_Spinner* speed = new GLUI_Spinner(panel, "speed", &m_blackboard->m_motoSpeed, Blackboard::e_SetMotoSpeed, callback);
	speed->set_float_limits(10.0f, 200.0f);
	GLUI_Spinner* acc = new GLUI_Spinner(panel, "acc", &m_blackboard->m_motoAcc, Blackboard::e_SetMotoAcc, callback);
	acc->set_float_limits(5.0f, 100.0f);
	GLUI_Spinner* torque = new GLUI_Spinner(panel, "torque", &m_blackboard->m_motoTorque, Blackboard::e_SetMotoTorque, callback);
	torque->set_float_limits(0.5f, 15.0f);
	GLUI_Spinner* damping = new GLUI_Spinner(panel, "damping", &m_blackboard->m_motoDamping, Blackboard::e_SetMotoDamping, callback);
	damping->set_float_limits(0.1f, 5.0f);
	GLUI_Spinner* hz = new GLUI_Spinner(panel, "hz", &m_blackboard->m_motoHz, Blackboard::e_SetMotoHz, callback);
	hz->set_float_limits(1, 30);
	GLUI_Spinner* max_motor_torque = new GLUI_Spinner(panel, "motor torque", &m_blackboard->m_motoMaxMotorTorque, Blackboard::e_SetMotoMaxMotorTorque, callback);
	max_motor_torque->set_float_limits(20, 200);
}