#include "PasteSymbolRandomWidget.h"

#include "Dataset/ISymbol.h"
#include "View/LibraryPanel.h"

#include <wx/spinctrl.h>

using namespace wxgui;

PasteSymbolRandomWidget::PasteSymbolRandomWidget(wxWindow* parent, LibraryPanel* libraryPanel)
	: wxPanel(parent)
	, m_libraryPanel(libraryPanel)
{
	initLayout();
}

void PasteSymbolRandomWidget::initLayout()
{
	wxStaticBox* bounding = new wxStaticBox(this, wxID_ANY, wxT("�������"));
	wxBoxSizer* topSizer = new wxStaticBoxSizer(bounding, wxVERTICAL);
	topSizer->AddSpacer(5);
	{
		wxStaticBox* bounding = new wxStaticBox(this, wxID_ANY, wxT("Ԫ������"));
		wxBoxSizer* sizer = new wxStaticBoxSizer(bounding, wxHORIZONTAL);
		sizer->Add(m_symbolFilterCtrl = new wxTextCtrl(this, wxID_ANY, wxEmptyString));
		topSizer->Add(sizer);
	}
	topSizer->AddSpacer(5);
	{
		wxStaticBox* bounding = new wxStaticBox(this, wxID_ANY, wxT("����"));
		wxBoxSizer* sizer = new wxStaticBoxSizer(bounding, wxHORIZONTAL);
		m_scaleMinCtrl = new wxSpinCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(50, -1), wxSP_ARROW_KEYS | wxALIGN_RIGHT, 10, 100, 75);
		sizer->Add(m_scaleMinCtrl);
		sizer->Add(new wxStaticText(this, wxID_ANY, wxT(" - ")));
		m_scaleMaxCtrl = new wxSpinCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(50, -1), wxSP_ARROW_KEYS | wxALIGN_RIGHT, 10, 100, 100);
		sizer->Add(m_scaleMaxCtrl);
		topSizer->Add(sizer);
	}
	topSizer->AddSpacer(5);
	{
		wxStaticBox* bounding = new wxStaticBox(this, wxID_ANY, wxT("�Ƕ�"));
		wxBoxSizer* sizer = new wxStaticBoxSizer(bounding, wxHORIZONTAL);
		m_angleMinCtrl = new wxSpinCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(55, -1), wxSP_ARROW_KEYS | wxALIGN_RIGHT, -180, 180, -45);
		sizer->Add(m_angleMinCtrl);
		sizer->Add(new wxStaticText(this, wxID_ANY, wxT(" - ")));
		m_angleMaxCtrl = new wxSpinCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(55, -1), wxSP_ARROW_KEYS | wxALIGN_RIGHT, -180, 180, 45);
		sizer->Add(m_angleMaxCtrl);
		topSizer->Add(sizer);
	}
	SetSizer(topSizer);
}

void PasteSymbolRandomWidget::getRandomValue(RandomValue& val) const
{
	std::vector<ISymbol*> symbols;
	m_libraryPanel->traverse(FilterSymbolVisitor(m_symbolFilterCtrl->GetValue(), symbols));
	if (symbols.empty())
		val.symbol = NULL;
	else
		val.symbol = symbols[static_cast<int>(symbols.size() * Random::getNum0To1())];

	const float scaleMin = m_scaleMinCtrl->GetValue() * 0.01f,
		scaleMax = m_scaleMaxCtrl->GetValue() * 0.01f;
	val.scale = scaleMin + (scaleMax - scaleMin) * Random::getNum0To1();

	const float angleMin = m_angleMinCtrl->GetValue() * TRANS_DEG_TO_RAD,
		angleMax = m_angleMaxCtrl->GetValue() * TRANS_DEG_TO_RAD;
	val.angle = angleMin + (angleMax - angleMin) * Random::getNum0To1();
}

//////////////////////////////////////////////////////////////////////////
// class PasteSymbolRandomWidget::FilterSymbolVisitor
//////////////////////////////////////////////////////////////////////////

PasteSymbolRandomWidget::FilterSymbolVisitor::
FilterSymbolVisitor(const wxString& filter, std::vector<ISymbol*>& result)
	: m_filter(filter)
	, m_result(result)
{
}

void PasteSymbolRandomWidget::FilterSymbolVisitor::
visit(IObject* object, bool& bFetchNext)
{
	ISymbol* symbol = static_cast<ISymbol*>(object);
	if (!m_filter.empty() && symbol->getFilepath().find(m_filter) != wxNOT_FOUND)
		m_result.push_back(symbol);
	bFetchNext = true;
}
