#include "EditPolylinesCMPT.h"

#include "Dataset/ChainShape.h"
#include "Edit/EditPolylinesOP.h"
#include "View/MultiShapesImpl.h"
#include "Tools/Math.h"

#include <wx/spinctrl.h>

using namespace wxgui;

EditPolylinesCMPT::EditPolylinesCMPT(wxWindow* parent, const wxString& name,
									 EditPanel* editPanel, MultiShapesImpl* shapesImpl)
	: AbstractEditCMPT(parent, name, editPanel)
	, m_shapesImpl(shapesImpl)
	, m_simplifySpin(NULL)
	, m_btnMerge(NULL)
{
	m_editOP = new EditPolylinesOP(editPanel, shapesImpl, this);
}

void EditPolylinesCMPT::updateControlValue()
{
	bool valid;
	m_shapesImpl->getShapeSelection()->traverse(CountVerifyVisitor(valid, 2));
	m_btnMerge->Enable(valid);
}

float EditPolylinesCMPT::getSimplifyThreshold() const 
{
	return m_simplifySpin->GetValue() * 0.1f;
}

wxSizer* EditPolylinesCMPT::initLayout()
{
	wxSizer* sizer = new wxBoxSizer(wxVERTICAL);

	sizer->Add(initSimplifyPanel());
	sizer->AddSpacer(20);
	sizer->Add(initEditPanel());

	return sizer;
}

wxSizer* EditPolylinesCMPT::initSimplifyPanel()
{
	wxStaticBox* bounding = new wxStaticBox(this, wxID_ANY, wxT("����"));
	wxBoxSizer* sizer = new wxStaticBoxSizer(bounding, wxVERTICAL);

	m_simplifySpin = new wxSpinCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, 
		wxSize(70, -1), wxSP_ARROW_KEYS, 0, 1000, 30);
	Connect(m_simplifySpin->GetId(), wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler(EditPolylinesCMPT::onSimplifyThresholdChanged));
	sizer->Add(m_simplifySpin);

	wxButton* btnOK = new wxButton(this, wxID_ANY, wxT("ȷ��"), wxDefaultPosition, wxSize(70, -1));
	Connect(btnOK->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(EditPolylinesCMPT::onUpdateFromSimplified));
	sizer->Add(btnOK);

	return sizer;
}

wxSizer* EditPolylinesCMPT::initSmoothPanel()
{
	wxStaticBox* bounding = new wxStaticBox(this, wxID_ANY, wxT("ƽ��"));
	wxBoxSizer* sizer = new wxStaticBoxSizer(bounding, wxVERTICAL);

	return sizer;
}

wxSizer* EditPolylinesCMPT::initEditPanel()
{
	wxStaticBox* bounding = new wxStaticBox(this, wxID_ANY, wxT(""));
	wxBoxSizer* sizer = new wxStaticBoxSizer(bounding, wxVERTICAL);
	{
		m_btnMerge = new wxButton(this, wxID_ANY, wxT("�ϲ�"));
		m_btnMerge->Enable(false);
		Connect(m_btnMerge->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(EditPolylinesCMPT::onMergeTwoChain));
		sizer->Add(m_btnMerge);
	}
	sizer->AddSpacer(10);
	{
		wxButton* btn = new wxButton(this, wxID_ANY, wxT("ˮƽƫ�Ƶ�(x=0)"));
		Connect(btn->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(EditPolylinesCMPT::onTranslate));
		sizer->Add(btn);
	}
	return sizer;
}

void EditPolylinesCMPT::onSimplifyThresholdChanged(wxSpinEvent& event)
{
	static_cast<EditPolylinesOP*>(m_editOP)->simplify();
}

void EditPolylinesCMPT::onUpdateFromSimplified(wxCommandEvent& event)
{
	static_cast<EditPolylinesOP*>(m_editOP)->updateFromSimplified();
}

void EditPolylinesCMPT::onMergeTwoChain(wxCommandEvent& event)
{
	std::vector<IShape*> shapes;
	m_shapesImpl->getShapeSelection()->traverse(FetchAllVisitor<IShape>(shapes));
	if (shapes.size() == 2)
	{
		ChainShape *chain0 = static_cast<ChainShape*>(shapes[0]),
			*chain1 = static_cast<ChainShape*>(shapes[1]);

		std::vector<f2Vec2> merged;
		Math::mergeTwoChains(*chain0, *chain1, merged);

		chain0->setVertices(merged);
		chain0->refresh();
		m_shapesImpl->removeShape(chain1);

		m_shapesImpl->getShapeSelection()->clear();

		m_btnMerge->Enable(false);

		m_editPanel->Refresh();
	}
}

void EditPolylinesCMPT::onTranslate(wxCommandEvent& event)
{
	std::vector<IShape*> shapes;
	m_shapesImpl->getShapeSelection()->traverse(FetchAllVisitor<IShape>(shapes));

	float leftmost = FLOAT_MAX;
	std::vector<ChainShape*> chains;
	for (size_t i = 0, n = shapes.size(); i < n; ++i)
	{
		ChainShape* chain = dynamic_cast<ChainShape*>(shapes[i]);
		if (chain) 
		{
			chains.push_back(chain);
			if (chain->getAABB().xMin < leftmost)
				leftmost = chain->getAABB().xMin;
		}
	}

	const f2Vec2 offset(-leftmost, 0.0f);
	for (size_t i = 0, n = chains.size(); i < n; ++i)
	{
		std::vector<f2Vec2> vertices = chains[i]->getVertices();
		for (size_t j = 0, m = vertices.size(); j < m; ++j)
			vertices[j] += offset;
		chains[i]->setVertices(vertices);
	}

	m_editPanel->Refresh();
}