#ifndef _DEDITOR_BOUNDARY_EXTRACTION_LIBRARY_PANEL_H_
#define _DEDITOR_BOUNDARY_EXTRACTION_LIBRARY_PANEL_H_

//#include <wx/wx.h>
//#include <wx/notebook.h>
//#include <Fruits2D/Fruits2D.h>
#include <wxGUI/wxGUI.h>

namespace deditor
{
	namespace boundary_extraction
	{
		//class StagePanel;
		//class ToolbarPanel;
		//class LibraryImagePage;
		//class LibraryFilePage;

		//class LibraryPanel : public wxPanel, public ISerializable
		//{
		//public:
		//	LibraryPanel(wxWindow* parent, StagePanel* stage, 
		//		ToolbarPanel* toolbar);

		//	//
		//	// ISerializable interface
		//	//
		//	virtual void loadFromTextFile(std::ifstream& fin);
		//	virtual void storeToTextFile(std::ofstream& fout) const;

		//	void clear();

		//private:
		//	void initLayout(StagePanel* stage, ToolbarPanel* toolbar);

		//	void onPageChanged(wxBookCtrlEvent& event);

		//public:
		//	static const wxString SYMBOL_LIST_NAME;
		//	static const wxString ACTOR_LIST_NAME;

		//private:
		//	LibraryImagePage* m_imagePage;
		//	LibraryFilePage* m_filePage;

		//	friend class FileIO;

		//}; // LibraryPanel

		class StagePanel;
		class ToolbarPanel;
		class LibraryImagePage;
		class LibraryFilePage;

		class LibraryPanel : public wxgui::LibraryPanel
		{
		public:
			LibraryPanel(wxWindow* parent, StagePanel* stage, 
				ToolbarPanel* toolbar);

			//
			// ISerializable interface
			//
			virtual void loadFromTextFile(std::ifstream& fin);
			virtual void storeToTextFile(std::ofstream& fout) const;

			virtual void onPageChanged(wxBookCtrlEvent& event);

		private:
			LibraryImagePage* m_imagePage;
			LibraryFilePage* m_filePage;

		}; // LibraryPanel
	}
}

#endif // _DEDITOR_BOUNDARY_EXTRACTION_LIBRARY_PANEL_H_