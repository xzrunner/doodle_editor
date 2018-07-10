#include "PackageCMPT.h"
#include "StagePanel.h"
#include "TrackChainIOCMPT.h"
#include "TilePackageCMPT.h"
#include "ObstaclePackage2CMPT.h"
#include "LibraryBreakableItem.h"
#include "PackageObstacles.h"
#include "PackageMotorbike.h"

#include "Task/PolygonEdit/PackageCMPT.h"
#include "Frame/defs.h"

using namespace deditor::motox;

const wxString PackageCMPT::TRACK_FILTER = wxT("_polyline.txt");
const wxString PackageCMPT::SURFACE_FILTER = wxT("_surface.txt");
const wxString PackageCMPT::TILES_FILTER = wxT("_motox.txt");
const wxString PackageCMPT::OBSTACLE_FILTER = wxT("_obstacle.txt");

const wxString PackageCMPT::SURFACE_MERGED_FILE = wxT("D:\\MyProject\\svn 2\\FruitsEditor\\MotoX\\MotoX\\editor\\发布打包\\ground_surface_automatic.txt");
//const wxString PackageCMPT::SURFACE_MERGED_FILE = wxT("D:\\MyProject\\svn 2\\FruitsEditor\\MotoX\\MotoX\\editor\\发布打包\\ground_surface_automatic_3.txt");
const wxString PackageCMPT::TILES_MERGED_FILE = wxT("D:\\MyProject\\svn 2\\FruitsEditor\\MotoX\\MotoX\\editor\\发布打包\\tiles_automatic.txt");
//const wxString PackageCMPT::TILES_MERGED_FILE = wxT("D:\\MyProject\\svn 2\\FruitsEditor\\MotoX\\MotoX\\editor\\发布打包\\tiles3_automatic.txt");
const wxString PackageCMPT::OBSTACLE_MERGED_FILE = wxT("D:\\MyProject\\svn 2\\FruitsEditor\\MotoX\\MotoX\\editor\\发布打包\\obstacle_automatic.txt");
const wxString PackageCMPT::OBSTACLE_INFO_FILE = wxT("D:\\MyProject\\svn 2\\FruitsEditor\\MotoX\\MotoX\\editor\\发布打包\\obstacle_info.bin");

PackageCMPT::PackageCMPT(wxWindow* parent, const wxString& name, 
						 StagePanel* editPanel)
	: AbstractEditCMPT(parent, name, editPanel)
{
	m_editOP = new wxgui::ZoomViewOP(editPanel, true);
}

wxSizer* PackageCMPT::initLayout()
{
	wxSizer* sizer = new wxBoxSizer(wxVERTICAL);
	{
		wxButton* btn = new wxButton(this, wxID_ANY, wxT("关卡数据..."));
		Connect(btn->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, 
			wxCommandEventHandler(PackageCMPT::onPackageLevels));
		sizer->Add(btn);
	}
	sizer->AddSpacer(10);
	{
		wxButton* btn = new wxButton(this, wxID_ANY, wxT("障碍物..."));
		Connect(btn->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, 
			wxCommandEventHandler(PackageCMPT::onPackageObstacles));
		sizer->Add(btn);
	}
	sizer->AddSpacer(10);
	{
		wxButton* btn = new wxButton(this, wxID_ANY, wxT("摩托车..."));
		Connect(btn->GetId(), wxEVT_COMMAND_BUTTON_CLICKED,
			wxCommandEventHandler(PackageCMPT::onPackageMotorbike));
		sizer->Add(btn);
	}
	sizer->AddSpacer(10);
	{
		wxButton* btn = new wxButton(this, wxID_ANY, wxT("header..."));
		Connect(btn->GetId(), wxEVT_COMMAND_BUTTON_CLICKED,
			wxCommandEventHandler(PackageCMPT::onPackageHeader));
		sizer->Add(btn);
	}
	return sizer;
}

