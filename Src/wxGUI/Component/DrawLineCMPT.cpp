#include "DrawLineCMPT.h"
#include "DrawPolylineCMPT.h"
#include "DrawPencilLineCMPT.h"

using namespace wxgui;

DrawLineCMPT::DrawLineCMPT(wxWindow* parent, const wxString& name,
						   EditPanel* editPanel, MultiShapesImpl* shapesImpl)
	: AbstractEditCMPT(parent, name, editPanel, wxT("����ѡ��"))
{
	addChild(new DrawPolylineCMPT(this, wxT("�ֱ�"), editPanel, shapesImpl, DrawPolylineCMPT::e_PenLine));
	addChild(new DrawPencilLineCMPT(this, wxT("Ǧ��"), editPanel, shapesImpl));
}

wxSizer* DrawLineCMPT::initLayout()
{
	return initChildrenLayout();
}