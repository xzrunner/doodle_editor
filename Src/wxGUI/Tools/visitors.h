#ifndef _WX_GUI_VISITORS_H_
#define _WX_GUI_VISITORS_H_

#include <wx/wx.h>

namespace wxgui
{
	template <typename T>
	class GetNameVisitor : public IVisitor
	{
	public:
		GetNameVisitor(std::vector<wxString>& names)
			: m_names(names) {}

		virtual void visit(IObject* object, bool& bFetchNext)
		{
			T* item = dynamic_cast<T*>(object);
			if (item)
				m_names.push_back(item->getName());
			bFetchNext = true;
		}

	private:
		std::vector<wxString>& m_names;

	}; // GetNameVisitor
}

#endif // _WX_GUI_VISITORS_H_