void PackageCMPT::onPackageLevels(wxCommandEvent& event)
{
	wxDirDialog dlg(NULL, "Choose directory", "D:\\MyProject\\svn 2\\FruitsEditor\\MotoX\\MotoX\\editor\\关卡数据",
		wxDD_DEFAULT_STYLE | wxDD_DIR_MUST_EXIST);
	if (dlg.ShowModal() == wxID_OK)
	{
		m_editPanel->clear();

		wxArrayString files;
		DirTraverser traverser(files);

		wxDir dir(dlg.GetPath());
		dir.Traverse(traverser);

		for (size_t i = 0, n = files.size(); i < n; ++i)
		{
			wxString filepath = files[i];
			if (filepath.find(TRACK_FILTER) != wxNOT_FOUND)
				onPackageTrackChains(filepath);
			else if (filepath.find(SURFACE_FILTER) != wxNOT_FOUND)
				onPackageSurface(filepath);
			else if (filepath.find(TILES_FILTER) != wxNOT_FOUND)
				onPackageTiles(filepath);
			else if (filepath.find(OBSTACLE_FILTER) != wxNOT_FOUND)
				onPackageObstacles(filepath);
		}
	}
}

void PackageCMPT::onPackageObstacles(wxCommandEvent& event)
{
	wxDirDialog dlg(NULL, "Choose directory", "D:\\MyProject\\svn 2\\FruitsEditor\\MotoX\\MotoX\\editor",
		wxDD_DEFAULT_STYLE | wxDD_DIR_MUST_EXIST);
	if (dlg.ShowModal() == wxID_OK)
	{
		std::vector<wxString> meshFiles, combineFiles, breakableFiles;
		filterObstacleFiles(dlg.GetPath(), meshFiles, combineFiles, breakableFiles);

		PackageObstacles package(OBSTACLE_MERGED_FILE, meshFiles, 
			combineFiles, breakableFiles);
		package.package(OBSTACLE_INFO_FILE);
	}
}

void PackageCMPT::onPackageMotorbike(wxCommandEvent& event)
{
	wxFileDialog dlg(this, wxT("摩托车模型"), wxEmptyString, wxEmptyString, 
		wxT("*_") + MODELING_TASK_TAG + wxT(".txt"), wxFD_OPEN);
	if (dlg.ShowModal() == wxID_OK)
	{
		PackageMotorbike package;
		package.package(dlg.GetPath());
	}
}

void PackageCMPT::onPackageHeader(wxCommandEvent& event)
{
	wxDirDialog dlg(NULL, "Choose directory", "D:\\MyProject",
		wxDD_DEFAULT_STYLE | wxDD_DIR_MUST_EXIST);
	if (dlg.ShowModal() == wxID_OK)
	{
		wxArrayString files;
		DirTraverser traverser(files);

		wxDir dir(dlg.GetPath());
		dir.Traverse(traverser);

		std::vector<std::string> header;
		header.push_back("/*");
		header.push_back("* Copyright (c) 2012-2013 XZRUNNER http://runnersoft.net");
		header.push_back("*");
		header.push_back("* This software is provided 'as-is', without any express or implied");
		header.push_back("* warranty.  In no event will the authors be held liable for any damages");
		header.push_back("* arising from the use of this software.");
		header.push_back("* Permission is granted to anyone to use this software for any purpose,");
		header.push_back("* including commercial applications, and to alter it and redistribute it");
		header.push_back("* freely, subject to the following restrictions:");
		header.push_back("* 1. The origin of this software must not be misrepresented; you must not");
		header.push_back("* claim that you wrote the original software. If you use this software");
		header.push_back("* in a product, an acknowledgment in the product documentation would be");
		header.push_back("* appreciated but is not required.");
		header.push_back("* 2. Altered source versions must be plainly marked as such, and must not be");
		header.push_back("* misrepresented as being the original software.");
		header.push_back("* 3. This notice may not be removed or altered from any source distribution.");
		header.push_back("*/");
		header.push_back("");

		for (size_t i = 0, n = files.size(); i < n; ++i)
		{
			std::ifstream fin(files[i].fn_str());

			std::vector<std::string> buffer;

			std::string line;
			while (getline(fin, line))
				buffer.push_back(line);

			fin.close();

			std::ofstream fout(files[i].fn_str());
			for (size_t i = 0, n = header.size(); i < n; ++i)
				fout << header[i] << '\n';
			for (size_t i = 0, n = buffer.size(); i < n; ++i)
				fout << buffer[i] << '\n';
		}
	}
}

