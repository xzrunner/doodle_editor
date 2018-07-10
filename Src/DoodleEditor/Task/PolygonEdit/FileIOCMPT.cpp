#include "FileIOCMPT.h"
#include "StagePanel.h"
#include "StageCanvas.h"

#include "Frame/defs.h"
#include "Task/MotoX/TileFileAdapter.h"

using namespace deditor::polygon_edit;

FileIOCMPT::FileIOCMPT(wxWindow* parent, const wxString& name,
					   StagePanel* editPanel)
	: AbstractEditCMPT(parent, name, editPanel)
	, m_editPanel(editPanel)
{
	m_editOP = new wxgui::ZoomViewOP(editPanel, true);
}

wxSizer* FileIOCMPT::initLayout()
{
	wxSizer* sizer = new wxBoxSizer(wxVERTICAL);
	{
		wxButton* btn = new wxButton(this, wxID_ANY, wxT("导入背景线..."));
		Connect(btn->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, 
			wxCommandEventHandler(FileIOCMPT::onLoadBackgroundLine));
		sizer->Add(btn);
	}
	sizer->AddSpacer(5);
	{
		wxButton* btn = new wxButton(this, wxID_ANY, wxT("导入边界线..."));
		Connect(btn->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, 
			wxCommandEventHandler(FileIOCMPT::onLoadBorderLine));
		sizer->Add(btn);
	}
	sizer->AddSpacer(5);
	{
		wxButton* btn = new wxButton(this, wxID_ANY, wxT("导入motox..."));
		Connect(btn->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, 
			wxCommandEventHandler(FileIOCMPT::onLoadMotoXFile));
		sizer->Add(btn);
	}
	sizer->AddSpacer(10);
	{
		sizer->Add(new wxStaticText(this, wxID_ANY, wxT("当前polyline：")));
		sizer->Add(m_currPolylineFilenameText = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY));
	}
	return sizer;
}

void FileIOCMPT::onLoadBackgroundLine(wxCommandEvent& event)
{
	wxString filter = wxT("*_") + wxgui::FileNameParser::getFileTag(wxgui::FileNameParser::e_polyline) + wxT(".txt");
	wxFileDialog dlg(this, wxT("导入polyline文件"), wxEmptyString, wxEmptyString, filter, wxFD_OPEN);
	if (dlg.ShowModal() == wxID_OK)
	{
		m_editPanel->loadBackgroundLine(dlg.GetPath());
		m_currPolylineFilenameText->ChangeValue(wxgui::FilenameTools::getFilename(dlg.GetPath()));
	}
}

void FileIOCMPT::onLoadBorderLine(wxCommandEvent& event)
{
	wxString filter = wxT("*_") + wxgui::FileNameParser::getFileTag(wxgui::FileNameParser::e_polyline) + wxT(".txt");
	wxFileDialog dlg(this, wxT("导入polyline文件"), wxEmptyString, wxEmptyString, filter, wxFD_OPEN);
	if (dlg.ShowModal() == wxID_OK)
	{
		m_editPanel->loadBorderLine(dlg.GetPath());
	}
}

void FileIOCMPT::onLoadMotoXFile(wxCommandEvent& event)
{
	wxString filter = wxT("*_") + MOTOX_TASK_TAG + wxT(".txt");
	wxFileDialog dlg(this, wxT("导入motox文件"), wxEmptyString, wxEmptyString, filter, wxFD_OPEN);
	if (dlg.ShowModal() == wxID_OK)
	{
		motox::TileFileAdapter adapter;
		adapter.resolve(dlg.GetPath());

		StageCanvas* canvas = static_cast<StageCanvas*>(m_editPanel->getCanvas());
		for (size_t i = 0, n = canvas->m_tiles.size(); i < n; ++i)
			canvas->m_tiles[i]->release();
		canvas->m_tiles.clear();
		for (size_t i = 0, n = adapter.m_layers.size(); i < n; ++i)
		{
			for (size_t j = 0, m = adapter.m_layers[i]->sprites.size(); j < m; ++j)
			{
				wxgui::ISprite* sprite = adapter.m_layers[i]->sprites[j];
				sprite->retain();
				canvas->m_tiles.push_back(sprite);
			}
		}
		canvas->Refresh();
	}
}