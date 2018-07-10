#include "LayersMgrCMPT.h"

#include "Edit/SelectShapesOP.h"
#include "Edit/SelectSpritesOP.h"
#include "Widgets/LayersMgrWidget.h"

using namespace wxgui;

LayersMgrCMPT::LayersMgrCMPT(wxWindow* parent, const wxString& name, 
							 EditPanel* editPanel, MultiShapesImpl* shapesImpl)
	: AbstractEditCMPT(parent, name, editPanel)
	, m_layersMgr(NULL)
{
	m_editOP = new SelectShapesOP(editPanel, shapesImpl);

	m_layersMgr = new LayersMgrWidget(this, editPanel);
	m_sizer = new wxBoxSizer(wxVERTICAL);
	m_sizer->Add(m_layersMgr);
}

LayersMgrCMPT::LayersMgrCMPT(wxWindow* parent, const wxString& name, 
							 EditPanel* editPanel, MultiSpritesImpl* spritesImpl,
							 PropertySettingPanel* propertyPanel)
	 : AbstractEditCMPT(parent, name, editPanel)
	 , m_layersMgr(NULL)
{
	m_editOP = new SelectSpritesOP(editPanel, spritesImpl, propertyPanel);

	m_layersMgr = new LayersMgrWidget(this, editPanel);
	m_sizer = new wxBoxSizer(wxVERTICAL);
	m_sizer->Add(m_layersMgr);
}

wxSizer* LayersMgrCMPT::initLayout()
{
	return m_sizer;
}