void PackageCMPT::onPackageTrackChains(const wxString& filepath)
{
	wxString dstPath = createDstFilepath(filepath, "track_chains.bin");
	TrackChainIOCMPT::packageToBin(filepath, dstPath);
}

void PackageCMPT::onPackageSurface(const wxString& filepath)
{
	wxString motoxFile;
	FindMotoXTraverser traverser(motoxFile);

	wxDir dir(wxFileName(filepath).GetPath());
	dir.Traverse(traverser);

	wxString dstPath = createDstFilepath(filepath, "ground_surface.bin");
	polygon_edit::PackageCMPT::packageToBin(filepath, SURFACE_MERGED_FILE, motoxFile, dstPath);
}

void PackageCMPT::onPackageTiles(const wxString& filepath)
{
	wxString dstPath = createDstFilepath(filepath, "tiles_data.bin");
	StagePanel* editPanel = static_cast<StagePanel*>(m_editPanel);
	TilePackageCMPT::packageToBin(editPanel, filepath, TILES_MERGED_FILE, dstPath);
}

void PackageCMPT::onPackageObstacles(const wxString& filepath)
{
	std::vector<wxString> meshFiles, combineFiles, breakableFiles;
	wxString dlgPath = wxT("D:\\MyProject\\svn 2\\FruitsEditor\\MotoX\\MotoX\\editor");
	filterObstacleFiles(dlgPath, meshFiles, combineFiles, breakableFiles);
	std::vector<wxString> obstacleFiles;
	copy(combineFiles.begin(), combineFiles.end(), back_inserter(obstacleFiles));
	copy(breakableFiles.begin(), breakableFiles.end(), back_inserter(obstacleFiles));

	wxString dstPath = createDstFilepath(filepath, "obstacle_data.bin");

	StagePanel* editPanel = static_cast<StagePanel*>(m_editPanel);

	ObstaclePackage2CMPT::packageToBin(editPanel, filepath, OBSTACLE_MERGED_FILE, obstacleFiles, dstPath);
}

void PackageCMPT::filterObstacleFiles(const wxString& dlg,
									  std::vector<wxString>& meshFiles,
									  std::vector<wxString>& combineFiles, 
									  std::vector<wxString>& breakableFiles)
{
	wxArrayString files;
	DirCurrTraverser traverser(files);

	wxDir dir(dlg);
	dir.Traverse(traverser);

	for (size_t i = 0, n = files.size(); i < n; ++i)
	{
		wxString filepath = files[i];
		if (wxgui::FileNameParser::isType(filepath, wxgui::FileNameParser::e_mesh))
			meshFiles.push_back(filepath);
		else if (wxgui::FileNameParser::isType(filepath, wxgui::FileNameParser::e_combination))
			combineFiles.push_back(filepath);
		else if (filepath.find(LibraryBreakableItem::TAG) != wxNOT_FOUND)
			breakableFiles.push_back(filepath);
	}
}

wxString PackageCMPT::createDstFilepath(const wxString& srcPath, const wxString& filename)
{
	wxString srcDir = wxFileName(srcPath).GetPath();

	wxString dstDir0 = srcDir.substr(0, srcDir.find_last_of('\\')) + "\\bin";
	if (!wxFileName::DirExists(dstDir0))
		wxFileName::Mkdir(dstDir0);

	wxString dstDir1 = srcDir;
	dstDir1.insert(dstDir1.find_last_of('\\'), "\\bin");
	if (!wxFileName::DirExists(dstDir1))
		wxFileName::Mkdir(dstDir1);

	return dstDir1 + wxT("\\") + filename;
}