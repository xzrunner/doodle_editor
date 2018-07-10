#include "Frame.h"
#include "defs.h"

#include "SettingOperatingDlg.h"
#include "SettingViewDlg.h"

#include "Task/ManualCompose/Task.h"
#include "Task/CompressPictures/Task.h"
#include "Task/AutomaticMerge/Task.h"
#include "Task/BoundaryExtraction/Task.h"

#include "Task/TextureEdit/Task.h"
#include "Task/LineEdit/Task.h"
#include "Task/PolygonEdit/Task.h"

#include "Task/Combination/Task.h"
#include "Task/Modeling/Task.h"

#include "Task/Skater/Task.h"
#include "Task/MotoX/Task.h"
#include "Task/ShootBubble/Task.h"
#include "Task/Monster/Task.h"
#include "Task/MagicDefence/Task.h"
#include "Task/HillClimb/Task.h"

using namespace deditor;

static const wxString VERSION = wxT("0.13.0423");

BEGIN_EVENT_TABLE(Frame, wxFrame)
	EVT_MENU(wxID_NEW, Frame::onNew)
	EVT_MENU(wxID_OPEN, Frame::onOpen)
	EVT_MENU(wxID_SAVE, Frame::onSave)
	EVT_MENU(wxID_SAVEAS, Frame::onSaveAs)

	EVT_MENU(wxID_EXIT, Frame::onQuit)
	EVT_MENU(wxID_HELP, Frame::onAbout)
	EVT_MENU(ID_PREVIEW, Frame::onPreview)
END_EVENT_TABLE()

Frame::Frame(const wxString& title)
	: wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(800, 600))
{
	m_task = NULL;
	initMenuBar();
}

void Frame::onNew(wxCommandEvent& event)
{
	if (!m_task) return;

	setCurrFilename();
	m_task->clear();
}

void Frame::onOpen(wxCommandEvent& event)
{
	if (!m_task) return;

	wxFileDialog dlg(this, wxT("添加现有数据"), wxEmptyString, wxEmptyString, 
		wxT("*_") + m_task->getFileTag() + wxT(".txt"), wxFD_OPEN);
	if (dlg.ShowModal() == wxID_OK)
	{
		m_task->clear();
		m_currFilename = dlg.GetPath();
		SetTitle(wxgui::FilenameTools::getFilename(dlg.GetPath()));
		m_task->loadFromTextFile(dlg.GetPath());
	}
}

void Frame::onSave(wxCommandEvent& event)
{
	if (!m_task) return;

	if (!m_currFilename.empty())
	{
		SetTitle(wxgui::FilenameTools::getFilename(m_currFilename));
		m_task->storeToTextFile(m_currFilename);
	}
}

void Frame::onSaveAs(wxCommandEvent& event)
{
	if (!m_task) return;

	wxFileDialog dlg(this, wxT("保存数据"), wxEmptyString, wxEmptyString, 
		wxT("*_") + m_task->getFileTag() + wxT(".txt"), wxFD_SAVE);
	if (dlg.ShowModal() == wxID_OK)
	{
		wxString fixed = wxgui::FilenameTools::getFilenameAddTag(dlg.GetPath(), m_task->getFileTag(), "txt");
		m_currFilename = fixed;
		m_task->storeToTextFile(fixed);
	}
}

void Frame::onQuit(wxCommandEvent& event)
{
	Close(true);
}

void Frame::onAbout(wxCommandEvent& event)
{
	wxString msg;
//	msg.Printf(wxT("Game common tools & level making tools.\n(c) zz, 2012"));
	msg.Printf(wxT("Version: ") + VERSION);
	wxMessageBox(msg, wxT("About DoodleEditor"), wxOK | wxICON_INFORMATION, this);
}

void Frame::onManualComposeTaskMenu(wxCommandEvent& event)
{
	delete m_task;
 	m_task = manual_compose::Task::create(this);
}

void Frame::onCompressPicturesTaskMenu(wxCommandEvent& event)
{
	delete m_task;
	m_task = compress_pictures::Task::create(this);
}

void Frame::onAutomaticMergeTaskMenu(wxCommandEvent& event)
{
	delete m_task;
	m_task = automatic_merge::Task::create(this);
}

void Frame::onBoundaryExtractionTaskMenu(wxCommandEvent& event)
{
	delete m_task;
	m_task = boundary_extraction::Task::create(this);
}

void Frame::onShapeEditTaskMenu(wxCommandEvent& event)
{
	delete m_task;
	m_task = line_edit::Task::create(this);
}

void Frame::onTextureEditTaskMenu(wxCommandEvent& event)
{
	delete m_task;
	m_task = texture_edit::Task::create(this);
}

