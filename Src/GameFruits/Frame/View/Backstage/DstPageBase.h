#ifndef _GAME_FRUITS_VIEW_BACKSTAGE_DST_PAGE_BASE_H_
#define _GAME_FRUITS_VIEW_BACKSTAGE_DST_PAGE_BASE_H_
#include <wx/wx.h>
#include <wx/splitter.h>
#include <wx/statline.h>

namespace GAME_FRUITS
{
	namespace VIEW
	{
		namespace BACKSTAGE
		{
			class DstPageBase : public wxSplitterWindow
			{
			public:
				DstPageBase(wxWindow* parent);

			protected:
				void buildPropertyTitle();
				void buildRegularTitle();

			protected:
				wxScrolledWindow* m_propertyPage;
				wxScrolledWindow* m_regularPage;

			}; // DstPageBase

			inline DstPageBase::DstPageBase(wxWindow* parent)
				: wxSplitterWindow(parent)
			{
				m_propertyPage = new wxScrolledWindow(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxVSCROLL);
				m_regularPage = new wxScrolledWindow(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxVSCROLL);

				//			// no use
				// 			m_propertyPage->EnableScrolling(false, true);
				// 			m_regularPage->EnableScrolling(false, true);
				// 
				// 			m_propertyPage->ShowScrollbars(wxSHOW_SB_NEVER, wxSHOW_SB_ALWAYS);
				// 			m_regularPage->ShowScrollbars(wxSHOW_SB_NEVER, wxSHOW_SB_ALWAYS);

				buildPropertyTitle();
				buildRegularTitle();

				m_propertyPage->SetBackgroundColour(wxColour("#dfdfdf"));
				m_regularPage->SetBackgroundColour(wxColour("#dfdfdf"));

				SetSashGravity(0.2f);
				SplitVertically(m_propertyPage, m_regularPage);
			}

			inline void DstPageBase::buildPropertyTitle()
			{
				wxBoxSizer* topSizer = new wxBoxSizer(wxVERTICAL);
				wxStaticText* text = new wxStaticText(m_propertyPage, wxID_ANY, wxT("Property"));
				topSizer->Add(text, 0, wxALIGN_CENTER_HORIZONTAL);
				topSizer->Add(new wxStaticLine(m_propertyPage), 0, wxEXPAND);
				topSizer->AddSpacer(20);
				m_propertyPage->SetSizer(topSizer);
			}

			inline void DstPageBase::buildRegularTitle()
			{
				wxBoxSizer* topSizer = new wxBoxSizer(wxVERTICAL);
				wxStaticText* text = new wxStaticText(m_regularPage, wxID_ANY, wxT("Regular"));
				topSizer->Add(text, 0, wxALIGN_CENTER_HORIZONTAL);
				topSizer->Add(new wxStaticLine(m_regularPage), 0, wxEXPAND);
				topSizer->AddSpacer(20);
				m_regularPage->SetSizer(topSizer);
			}
		}
	}
}

#endif // _GAME_FRUITS_VIEW_BACKSTAGE_DST_PAGE_BASE_H_
