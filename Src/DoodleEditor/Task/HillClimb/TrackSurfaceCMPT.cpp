#include "TrackSurfaceCMPT.h"
#include "StagePanel.h"
#include "TrackSurfaceData.h"

using namespace deditor::hill_climb;

TrackSurfaceCMPT::TrackSurfaceCMPT(wxWindow* parent, const wxString& name, 
								   StagePanel* editPanel)
	: AbstractEditCMPT(parent, name, editPanel)
{
	m_editOP = new wxgui::ZoomViewOP(editPanel, true);
}

wxSizer* TrackSurfaceCMPT::initLayout()
{
	wxSizer* sizer = new wxBoxSizer(wxVERTICAL);
	{
		wxButton* btn = new wxButton(this, wxID_ANY, wxT("加载纹理..."));
		Connect(btn->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, 
			wxCommandEventHandler(TrackSurfaceCMPT::onLoadTexture));
		sizer->Add(btn);
	}
	sizer->AddSpacer(5);
	{
		m_offsetSlider = new wxSlider(this, wxID_ANY, 0, 0, 100);
		sizer->Add(m_offsetSlider);
	}
	sizer->AddSpacer(10);
	{
		wxButton* btn = new wxButton(this, wxID_ANY, wxT("导出txt..."));
		Connect(btn->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, 
			wxCommandEventHandler(TrackSurfaceCMPT::onStoreText));
		sizer->Add(btn);
	}
	return sizer;
}

void TrackSurfaceCMPT::onLoadTexture(wxCommandEvent& event)
{
	wxFileDialog dlg(this, wxT("选择纹理"), wxEmptyString, wxEmptyString, wxT("*.png;*.jpg"), wxFD_OPEN);
	if (dlg.ShowModal() == wxID_OK)
	{
		wxString filepath = dlg.GetPath();
		
		wxgui::Image* image = wxgui::ImageMgr::Instance()->getItem(filepath);
		createTrackTexture(image);
		m_editPanel->Refresh();
	}
}

void TrackSurfaceCMPT::onStoreText(wxCommandEvent& event)
{
	wxString filter = wxT("*_hillclimb.txt");
	wxFileDialog dlg(this, wxT("导出路面txt文件"), wxEmptyString, wxEmptyString, filter, wxFD_SAVE);
	if (dlg.ShowModal() == wxID_OK)
	{
		wxString fixed = wxgui::FilenameTools::getFilenameAddTag(dlg.GetPath(), wxT("hillclimb"), wxT("txt"));
		storeToTextFile(fixed);
	}
}

void TrackSurfaceCMPT::storeToTextFile(const wxString& filepath) const
{
	std::vector<wxgui::ChainShape*> shapes;
	static_cast<StagePanel*>(m_editPanel)->traverseShapes(FetchAllVisitor<wxgui::ChainShape>(shapes));
	
	std::vector<TrackSurfaceData*> chainsData;
	for (size_t i = 0, n = shapes.size(); i < n; ++i)
	{
		wxgui::ChainShape* chain = shapes[i];
		if (chain->getUserData())
			chainsData.push_back(static_cast<TrackSurfaceData*>(chain->getUserData()));
	}

	std::ofstream fout(filepath.fn_str());

	fout << chainsData.size() << '\n';
	for (size_t i = 0, n = chainsData.size(); i < n; ++i)
	{
		TrackSurfaceData* data = chainsData[i];
		fout << data->vertices.size() << '\n';
		for (size_t j = 0, m = data->vertices.size(); j < m; ++j)
			fout << data->vertices[j] << " ";
		fout << '\n';
		for (size_t j = 0, m = data->texCoords.size(); j < m; ++j)
			fout << data->texCoords[j] << " ";
		fout << '\n';
	}

	fout.close();
}

void TrackSurfaceCMPT::createTrackTexture(wxgui::Image* image)
{
	const float width = image->width(),
		height = image->height();

	std::vector<wxgui::CurveShape*> trackChains;
	static_cast<StagePanel*>(m_editPanel)->traverseShapes(FetchAllVisitor<wxgui::CurveShape>(trackChains));
	for (size_t i = 0, n = trackChains.size(); i < n; ++i)
	{
		wxgui::CurveShape* chain = trackChains[i];

		const std::vector<f2Vec2>& src = chain->getMidPoints();
		std::vector<f2Vec2> dst;
		float texDis = width, currDis = 0;
		dst.push_back(src[0]);
		for (size_t i = 1, n = src.size(); i < n; ++i)
		{
			float dis = f2Math::getDistance(src[i-1], src[i]);
			while (currDis + dis > texDis)
			{
				f2Vec2 insert = dst.back() + (src[i] - src[i-1]) / f2Math::getDistance(src[i-1], src[i]) * (texDis - currDis);
				dst.push_back(insert);
				dis -= (texDis - currDis);
				currDis = texDis;
				texDis += width;
			}
			currDis += dis;
			dst.push_back(src[i]);
		}

		if (chain->getUserData())
		{
			TrackSurfaceData* data = static_cast<TrackSurfaceData*>(chain->getUserData());
			data->image = image;
			createTrackTexture(dst, *data, m_offsetSlider->GetValue() * 0.01f);
		}
		else
		{
			TrackSurfaceData* data = new TrackSurfaceData;
			data->image = image;
			createTrackTexture(dst, *data);
			chain->setUserData(data);
		}
	}
}

