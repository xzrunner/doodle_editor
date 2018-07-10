#ifndef _FEDITOR_NODE_CAPTURE_CMPT_H_
#define _FEDITOR_NODE_CAPTURE_CMPT_H_
#include "AbstractCmpt.h"
#include "../Utility.h"
#include "../../Dataset/ChainShape.h"
#include "../../Dataset/PointShape.h"
#include "../../Dataset/ChainShapeAddr.h"

class GLUI_Spinner;

namespace FEDITOR
{
 	class LayersMgr;

	class NodeCaptureCmpt : public AbstractCmpt
	{
	public:
		NodeCaptureCmpt(LayersMgr& layers, CmptMgr& cmptMgr, float scale = 1.0f);

		virtual void createUIControls(GLUI_Node* parent, ShortcutKeyListener* shortcutLsn);
		virtual void handleUIEvent();

		bool captureByPos(const f2Vec2& pos);

		const ChainShapeAddr& getCapturedAddr() const;

		float getTolerance() const;

		void refreshPos();

		void clear();

	private:
		void createCaptureLayer();

		bool isOpen() const;

		bool captureByPos(const f2Vec2& pos, bool preferPrevious);
		bool captureByPos(const f2Vec2& pos, Layer* layer, bool preferPrevious);
		bool captureByPos(const f2Vec2& pos, Sprite* sprite, bool preferPrevious);
		bool captureByPos(const f2Vec2& pos, Shape* shape, bool preferPrevious);

	private:
		class UICtrls
		{
		public:
			enum
			{
				e_SetState
			};

			UICtrls();

			void createUIControls(GLUI_Node* parent);

			void onEvent(Event event); 

		private:
			void smallLayoutUI(GLUI_Node* parent);
			void largeLayoutUI(GLUI_Node* parent);

			void setState();

			static void callback(int id);

		public:
			int m_captureOpen;
			float m_tolerance;

			GLUI_Spinner* m_tolUI;

			static std::queue<Event> m_eventList;

		}; // UICtrls

	private:
		float m_scale;

		LayersMgr& m_layers;

		ChainShapeAddr m_src;
		PointShape* m_dst;

		UICtrls m_uiCtrls;
		
	}; // NodeCaptureCmpt

	inline float NodeCaptureCmpt::getTolerance() const
	{
		return m_uiCtrls.m_tolerance * m_scale;
	}

	inline void NodeCaptureCmpt::refreshPos()
	{
		if (m_dst && m_src.isValid())
			m_dst->m_pos = m_src.shape->m_vertices[m_src.iPos];
	}

	inline void NodeCaptureCmpt::clear()
	{
		m_src.setInvalid();
		m_dst->m_pos.x = m_dst->m_pos.y = FLOAT_MAX;
	}

	inline bool NodeCaptureCmpt::isOpen() const
	{
		return m_uiCtrls.m_captureOpen == 1;
	}
}

#endif // _FEDITOR_NODE_CAPTURE_CMPT_H_