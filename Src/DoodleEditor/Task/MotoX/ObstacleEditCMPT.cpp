#include "ObstacleEditCMPT.h"
#include "ObstacleCommonCMPT.h"
#include "ObstacleBridgeCMPT.h"
#include "ObstacleSoftCMPT.h"
#include "ObstacleBreakableCMPT.h"
#include "ObstaclePackage2CMPT.h"
#include "BreakableSprite.h"
#include "StagePanel.h"
#include "TypesDef.h"

using namespace deditor::motox;

const wxString ObstacleEditCMPT::OBSTACLE_FILE_TAG = wxT("obstacle");

ObstacleEditCMPT::ObstacleEditCMPT(wxWindow* parent, const wxString& name,
								   StagePanel* editPanel, wxgui::LibraryPanel* libraryPanel,
								   wxgui::PropertySettingPanel* propertyPanel)
	: wxgui::AbstractEditCMPT(parent, name, editPanel)
	, m_libraryPanel(libraryPanel)
{
	addChild(new ObstacleCommonCMPT(this, wxT("普通"), editPanel, libraryPanel, propertyPanel));
	addChild(new ObstacleBridgeCMPT(this, wxT("桥"), editPanel));
	addChild(new ObstacleSoftCMPT(this, wxT("软体"), editPanel, libraryPanel));
	addChild(new ObstacleBreakableCMPT(this, wxT("破碎"), editPanel, libraryPanel, propertyPanel));
	addChild(new ObstaclePackage2CMPT(this, wxT("打包"), editPanel));
}

void ObstacleEditCMPT::loadToEditpanel(StagePanel* editPanel, 
									   const wxString& filepath)
{
	std::ifstream fin(filepath.fn_str());

	size_t size;
	fin >> size;
	for (size_t i = 0; i < size; ++i)
	{
		std::string filename = StringTools::getLine(fin);

		std::string strLine = StringTools::getLine(fin);
		std::stringstream ss(strLine);

		f2Vec2 pos;
		float angle;
		float scale;
		int type;
		ss >> pos >> angle >> scale >> type;

		wxgui::ISprite* sprite;
		if (type == e_common)
		{
			wxgui::ISymbol* symbol = wxgui::SymbolMgr::Instance()->getSymbol(filename);
			sprite = wxgui::SpriteFactory::create(symbol);
		}
		else if (type == e_breakable)
		{
			LibraryBreakableItem* symbol = new LibraryBreakableItem;
			symbol->loadFromFile(filename);
			sprite = new BreakableSprite(symbol, !symbol->getSpriteCombineSymbol());
		}

		sprite->setTransform(pos, angle);
		sprite->setScale(scale);
		sprite->loadBodyFromFile();
		if (type == e_breakable)
			sprite->getBody()->getBody()->SetUserData(new int(BREAKABLE_ID));

		editPanel->insertSprite(sprite);
		sprite->release();
	}

	fin.close();
}

wxSizer* ObstacleEditCMPT::initLayout()
{
	wxSizer* sizer = new wxBoxSizer(wxVERTICAL);
	sizer->AddSpacer(5);
	{
		wxButton* btn = new wxButton(this, wxID_ANY, wxT("导入..."));
		Connect(btn->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, 
			wxCommandEventHandler(ObstacleEditCMPT::onLoadText));
		sizer->Add(btn);
	}
	sizer->AddSpacer(5);
	{
		wxButton* btn = new wxButton(this, wxID_ANY, wxT("导出..."));
		Connect(btn->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, 
			wxCommandEventHandler(ObstacleEditCMPT::onStoreText));
		sizer->Add(btn);
	}
	sizer->AddSpacer(15);
	sizer->Add(initChildrenLayout());
	return sizer;
}

void ObstacleEditCMPT::onLoadText(wxCommandEvent& event)
{
	wxString filter = wxT("*_") + OBSTACLE_FILE_TAG + wxT(".txt");
	wxFileDialog dlg(this, wxT("导入障碍文件"), wxEmptyString, wxEmptyString, filter, wxFD_OPEN);
	if (dlg.ShowModal() == wxID_OK)
	{
		loadFromTextFile(dlg.GetPath());
	}
}

void ObstacleEditCMPT::onStoreText(wxCommandEvent& event)
{
	wxString filter = wxT("*_") + OBSTACLE_FILE_TAG + wxT(".txt");
	wxFileDialog dlg(this, wxT("导出障碍文件"), wxEmptyString, wxEmptyString, filter, wxFD_SAVE);
	if (dlg.ShowModal() == wxID_OK)
	{
		wxString fixed = wxgui::FilenameTools::getFilenameAddTag(dlg.GetPath(), OBSTACLE_FILE_TAG, "txt");
		storeToTextFile(fixed);
	}
}

void ObstacleEditCMPT::loadFromTextFile(const wxString& filepath)
{
	loadToEditpanel(static_cast<StagePanel*>(m_editPanel), filepath);
	m_libraryPanel->loadFromSymbolMgr(*wxgui::SymbolMgr::Instance());
	m_editPanel->resetCanvas();
}

void ObstacleEditCMPT::storeToTextFile(const wxString& filepath) const
{
	const std::vector<wxgui::ISprite*>& sprites = static_cast<StagePanel*>(m_editPanel)->getAllPhysics();

	std::ofstream fout(filepath.fn_str());
	fout << sprites.size() << '\n';
	for (size_t i = 0, n = sprites.size(); i < n; ++i)
	{
		wxgui::ISprite* sprite = sprites[i];

		int type;
		wxString path;
		BreakableSprite* breakable = dynamic_cast<BreakableSprite*>(sprite);
		if (breakable)
		{
			type = e_breakable;
			path = breakable->getFilepath();
		}
		else
		{
			type = e_common;
			path = sprite->getSymbol().getFilepath();
		}

		fout << path << '\n';
		fout << sprite->getPosition() << " " << sprite->getAngle() << " " 
			<< sprite->getScale() << " " << type << '\n';
	}
	fout.close();
}