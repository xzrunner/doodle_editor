#ifndef _DEDITOR_POLYGON_EDIT_STAGE_PANEL_H_
#define _DEDITOR_POLYGON_EDIT_STAGE_PANEL_H_

#include <wxGUI/wxGUI.h>

namespace deditor
{
	namespace polygon_edit
	{
		class StagePanel : public wxgui::EditPanel, public wxgui::MultiShapesImpl
		{
		public:
			StagePanel(wxWindow* parent);
			virtual ~StagePanel();

			//
			// wxgui::MultiShapesImpl interface
			//
			virtual void traverseShapes(IVisitor& visitor, 
				wxgui::TraverseType type = wxgui::e_allExisting) const;
			virtual void removeShape(wxgui::IShape* shape);
			virtual void insertShape(wxgui::IShape* shape);
			virtual void clear();

			void loadBackgroundLine(const wxString& filepath);
			void loadBorderLine(const wxString& filepath);

			void setLayersMgr(wxgui::LayersMgrWidget* layersMgr) { 
				m_layersMgr = layersMgr; 
			}
			wxgui::LayersMgrWidget* getLayersMgr() {
				return m_layersMgr;
			}

			wxColourData& getColorData() { return m_colorData; }
			void setColorData(const wxColourData& colorData) { m_colorData = colorData; }

		private:
			void traverseLayersShape(IVisitor& visitor, const std::vector<wxgui::Layer*>& layers) const;

		private:
			wxgui::LayersMgrWidget* m_layersMgr;

			wxColourData m_colorData;

		}; // StagePanel
	}
}

#endif // _DEDITOR_POLYGON_EDIT_STAGE_PANEL_H_