void TrackSurfaceCMPT::createTrackTexture(const std::vector<f2Vec2>& ctlpos, TrackSurfaceData& result)
{
	const float width = result.image->width(),
		height = result.image->height();

	result.vertices.clear();
	result.texCoords.clear();
	float xTexCoords = 0;
	for (size_t i = 0, n = ctlpos.size(); i < n; ++i)
	{
		f2Vec2 prev, curr, next;

		if (i > 0) prev = ctlpos[i-1];
		else prev.setInvalid();

		curr = ctlpos[i];

		if (i < ctlpos.size() - 1) next = ctlpos[i+1];
		else next.setInvalid();

		result.vertices.push_back(curr);

		f2Vec2 offset;
		if (!prev.isValid())
		{
			const float dis = f2Math::getDistance(curr, next);
			offset = f2Math::rotateVectorRightAngle((next - curr) * height / dis, true);
		}
		else if (!next.isValid())
		{
			const float dis = f2Math::getDistance(prev, curr);
			offset = f2Math::rotateVectorRightAngle((prev - curr) * height / dis, false); 
		}
		else
		{
			f2Vec2 offsetPrev, offsetNext;
			{
				const float dis = f2Math::getDistance(prev, curr);
				offsetPrev = f2Math::rotateVectorRightAngle((prev - curr) * height / dis, false); 
			}
			{
				const float dis = f2Math::getDistance(curr, next);
				offsetNext = f2Math::rotateVectorRightAngle((next - curr) * height / dis, true);
			}
			offset = (offsetPrev + offsetNext) * 0.5f;
		}
		result.vertices.push_back(curr + offset);

		if (!prev.isValid())
		{
			result.texCoords.push_back(f2Vec2(0.0f, 0.0f));
			result.texCoords.push_back(f2Vec2(0.0f, 1.0f));
		}
		else
		{
			const float dis = f2Math::getDistance(prev, curr);
			xTexCoords += dis;
			if (xTexCoords > width + 0.1f) 
			{
				assert(0);
			}
			else if (fabs(xTexCoords - width) < 0.1f)
			{
				result.texCoords.push_back(f2Vec2(1.0f, 0.0f));
				result.texCoords.push_back(f2Vec2(1.0f, 1.0f));
				xTexCoords = 0;
				
				result.vertices.push_back(curr);
				result.vertices.push_back(curr + offset);
				result.texCoords.push_back(f2Vec2(0.0f, 0.0f));
				result.texCoords.push_back(f2Vec2(0.0f, 1.0f));
			}
			else
			{
				const float texCoords = xTexCoords / width;
				result.texCoords.push_back(f2Vec2(texCoords, 0.0f));
				result.texCoords.push_back(f2Vec2(texCoords, 1.0f));
			}
		}
	}
}

void TrackSurfaceCMPT::createTrackTexture(const std::vector<f2Vec2>& ctlpos, TrackSurfaceData& result, float rOffset)
{
	const float width = result.image->width(),
		height = result.image->height();

	result.vertices.clear();
	result.texCoords.clear();
	float xTexCoords = 0;
	for (size_t i = 0, n = ctlpos.size(); i < n; ++i)
	{
		f2Vec2 prev, curr, next;

		if (i > 0) prev = ctlpos[i-1];
		else prev.setInvalid();

		curr = ctlpos[i];

		if (i < ctlpos.size() - 1) next = ctlpos[i+1];
		else next.setInvalid();

		f2Vec2 offset;
		if (!prev.isValid())
		{
			const float dis = f2Math::getDistance(curr, next);
			offset = f2Math::rotateVectorRightAngle((next - curr) * height / dis, true);
		}
		else if (!next.isValid())
		{
			const float dis = f2Math::getDistance(prev, curr);
			offset = f2Math::rotateVectorRightAngle((prev - curr) * height / dis, false); 
		}
		else
		{
			f2Vec2 offsetPrev, offsetNext;
			{
				const float dis = f2Math::getDistance(prev, curr);
				offsetPrev = f2Math::rotateVectorRightAngle((prev - curr) * height / dis, false); 
			}
			{
				const float dis = f2Math::getDistance(curr, next);
				offsetNext = f2Math::rotateVectorRightAngle((next - curr) * height / dis, true);
			}
			offset = (offsetPrev + offsetNext) * 0.5f;
		}

		result.vertices.push_back(curr - offset * rOffset);
		result.vertices.push_back(curr + offset * (1 - rOffset));

		if (!prev.isValid())
		{
			result.texCoords.push_back(f2Vec2(0.0f, 0.0f));
			result.texCoords.push_back(f2Vec2(0.0f, 1.0f));
		}
		else
		{
			const float dis = f2Math::getDistance(prev, curr);
			xTexCoords += dis;
			if (xTexCoords > width + 0.1f) 
			{
				assert(0);
			}
			else if (fabs(xTexCoords - width) < 0.1f)
			{
				result.texCoords.push_back(f2Vec2(1.0f, 0.0f));
				result.texCoords.push_back(f2Vec2(1.0f, 1.0f));
				xTexCoords = 0;

				result.vertices.push_back(curr - offset * rOffset);
				result.vertices.push_back(curr + offset * (1 - rOffset));
				result.texCoords.push_back(f2Vec2(0.0f, 0.0f));
				result.texCoords.push_back(f2Vec2(0.0f, 1.0f));
			}
			else
			{
				const float texCoords = xTexCoords / width;
				result.texCoords.push_back(f2Vec2(texCoords, 0.0f));
				result.texCoords.push_back(f2Vec2(texCoords, 1.0f));
			}
		}
	}
}
