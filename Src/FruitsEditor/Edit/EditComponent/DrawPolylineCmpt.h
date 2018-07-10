#ifndef _FEDITOR_PHYS_TASK_SETTING_CMPT_H_
#define _FEDITOR_PHYS_TASK_SETTING_CMPT_H_
#include "AbstractCmpt.h"
#include "../Utility.h"

namespace FEDITOR
{
	class AbstractControl;
	class Sprite;
	class Layer;
	class NodeCaptureCmpt;

	class DrawPolylineCmpt : public AbstractCmpt
	{
	public:
		DrawPolylineCmpt(AbstractControl* control, Sprite* sprite, Layer* layer);
			// if sprite != NULL add polyline as shape
			// else add as sprite

		virtual void createUIControls(GLUI_Node* parent, ShortcutKeyListener* shortcutLsn);
		virtual void handleUIEvent();

		void setEditedLayer(Layer* edited);

	private:
		enum
		{
			e_Draw,
			e_Edit,
			e_Clear
		};

		static void callback(int id);

	private:
		void smallLayoutUI(GLUI_Node* parent);
		void largeLayoutUI(GLUI_Node* parent);

		void initTmpSprite();
		void swapTmpSprite();

		void clear();

	private:
		AbstractControl* m_control;

		Layer* m_layer;
		Sprite* m_sprite;

		bool m_addToSingleSprite;

		Sprite* m_temp;

		NodeCaptureCmpt* m_capture;

		static std::queue<Event> m_eventList;

	}; // DrawPolylineCmpt

	inline void DrawPolylineCmpt::setEditedLayer(Layer* edited)
	{
		m_layer = edited;
	}
}

#endif // _FEDITOR_PHYS_TASK_SETTING_CMPT_H_