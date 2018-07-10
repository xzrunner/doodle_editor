#ifndef _FEDITOR_ABSTRACT_CONTROL_H_
#define _FEDITOR_ABSTRACT_CONTROL_H_
#include "Utility.h"

namespace FEDITOR
{
	class AbstractControl;
	class AbstractView;
	class AbstractModel;
	class AbstractOp;
	class LayersMgr;
	class CmptMgr;

	typedef AbstractControl* TaskCreateFcn();

	struct TaskEntry
	{
		const char* name;
		TaskCreateFcn* createFcn;
	};

	class AbstractControl
	{
	public:
		AbstractControl();
		virtual ~AbstractControl();

		virtual void onKeyboard(unsigned char key, int x, int y);
		virtual void onKeyboardSpecial(int key, int x, int y);
		virtual void onMouseDrag(int x, int y);
		virtual void onMouseMove(int x, int y);
		virtual void onMouseWheel(int direction, int x, int y);
		void onMouseButton(int button, int state, int x, int y);

		void createUIFrame(int mainWnd);

		void step();

		void reshape(int fw, int fh, int vw, int vh);

		f2Vec2 transPosScrToPoj(int x, int y) const;

		LayersMgr& getLayersMgr();
		CmptMgr& getCmptMgr();

		void setEditOp(AbstractOp* editOp);

		float getScale() const;

		AbstractOp* getEditOp() const;

	protected:
		virtual void onMouseLeftDown(int x, int y);
		virtual void onMouseLeftUp(int x, int y);
		virtual void onMouseRightDown(int x, int y);
		virtual void onMouseRightUp(int x, int y);

		virtual void createEditCmpt() = 0;

		virtual void handleStep() = 0;
		virtual void handleUIEvent() = 0;
		void handleModelEvent();

		virtual void update();
		virtual void display() const;

	protected:
		AbstractView* m_view;
		AbstractModel* m_model;

		AbstractOp* m_editOp;

	}; // AbstractControl
}

#endif // _FEDITOR_ABSTRACT_CONTROL_H_