void Frame::onPolygonFillingMenu(wxCommandEvent& event)
{
	delete m_task;
	m_task = polygon_edit::Task::create(this);
}

void Frame::onDrawingMenu(wxCommandEvent& event)
{
	delete m_task;
	m_task = combination::Task::create(this);
}

void Frame::onModelingMenu(wxCommandEvent& event)
{
	delete m_task;
	m_task = modeling::Task::create(this);
}

void Frame::onAnimationMenu(wxCommandEvent& event)
{
	wxMessageBox("coming soon...");
}

void Frame::onParticleMenu(wxCommandEvent& event)
{
	wxMessageBox("coming soon...");
}

void Frame::onSkaterTaskMenu(wxCommandEvent& event)
{
	delete m_task;
	m_task = skater::Task::create(this);
}

void Frame::onMotoXTaskMenu(wxCommandEvent& event)
{
	delete m_task;
	m_task = motox::Task::create(this);
}

void Frame::onShootBubbleTaskMenu(wxCommandEvent& event)
{
	delete m_task;
	m_task = shoot_bubble::Task::create(this);
}

void Frame::onMonsterTaskMenu(wxCommandEvent& event)
{
	delete m_task;
	m_task = monster::Task::create(this);
}

void Frame::onMagicDefenceTaskMenu(wxCommandEvent& event)
{
	delete m_task;
	m_task = magic_defence::Task::create(this);
}

void Frame::onHillClimbTaskMenu(wxCommandEvent& event)
{
	delete m_task;
	m_task = hill_climb::Task::create(this);
}

void Frame::onSettingOperatingMenu(wxCommandEvent& event)
{
	SettingOperatingDlg dlg(this);
	dlg.ShowModal();
}

void Frame::onSettingViewMenu(wxCommandEvent& event)
{
	if (m_task)
	{
		SettingViewDlg dlg(this, m_task->getCanvas());
		dlg.ShowModal();
	}
}

void Frame::onPreview(wxCommandEvent& event)
{
	if (m_task)
		m_task->onPreview();
}

void Frame::initMenuBar()
{
	wxMenuBar* menuBar = new wxMenuBar;

	menuBar->Append(initFileBar(), "文件");

	menuBar->Append(initCommonTaskBar(), "【常用工具】");
	menuBar->Append(initSimpleTaskBar(), "【元件编辑】");
	menuBar->Append(initComplexTaskBar(), "【复合工具】");
	menuBar->Append(initLevelTaskBar(), "【关卡制作】");

	menuBar->Append(initViewBar(), wxT("视图"));
	menuBar->Append(initSettingsBar(), wxT("设置"));
	menuBar->Append(initHelpBar(), wxT("关于"));

	SetMenuBar(menuBar);
}

wxMenu* Frame::initFileBar()
{
	wxMenu* fileMenu = new wxMenu;
	fileMenu->Append(wxID_NEW, wxT("新建\tCtrl+N"), wxT("Create a project"));
	fileMenu->Append(wxID_OPEN, wxT("打开...\tCtrl+O"), wxT("Open a project"));
	fileMenu->AppendSeparator();
	fileMenu->Append(wxID_SAVE, wxT("保存\tCtrl+S"), wxT("Save the project"));
	fileMenu->Append(wxID_SAVEAS, wxT("另存为...\tF11", wxT("Save to a new file")));
	fileMenu->AppendSeparator();
	fileMenu->Append(wxID_EXIT, wxT("退出\tAlt+X"), wxT("Quit GameFruits"));
	return fileMenu;
}

wxMenu* Frame::initCommonTaskBar()
{
	wxMenu* menu = new wxMenu;

	int id = ID_TASK_COMMON_BEGIN;
	menu->Append(id++, wxT("简单拼图"));
	Connect(id - 1, wxEVT_COMMAND_MENU_SELECTED, 
		wxCommandEventHandler(Frame::onManualComposeTaskMenu));
	menu->Append(id++, wxT("图片压缩"));
	Connect(id - 1, wxEVT_COMMAND_MENU_SELECTED, 
		wxCommandEventHandler(Frame::onCompressPicturesTaskMenu));
	menu->Append(id++, wxT("自动合图"));
	Connect(id - 1, wxEVT_COMMAND_MENU_SELECTED, 
		wxCommandEventHandler(Frame::onAutomaticMergeTaskMenu));
	menu->Append(id++, wxT("边界提取"));
	Connect(id - 1, wxEVT_COMMAND_MENU_SELECTED, 
		wxCommandEventHandler(Frame::onBoundaryExtractionTaskMenu));

	return menu;
}

