#ifndef _WX_GUI_LAYERS_MGR_CMPT_H_
#define _WX_GUI_LAYERS_MGR_CMPT_H_

#include "AbstractEditCMPT.h"

namespace wxgui
{
	class MultiShapesImpl;
	class MultiSpritesImpl;
	class LayersMgrWidget;
	class PropertySettingPanel;

	class LayersMgrCMPT : public AbstractEditCMPT
	{
	public:
		LayersMgrCMPT(wxWindow* parent, const wxString& name,
			EditPanel* editPanel, MultiShapesImpl* shapesImpl);
		LayersMgrCMPT(wxWindow* parent, const wxString& name,
			EditPanel* editPanel, MultiSpritesImpl* spritesImpl,
			PropertySettingPanel* propertyPanel);

		LayersMgrWidget* getLayersMgr() { return m_layersMgr; }

	protected:
		virtual wxSizer* initLayout();

	private:
		LayersMgrWidget* m_layersMgr;

		wxSizer* m_sizer;

	}; // LayersMgrCMPT
}

#endif // _WX_GUI_LAYERS_MGR_CMPT_H_