#ifndef _WX_GUI_LIST_ITEM_H_
#define _WX_GUI_LIST_ITEM_H_

#include "dataset/Bitmap.h"

namespace wxgui
{
	class ListItem : public IObject
	{
	public:
		ListItem() {
			m_bitmap = NULL;
		}
		virtual ~ListItem() {}

		const wxString& getName() const { return m_name; }
		void setName(const wxString& name) { m_name = name; }

		const Bitmap* getBitmap() const { return m_bitmap; }

	protected:
		wxString m_name;

		Bitmap* m_bitmap;

	}; // ListItem
}

#endif // _WX_GUI_LIST_ITEM_H_