wxMenu* Frame::initSimpleTaskBar()
{
	wxMenu* menu = new wxMenu;

	int id = ID_TASK_SIMPLE_BEGIN;
	menu->Append(id++, wxT("纹理"));
	Connect(id - 1, wxEVT_COMMAND_MENU_SELECTED, 
		wxCommandEventHandler(Frame::onTextureEditTaskMenu));
	menu->Append(id++, wxT("线"));
	Connect(id - 1, wxEVT_COMMAND_MENU_SELECTED, 
		wxCommandEventHandler(Frame::onShapeEditTaskMenu));
	menu->Append(id++, wxT("多边形"));
	Connect(id - 1, wxEVT_COMMAND_MENU_SELECTED, 
		wxCommandEventHandler(Frame::onPolygonFillingMenu));

	return menu;
}

wxMenu* Frame::initComplexTaskBar()
{
	wxMenu* menu = new wxMenu;

	int id = ID_TASK_COMPLEX_BEGIN;
	menu->Append(id++, wxT("组合"));
	Connect(id - 1, wxEVT_COMMAND_MENU_SELECTED, 
		wxCommandEventHandler(Frame::onDrawingMenu));
	menu->Append(id++, wxT("建模"));
	Connect(id - 1, wxEVT_COMMAND_MENU_SELECTED, 
		wxCommandEventHandler(Frame::onModelingMenu));
	menu->Append(id++, wxT("动画"));
	Connect(id - 1, wxEVT_COMMAND_MENU_SELECTED, 
		wxCommandEventHandler(Frame::onAnimationMenu));
	menu->Append(id++, wxT("粒子"));
	Connect(id - 1, wxEVT_COMMAND_MENU_SELECTED, 
		wxCommandEventHandler(Frame::onParticleMenu));

	return menu;
}

wxMenu* Frame::initLevelTaskBar()
{
	wxMenu* menu = new wxMenu;

	int id = ID_TASK_LEVEL_BEGIN;
	menu->Append(id++, wxT("Skater"));
	Connect(id - 1, wxEVT_COMMAND_MENU_SELECTED, 
		wxCommandEventHandler(Frame::onSkaterTaskMenu));
	menu->Append(id++, wxT("MotoX"));
	Connect(id - 1, wxEVT_COMMAND_MENU_SELECTED, 
		wxCommandEventHandler(Frame::onMotoXTaskMenu));
	menu->Append(id++, wxT("ShootBubble"));
	Connect(id - 1, wxEVT_COMMAND_MENU_SELECTED, 
		wxCommandEventHandler(Frame::onShootBubbleTaskMenu));
	menu->Append(id++, wxT("Monster"));
	Connect(id - 1, wxEVT_COMMAND_MENU_SELECTED, 
		wxCommandEventHandler(Frame::onMonsterTaskMenu));
	menu->Append(id++, wxT("MagicDefence"));
	Connect(id - 1, wxEVT_COMMAND_MENU_SELECTED, 
		wxCommandEventHandler(Frame::onMagicDefenceTaskMenu));
	menu->Append(id++, wxT("HillClimb"));
	Connect(id - 1, wxEVT_COMMAND_MENU_SELECTED, 
		wxCommandEventHandler(Frame::onHillClimbTaskMenu));

	return menu;
}

wxMenu* Frame::initViewBar()
{
	wxMenu* menu = new wxMenu;
	menu->Append(ID_PREVIEW, wxT("&Preview\tCtrl+Enter"), wxEmptyString);

	return menu;
}

wxMenu* Frame::initSettingsBar()
{
	wxMenu* menu = new wxMenu;

	int id = ID_OTHERS_BEGIN;
	menu->Append(id++, wxT("操作..."));
	Connect(id - 1, wxEVT_COMMAND_MENU_SELECTED, 
		wxCommandEventHandler(Frame::onSettingOperatingMenu));
	menu->Append(id++, wxT("显示..."));
	Connect(id - 1, wxEVT_COMMAND_MENU_SELECTED, 
		wxCommandEventHandler(Frame::onSettingViewMenu));

	return menu;
}

wxMenu* Frame::initHelpBar()
{
	wxMenu* helpMenu = new wxMenu;
	helpMenu->Append(wxID_HELP, wxT("&About...\tF1"), wxT("Show about dialog"));

	return helpMenu;
}

void Frame::setCurrFilename()
{
	int id = 0;
	while (true)
	{
		wxString str = 
			wxT("new") + 
			wxString::FromDouble(id++) + 
			wxT("_") + 
			m_task->getFileTag() + 
			wxT(".txt");

		if (!wxgui::FilenameTools::isExist(str))
		{
			m_currFilename = str;
			break;
		}
	}
}