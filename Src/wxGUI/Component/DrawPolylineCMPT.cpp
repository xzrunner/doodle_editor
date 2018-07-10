#include "DrawPolylineCMPT.h"

#include "Edit/DrawPenLineOP.h"
#include "Edit/DrawCosineCurveOP.h"
#include "Edit/SelectShapesOP.h"
#include "Edit/EditPolylineOP.h"

using namespace wxgui;

DrawPolylineCMPT::DrawPolylineCMPT(wxWindow* parent, const wxString& name,
								   EditPanel* editPanel, MultiShapesImpl* shapesImpl,
								   Type type)
	: AbstractEditCMPT(parent, name, editPanel)
{
	switch (type)
	{
	case e_PenLine:
		m_editOP = new EditPolylineOP<DrawPenLineOP, SelectShapesOP, DrawPolylineCMPT>(editPanel, shapesImpl, this);
		break;
	case e_CosineCurve:
		m_editOP = new EditPolylineOP<DrawCosineCurveOP, SelectShapesOP, DrawPolylineCMPT>(editPanel, shapesImpl, this);
		break;
	default:
		m_editOP = new ZoomViewOP(editPanel, true);
	}	
}

int DrawPolylineCMPT::getNodeCaptureDistance() const
{
	return m_tolSlider->GetValue();
}

wxSizer* DrawPolylineCMPT::initLayout()
{
	wxStaticBox* bounding = new wxStaticBox(this, wxID_ANY, wxT("结点捕捉精度"));
	wxBoxSizer* sizer = new wxStaticBoxSizer(bounding, wxVERTICAL);
	m_tolSlider = new wxSlider(this, wxID_ANY, 5, 0, 15, wxDefaultPosition, wxDefaultSize, wxSL_LABELS);
	sizer->Add(m_tolSlider);
	return sizer;
}