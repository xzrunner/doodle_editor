#ifndef _DEDITOR_MANUAL_COMPOSE_FILE_ADAPTER_H_
#define _DEDITOR_MANUAL_COMPOSE_FILE_ADAPTER_H_

//#define JUNYONG_FORMAT

#include <wxGUI/wxGUI.h>

namespace deditor
{
	class ManualComposeFileAdapter : public wxgui::IFileAdapter
	{
	public:
		virtual void load(const char* filename);

	public:
		struct Item
		{
			wxString filename;
			f2Vec2 pos;
			float angle;
		}; // Item

	public:
		wxString m_bgFilename;
		std::vector<Item> m_items;

	}; // ManualComposeFileAdapter
}

#endif // _DEDITOR_MANUAL_COMPOSE_FILE_ADAPTER_H_