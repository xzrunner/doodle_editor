#include "ObstaclePackage2CMPT.h"
#include "ObstacleEditCMPT.h"
#include "StagePanel.h"
#include "BreakableSprite.h"

#include "Frame/defs.h"

using namespace deditor::motox;

ObstaclePackage2CMPT::ObstaclePackage2CMPT(wxWindow* parent, const wxString& name, 
										   StagePanel* editPanel)
	: AbstractEditCMPT(parent, name, editPanel)
	, m_editPanel(editPanel)
{
	m_editOP = new wxgui::ZoomViewOP(editPanel, true);
}

void ObstaclePackage2CMPT::packageToBin(StagePanel* editPanel, const wxString& src, 
										const wxString& mergeFile, const std::vector<wxString>& obstacleFiles,
										const wxString& dst)
{
	ObstacleEditCMPT::loadToEditpanel(editPanel, src);

	automatic_merge::FileAdapter merged;
	merged.resolve(mergeFile);

	storeToBinFile(editPanel, merged, obstacleFiles, dst);

	editPanel->clear();
}

wxSizer* ObstaclePackage2CMPT::initLayout()
{
	wxSizer* sizer = new wxBoxSizer(wxVERTICAL);
	//{
	//	wxButton* btn = new wxButton(this, wxID_ANY, wxT("导出bin..."));
	//	Connect(btn->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, 
	//		wxCommandEventHandler(ObstaclePackage2CMPT::onStoreToBinFile));
	//	sizer->Add(btn);
	//}
	//sizer->AddSpacer(5);
	//{
	//	wxButton* btn = new wxButton(this, wxID_ANY, wxT("导入bin..."));
	//	Connect(btn->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, 
	//		wxCommandEventHandler(ObstaclePackage2CMPT::onLoadFromBinFile));
	//	sizer->Add(btn);
	//}
	//sizer->AddSpacer(10);
	//{
	//	wxButton* btn = new wxButton(this, wxID_ANY, wxT("导入合图文件..."));
	//	Connect(btn->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, 
	//		wxCommandEventHandler(ObstaclePackage2CMPT::onLoadMergedFile));
	//	sizer->Add(btn);
	//}
	return sizer;
}

void ObstaclePackage2CMPT::onStoreToBinFile(wxCommandEvent& event)
{
// 	wxString filter = wxT("*_") + ObstacleEditCMPT::OBSTACLE_FILE_TAG + wxT(".bin");
// 	wxFileDialog dlg(this, wxT("导出tile二进制文件"), wxEmptyString, wxEmptyString, filter, wxFD_SAVE);
// 	if (dlg.ShowModal() == wxID_OK)
// 	{
// 		wxString fixed = wxgui::FilenameTools::getFilenameAddTag(dlg.GetPath(), ObstacleEditCMPT::OBSTACLE_FILE_TAG, "bin");
// 		storeToBinFile(m_editPanel, m_merged, fixed);
// 	}
}

void ObstaclePackage2CMPT::onLoadFromBinFile(wxCommandEvent& event)
{
	wxString filter = wxT("*_") + ObstacleEditCMPT::OBSTACLE_FILE_TAG + wxT(".bin");
	wxFileDialog dlg(this, wxT("导入tile二进制文件"), wxEmptyString, wxEmptyString, filter, wxFD_OPEN);
	if (dlg.ShowModal() == wxID_OK)
	{
		std::ifstream fin(dlg.GetPath().fn_str(), std::ios::in | std::ios::binary);

		size_t size = 0;
		fin.read(reinterpret_cast<char*>(&size), sizeof(size_t));
		for (size_t i = 0; i < size; ++i)
		{
			int id;
			fin.read(reinterpret_cast<char*>(&id), sizeof(int));

			f2Vec2 pos;
			fin.read(reinterpret_cast<char*>(&pos.x), sizeof(float));
			fin.read(reinterpret_cast<char*>(&pos.y), sizeof(float));

			wxgui::ISymbol* symbol = wxgui::SymbolMgr::Instance()->getSymbol(m_merged.m_data[id].filepath);
			wxgui::ISprite* sprite = wxgui::SpriteFactory::create(symbol);
			sprite->loadBodyFromFile();

			float angle;
			fin.read(reinterpret_cast<char*>(&angle), sizeof(float));

			float scale;
			fin.read(reinterpret_cast<char*>(&scale), sizeof(float));

			unsigned int type;
			fin.read(reinterpret_cast<char*>(&type), sizeof(unsigned int));
			const bool xMirror = type & SPRITE_X_MIRROR,
				yMirror = type & SPRITE_Y_MIRROR;

			sprite->setTransform(pos, angle);
			sprite->setScale(scale);
			sprite->setMirror(xMirror, yMirror);

			m_editPanel->insertSprite(sprite);
		}

		fin.close();

		m_editPanel->Refresh();
	}
}

