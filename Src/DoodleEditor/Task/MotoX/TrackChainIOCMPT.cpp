#include "TrackChainIOCMPT.h"
#include "StagePanel.h"
#include "ShapesPanelImpl.h"
#include "TrackChain.h"

using namespace deditor::motox;

const wxString TrackChainIOCMPT::TRACK_FILE_TAG = wxT("trackchains");

TrackChainIOCMPT::TrackChainIOCMPT(wxWindow* parent, const wxString& name,
								   StagePanel* editPanel)
	: AbstractEditCMPT(parent, name, editPanel)
	, m_shapesImpl(editPanel)
{
	m_editOP = new wxgui::ZoomViewOP(editPanel, true);
}

void TrackChainIOCMPT::packageToBin(const wxString& src, 
									const wxString& dst)
{
	if (wxgui::FileNameParser::getFileType(src) != wxgui::FileNameParser::e_polyline)
		return;

	std::vector<wxgui::ChainShape*>* data = new std::vector<wxgui::ChainShape*>;
	wxgui::PolylineFileAdapter fileAdapter(*data);
	fileAdapter.load(src.c_str());

	std::vector<std::vector<f2Vec2> > vertices;
	for (size_t i = 0, n = data->size(); i < n; ++i)
	{
		vertices.push_back((*data)[i]->getVertices());
		(*data)[i]->release();
	}
	storeToBinFile(vertices, dst);
}

wxSizer* TrackChainIOCMPT::initLayout()
{
	wxSizer* sizer = new wxBoxSizer(wxVERTICAL);
	{
		wxButton* btn = new wxButton(this, wxID_ANY, wxT("导入txt..."));
		Connect(btn->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, 
			wxCommandEventHandler(TrackChainIOCMPT::onLoadText));
		sizer->Add(btn);
	}
	{
		wxButton* btn = new wxButton(this, wxID_ANY, wxT("导出txt..."));
		Connect(btn->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, 
			wxCommandEventHandler(TrackChainIOCMPT::onStoreText));
		sizer->Add(btn);
	}
	sizer->AddSpacer(10);
	{
		wxButton* btn = new wxButton(this, wxID_ANY, wxT("导入bin..."));
		Connect(btn->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, 
			wxCommandEventHandler(TrackChainIOCMPT::onLoadBin));
		sizer->Add(btn);
	}
	{
		wxButton* btn = new wxButton(this, wxID_ANY, wxT("导出bin..."));
		Connect(btn->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, 
			wxCommandEventHandler(TrackChainIOCMPT::onStoreBin));
		sizer->Add(btn);
	}
	sizer->AddSpacer(20);
	{
		sizer->Add(new wxStaticText(this, wxID_ANY, wxT("当前文件：")));
		sizer->Add(m_currFilenameCtrl = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY));
	}
	return sizer;
}

void TrackChainIOCMPT::onLoadText(wxCommandEvent& event)
{
	wxString filter = wxT("*_") + wxgui::FileNameParser::getFileTag(wxgui::FileNameParser::e_polyline) + wxT(".txt");
	wxFileDialog dlg(this, wxT("导入道路txt文件"), wxEmptyString, wxEmptyString, filter, wxFD_OPEN);
	if (dlg.ShowModal() == wxID_OK)
	{
		loadFromTextFile(dlg.GetPath());
		m_currFilenameCtrl->ChangeValue(wxgui::FilenameTools::getFilename(dlg.GetPath()));
	}
}

void TrackChainIOCMPT::onStoreText(wxCommandEvent& event)
{
	wxString filter = wxT("*_") + wxgui::FileNameParser::getFileTag(wxgui::FileNameParser::e_polyline) + wxT(".txt");
	wxFileDialog dlg(this, wxT("导出道路txt文件"), wxEmptyString, wxEmptyString, filter, wxFD_SAVE);
	if (dlg.ShowModal() == wxID_OK)
	{
		wxString fixed = wxgui::FilenameTools::getFilenameAddTag(dlg.GetPath(), wxgui::FileNameParser::getFileTag(wxgui::FileNameParser::e_polyline), "txt");
		storeToTextFile(fixed);
		m_currFilenameCtrl->ChangeValue(wxgui::FilenameTools::getFilename(fixed));
	}
}

void TrackChainIOCMPT::onLoadBin(wxCommandEvent& event)
{
	wxString filter = wxT("*_") + TRACK_FILE_TAG + wxT(".bin");
	wxFileDialog dlg(this, wxT("导入道路二进制文件"), wxEmptyString, wxEmptyString, filter, wxFD_OPEN);
	if (dlg.ShowModal() == wxID_OK)
	{
		loadFromBinFile(dlg.GetPath());
	}
}

