#include <wx/wx.h>

class Toolbars : public wxFrame
{
public:
	Toolbars(const wxString& title);

	void OnQuit(wxCommandEvent& event);

	wxToolBar *toolbar1;
	wxToolBar *toolbar2;

};