#ifndef _FEDITOR_LAYERS_IO_CMPT_H_
#define _FEDITOR_LAYERS_IO_CMPT_H_
#include "AbstractCmpt.h"
#include "../Utility.h"

class GLUI_FileBrowser;

namespace FEDITOR
{
	class LayersMgr;

	class LayersIOCmpt : public AbstractCmpt
	{
	public:
		LayersIOCmpt(const LayersMgr& layers, CmptMgr& cmptMgr, const std::string& filename);

		virtual void createUIControls(GLUI_Node* parent, ShortcutKeyListener* shortcutLsn);
		virtual void handleUIEvent();

	private:
		enum Type
		{
			e_OpenFromFile,
			e_StoreToFile
		};

		static const size_t BTN_WIDTH = 10;

		static void callback(int id);

	private:
		const LayersMgr& m_layers;

		static GLUI_FileBrowser* m_layers_fb;

		static std::queue<Event> m_eventList;

	}; // LayersIOCmpt
}

#endif // _FEDITOR_LAYERS_IO_CMPT_H_