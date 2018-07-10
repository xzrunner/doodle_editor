#include "DrawLineCMPT.h"
#include "DrawPolylineCMPT.h"
#include "DrawPencilLineCMPT.h"

using namespace wxgui;

DrawLineCMPT::DrawLineCMPT(wxWindow* parent, const wxString& name,
						   EditPanel* editPanel, MultiShapesImpl* shapesImpl)
	: AbstractEditCMPT(parent, name, editPanel, wxT("¹¤¾ßÑ¡Ôñ"))
{
	addChild(new DrawPolylineCMPT(this, wxT("¸Ö±Ê"), editPanel, shapesImpl, DrawPolylineCMPT::e_PenLine));
	addChild(new DrawPencilLineCMPT(this, wxT("Ç¦±Ê"), editPanel, shapesImpl));
}

wxSizer* DrawLineCMPT::initLayout()
{
	return initChildrenLayout();
}