#include "BaseTask.h"

#include <wx/splitter.h>

using namespace deditor;

BaseTask::BaseTask(wxFrame* parent)
	: m_root(NULL)
	, m_parent(parent)
	, m_stageView(NULL)
{
}

BaseTask::~BaseTask()
{
	wxgui::SymbolMgr::Instance()->clear();
	wxgui::BitmapMgr::Instance()->clear();
	delete m_root;

	m_parent->SetTitle("DoodleEditor");
}

wxgui::GLCanvas* BaseTask::getCanvas() const
{
	if (!m_stageView) return NULL;

	wxgui::EditPanel* editPanel = dynamic_cast<wxgui::EditPanel*>(m_stageView);
	if (editPanel) return editPanel->getCanvas();
	else return NULL;
}

void BaseTask::initLayout()
{
	wxSplitterWindow* rightVerticalSplitter = new wxSplitterWindow(m_parent);
	wxSplitterWindow* leftVerticalSplitter = new wxSplitterWindow(rightVerticalSplitter);
	wxSplitterWindow* leftHorizontalSplitter = new wxSplitterWindow(leftVerticalSplitter);

	wxWindow *library, *property, *stage, *toolbar;
	initWindows(leftHorizontalSplitter, leftVerticalSplitter, rightVerticalSplitter,
		library, property, stage, toolbar);

	assert(stage);
	m_stageView = stage;

	if (library || property)
	{
		if (library && property)
		{
			leftHorizontalSplitter->SetSashGravity(0.8f);
			leftHorizontalSplitter->SplitHorizontally(library, property);
		}
		leftVerticalSplitter->SetSashGravity(0.1f);
		leftVerticalSplitter->SplitVertically(leftHorizontalSplitter, stage);
	}

	if (toolbar)
	{
		rightVerticalSplitter->SetSashGravity(0.95f);
		rightVerticalSplitter->SplitVertically(leftVerticalSplitter, toolbar);
	}

	m_root = rightVerticalSplitter;

	wxSize size = m_parent->GetSize();
	size.SetWidth(size.GetWidth() + 1);
	m_parent->SetSize(size);




	////////////////////////////////////////////////////////////////////////////

 //	wxSplitterWindow* rSplitter = new wxSplitterWindow(m_parent);
 //	wxSplitterWindow* lSplitter = new wxSplitterWindow(rSplitter);
 //
	//wxWindow *left, *middle, *right;
	//initWindows(lSplitter, rSplitter, &left, &middle, &right);
	//m_stageView = middle;

	//if (left)
	//{
	//	lSplitter->SetSashGravity(0.1f);
	//	lSplitter->SplitVertically(left, middle);
	//}

	//if (right)
	//{
	//	rSplitter->SetSashGravity(0.95f);
	//	rSplitter->SplitVertically(lSplitter, right);
	//}

 //	m_root = rSplitter;
 //
	//////////////////////////////////////////////////////////////////////////////
	////wxPropertyGrid *pg = new wxPropertyGrid(
	////	middle, 
	////	-1,
	////	wxDefaultPosition,
	////	wxDefaultSize,
	////	wxPG_SPLITTER_AUTO_CENTER | wxPG_BOLD_MODIFIED
	////	);

	////middle->GetSizer()->Add(pg);

	////pg->Append( new wxStringProperty("String Property", wxPG_LABEL) );
	////pg->Append( new wxIntProperty("Int Property", wxPG_LABEL) );
	////pg->Append( new wxBoolProperty("Bool Property", wxPG_LABEL) );
	//////////////////////////////////////////////////////////////////////////////

 //  	wxSize size = m_parent->GetSize();
 //  	size.SetWidth(size.GetWidth() + 1);
 //  	m_parent->SetSize(size);


}