void TrackChainIOCMPT::onStoreBin(wxCommandEvent& event)
{
	wxString filter = wxT("*_") + TRACK_FILE_TAG + wxT(".bin");
	wxFileDialog dlg(this, wxT("导出道路二进制文件"), wxEmptyString, wxEmptyString, filter, wxFD_SAVE);
	if (dlg.ShowModal() == wxID_OK)
	{
		wxString fixed = wxgui::FilenameTools::getFilenameAddTag(dlg.GetPath(), "trackchains", "bin");
		storeToBinFile(fixed);
	}
}

void TrackChainIOCMPT::loadFromTextFile(const wxString& filepath)
{
	if (wxgui::FileNameParser::getFileType(filepath) != wxgui::FileNameParser::e_polyline)
		return;

	m_shapesImpl->clear();

	std::vector<wxgui::ChainShape*>* data = new std::vector<wxgui::ChainShape*>;
	wxgui::PolylineFileAdapter fileAdapter(*data);
	fileAdapter.load(filepath.c_str());

	for (size_t i = 0, n = data->size(); i < n; ++i)
	{
		TrackChain* chain = new TrackChain(m_shapesImpl->m_world, m_shapesImpl->m_worldReverse, 
			static_cast<wxgui::ChainShape*>((*data)[i])->getVertices());
		m_shapesImpl->m_chains.push_back(chain);
	}

	for_each(data->begin(), data->end(), DeletePointerFunctor<wxgui::ChainShape>());

	m_shapesImpl->m_wnd->Refresh();
}

void TrackChainIOCMPT::storeToTextFile(const wxString& filepath) const
{
	std::vector<wxgui::ChainShape*> shapes;
	shapes.reserve(m_shapesImpl->m_chains.size());
	for (size_t i = 0, n = m_shapesImpl->m_chains.size(); i < n; ++i)
		shapes.push_back(m_shapesImpl->m_chains[i]);

	wxgui::PolylineFileAdapter fileAdapter(shapes);
	fileAdapter.store(filepath.c_str());
}

void TrackChainIOCMPT::loadFromBinFile(const wxString& filepath)
{
	m_shapesImpl->clear();

	std::ifstream fin(filepath.fn_str(), std::ios::in | std::ios::binary);

	size_t chainSize = 0;
	fin.read(reinterpret_cast<char*>(&chainSize), sizeof(size_t));
	for (size_t i = 0; i < chainSize; ++i)
	{
		size_t posSize = 0;
		fin.read(reinterpret_cast<char*>(&posSize), sizeof(size_t));
		std::vector<f2Vec2> vertices;
		vertices.reserve(posSize);
		for (size_t j = 0; j < posSize; ++j)
		{
			int x, y;
			fin.read(reinterpret_cast<char*>(&x), sizeof(int));
			fin.read(reinterpret_cast<char*>(&y), sizeof(int));
			vertices.push_back(f2Vec2(x, y));
		}
		m_shapesImpl->m_chains.push_back(new TrackChain(m_shapesImpl->m_world, 
			m_shapesImpl->m_worldReverse, vertices));
	}

	fin.close();

	m_shapesImpl->m_wnd->Refresh();
}

void TrackChainIOCMPT::storeToBinFile(const wxString& filepath) const
{
	std::vector<std::vector<f2Vec2> > vertices;
	for (size_t i = 0, n = m_shapesImpl->m_chains.size(); i < n; ++i)
		vertices.push_back(m_shapesImpl->m_chains[i]->getVertices());
	storeToBinFile(vertices, filepath);
}

void TrackChainIOCMPT::storeToBinFile(const std::vector<std::vector<f2Vec2> >& vertices,
									  const wxString& filepath)
{
	std::ofstream fout(filepath.fn_str(), std::ios::out | std::ios::binary);

	size_t chainSize = vertices.size();
	fout.write(reinterpret_cast<const char*>(&chainSize), sizeof(size_t));
	for (size_t i = 0; i < chainSize; ++i)
	{
		const std::vector<f2Vec2>& pos = vertices[i];
		size_t posSize = pos.size();
		fout.write(reinterpret_cast<const char*>(&posSize), sizeof(size_t));
		for (size_t j = 0; j < posSize; ++j)
		{
			int x = (int) (pos[j].x + 0.5f), y = (int) (pos[j].y + 0.5f);
			fout.write(reinterpret_cast<const char*>(&x), sizeof(int));
			fout.write(reinterpret_cast<const char*>(&y), sizeof(int));
		}
	}

	fout.close();
}