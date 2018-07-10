#include "TrackChainCMPT.h"
#include "StagePanel.h"

using namespace deditor::hill_climb;

TrackChainCMPT::TrackChainCMPT(wxWindow* parent, const wxString& name,
							   StagePanel* editPanel)
	: AbstractEditCMPT(parent, name, editPanel)
{
// 	addChild(new wxgui::DrawLineCMPT(this, wxT("绘制道路"), editPanel, editPanel));
// 	addChild(new wxgui::EditNodesCMPT(this, wxT("编辑节点"), editPanel, editPanel));
// 	addChild(new wxgui::EditPolylinesCMPT(this, wxT("编辑线"), editPanel, editPanel));

	addChild(new wxgui::DrawPolylineCMPT(this, wxT("道路编辑"), editPanel, editPanel, wxgui::DrawPolylineCMPT::e_CosineCurve));
}

wxSizer* TrackChainCMPT::initLayout()
{
	wxSizer* sizer = new wxBoxSizer(wxVERTICAL);
	{
		wxButton* btn = new wxButton(this, wxID_ANY, wxT("导入物理线..."));
		Connect(btn->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, 
			wxCommandEventHandler(TrackChainCMPT::onLoadPhysicsText));
		sizer->Add(btn);
	}
	sizer->AddSpacer(5);
	{
		wxButton* btn = new wxButton(this, wxID_ANY, wxT("导出物理线..."));
		Connect(btn->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, 
			wxCommandEventHandler(TrackChainCMPT::onStorePhysicsText));
		sizer->Add(btn);
	}
	sizer->AddSpacer(10);
	{
		wxButton* btn = new wxButton(this, wxID_ANY, wxT("导出渲染线..."));
		Connect(btn->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, 
			wxCommandEventHandler(TrackChainCMPT::onStoreRenderText));
		sizer->Add(btn);
	}
	sizer->AddSpacer(20);
	sizer->Add(initChildrenLayout());
	return sizer;
}

void TrackChainCMPT::onLoadPhysicsText(wxCommandEvent& event)
{
	wxString filter = wxT("*_") + wxgui::FileNameParser::getFileTag(wxgui::FileNameParser::e_polyline) + wxT(".txt");
	wxFileDialog dlg(this, wxT("导入道路物理线txt文件"), wxEmptyString, wxEmptyString, filter, wxFD_OPEN);
	if (dlg.ShowModal() == wxID_OK)
	{
		loadFromPhysicsTextFile(dlg.GetPath());
	}
}

void TrackChainCMPT::onStorePhysicsText(wxCommandEvent& event)
{
	wxString filter = wxT("*_") + wxgui::FileNameParser::getFileTag(wxgui::FileNameParser::e_polyline) + wxT(".txt");
	wxFileDialog dlg(this, wxT("导出道路物理线txt文件"), wxEmptyString, wxEmptyString, filter, wxFD_SAVE);
	if (dlg.ShowModal() == wxID_OK)
	{
		wxString fixed = wxgui::FilenameTools::getFilenameAddTag(dlg.GetPath(), wxgui::FileNameParser::getFileTag(wxgui::FileNameParser::e_polyline), "txt");
		storeToPhysicsTextFile(fixed);
	}
}

void TrackChainCMPT::onStoreRenderText(wxCommandEvent& event)
{
	wxString filter = wxT("*_") + wxgui::FileNameParser::getFileTag(wxgui::FileNameParser::e_polyline) + wxT(".txt");
	wxFileDialog dlg(this, wxT("导出道路渲染线txt文件"), wxEmptyString, wxEmptyString, filter, wxFD_SAVE);
	if (dlg.ShowModal() == wxID_OK)
	{
		wxString fixed = wxgui::FilenameTools::getFilenameAddTag(dlg.GetPath(), wxgui::FileNameParser::getFileTag(wxgui::FileNameParser::e_polyline), "txt");
		storeToRenderTextFile(fixed);
	}
}

void TrackChainCMPT::loadFromPhysicsTextFile(const wxString& filepath)
{
	if (wxgui::FileNameParser::getFileType(filepath) != wxgui::FileNameParser::e_polyline)
		return;

	m_editPanel->clear();

	std::vector<wxgui::ChainShape*>* data = new std::vector<wxgui::ChainShape*>;
	wxgui::PolylineFileAdapter fileAdapter(*data);
	fileAdapter.load(filepath.c_str());

	StagePanel* editPanel = static_cast<StagePanel*>(m_editPanel);
	for (size_t i = 0, n = data->size(); i < n; ++i)
	{
		wxgui::CurveShape* curve = new wxgui::CurveShape((*data)[i]->getVertices());
		editPanel->insertShape(curve);
		(*data)[i]->release();
	}
	delete data;

	m_editPanel->Refresh();
}

void TrackChainCMPT::storeToPhysicsTextFile(const wxString& filepath) const
{
	std::vector<wxgui::ChainShape*> shapes;
	static_cast<StagePanel*>(m_editPanel)->traverseShapes(FetchAllVisitor<wxgui::ChainShape>(shapes));

	wxgui::PolylineFileAdapter fileAdapter(shapes);
	fileAdapter.store(filepath.c_str());
}

void TrackChainCMPT::storeToRenderTextFile(const wxString& filepath) const
{
	std::vector<wxgui::CurveShape*> curves;
	static_cast<StagePanel*>(m_editPanel)->traverseShapes(FetchAllVisitor<wxgui::CurveShape>(curves));

	std::ofstream fout(filepath.fn_str());

	fout << '\n';
	fout << curves.size() << '\n';
	for (size_t i = 0, n = curves.size(); i < n; ++i)
	{
		wxgui::CurveShape* curve = curves[i];

		std::vector<f2Vec2> fixed;
		for (size_t i = 0, n = curve->getMidPoints().size(); i < n; ++i)
		{
			if (fixed.empty() || f2Math::getDistance(curve->getMidPoints()[i], fixed.back()) > EPSILON)
				fixed.push_back(curve->getMidPoints()[i]);
		}

		fout << fixed.size() << '\n';
		for (size_t i = 0, n = fixed.size(); i < n; ++i)
			fout << fixed[i] << " ";
		fout << '\n';
		fout << curve->isClosed();
		fout << '\n';
	}

	fout.close();
}