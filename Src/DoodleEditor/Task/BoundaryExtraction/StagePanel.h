#ifndef _DEDITOR_BOUNDARY_EXTRACTION_STAGE_PANEL_H_
#define _DEDITOR_BOUNDARY_EXTRACTION_STAGE_PANEL_H_

#include <wxGUI/wxGUI.h>

namespace deditor
{
	namespace boundary_extraction
	{
		class LibraryItem;

		class StagePanel : public wxgui::EditPanel, public wxgui::MultiShapesImpl
		{
		public:
			StagePanel(wxWindow* parent);

			//
			// wxgui::MultiShapesImpl interface
			//
			virtual void traverseShapes(IVisitor& visitor, 
				wxgui::TraverseType type = wxgui::e_allExisting) const;
			virtual void removeShape(wxgui::IShape* shape);
			virtual void insertShape(wxgui::IShape* shape);
			virtual void clear();

			void onDraw();

			void changeCurrItem(LibraryItem* item);

			void clearItemLines();

		private:
			LibraryItem* m_item;

		}; // StagePanel
	}
}

#endif // _DEDITOR_BOUNDARY_EXTRACTION_STAGE_PANEL_H_