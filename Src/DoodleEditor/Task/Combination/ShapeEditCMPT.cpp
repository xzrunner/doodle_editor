#include "ShapeEditCMPT.h"
#include "StagePanel.h"
#include "ShapeEditOP.h"

using namespace deditor::combination;

ShapeEditCMPT::ShapeEditCMPT(wxWindow* parent, const wxString& name,
							 StagePanel* editPanel)
	: wxgui::DrawPolylineCMPT(parent, name, editPanel, editPanel, DrawPolylineCMPT::e_PenLine)
	, m_editPanel(editPanel)
//	, m_extractCheck(NULL)
{
	if (m_editOP) delete m_editOP;
	m_editOP = new ShapeEditOP(editPanel, this);

//	m_pixelsData = new wxgui::RawPixels;
}

wxSizer* ShapeEditCMPT::initLayout()
{
	wxBoxSizer* topSizer = new wxBoxSizer(wxVERTICAL);
	topSizer->Add(DrawPolylineCMPT::initLayout());
// 	topSizer->AddSpacer(10);
// 	{
// 		m_extractCheck = new wxCheckBox(this, wxID_ANY, wxT("±ß½çÌáÈ¡"));
// 		m_extractCheck->SetValue(true);
// 		topSizer->Add(m_extractCheck);
// 	}
	return topSizer;
}