void ObstaclePackage2CMPT::onLoadMergedFile(wxCommandEvent& event)
{
	wxString filter = "*_" + AUTOMATIC_MERGE_TASK_TAG + ".txt";
	wxFileDialog dlg(this, wxT("选择合图文件"), wxEmptyString, wxEmptyString, filter, wxFD_OPEN);
	if (dlg.ShowModal() == wxID_OK)
	{
		m_merged.resolve(dlg.GetPath());
	}
}

void ObstaclePackage2CMPT::storeToBinFile(StagePanel* editPanel,
										  const deditor::automatic_merge::FileAdapter& merged,
										  const std::vector<wxString>& obstacleFiles,
										  const wxString& filepath)
{
	std::vector<wxgui::ISprite*> sprites = editPanel->getAllPhysics();
	std::sort(sprites.begin(), sprites.end(), SpriteCmp());

	std::ofstream fout(filepath.fn_str(), std::ios::out | std::ios::binary);

	size_t size = sprites.size();
	fout.write(reinterpret_cast<const char*>(&size), sizeof(size_t));
	for (size_t i = 0; i < size; ++i)
	{
		wxgui::ISprite* sprite = sprites[i];

		BreakableSprite* breakable = dynamic_cast<BreakableSprite*>(sprites[i]);
		wxString filepath = breakable ? breakable->getFilepath() : sprite->getSymbol().getFilepath();

		if (wxgui::FileNameParser::isType(filepath, wxgui::FileNameParser::e_image))
		{
			int id = -1;
			for (size_t j = 0, m = merged.m_data.size(); j < m; ++j)
			{
				if (merged.m_data[j].filepath == filepath)
				{
					id = j;
					break;
				}
			}
			assert(id != -1);
			fout.write(reinterpret_cast<const char*>(&id), sizeof(int));
		}
		else 
		{
			int id = -1;
			for (size_t j = 0, m = obstacleFiles.size(); j < m; ++j)
			{
				if (obstacleFiles[j] == filepath)
				{
					id = j;
					break;
				}
			}
			assert(id != -1);
			id += merged.m_data.size();
			fout.write(reinterpret_cast<const char*>(&id), sizeof(int));
		}

		const f2Vec2& pos = sprite->getPosition();
		fout.write(reinterpret_cast<const char*>(&pos.x), sizeof(float));
		fout.write(reinterpret_cast<const char*>(&pos.y), sizeof(float));

		float angle = sprite->getAngle();
		fout.write(reinterpret_cast<const char*>(&angle), sizeof(float));

		float scale = sprite->getScale();
		fout.write(reinterpret_cast<const char*>(&scale), sizeof(float));

		bool xMirror, yMirror;
		sprite->getMirror(xMirror, yMirror);
		unsigned int type = 0;
		if (xMirror) 
			type |= SPRITE_X_MIRROR;
		if (yMirror) 
			type |= SPRITE_Y_MIRROR;		
		fout.write(reinterpret_cast<const char*>(&type), sizeof(unsigned int));
	}

	fout.close();
}