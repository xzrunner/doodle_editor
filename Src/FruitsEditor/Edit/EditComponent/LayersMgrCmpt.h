#ifndef _FEDITOR_LAYERS_MGR_CMPT_H_
#define _FEDITOR_LAYERS_MGR_CMPT_H_
#include "AbstractCmpt.h"
#include "../Utility.h"
#include "../../Dataset/LayersMgr.h"

class GLUI_Panel;
class GLUI_RadioGroup;
class GLUI_Rollout;

namespace FEDITOR
{
	class Layer;
	class LayersMgr;
	class AbstractBlackboard;

	class LayersMgrCmpt : public AbstractCmpt
	{
	public:
		enum Type
		{
			e_BackgroundLayer,
			e_TempLayer,
			e_EditedLayer
		};

		enum EventType
		{
			e_ChangeEditableLayer = EVENT_ID_BASE_LAYERS_MGR_CMPT
		};

		LayersMgrCmpt(LayersMgr& layers, CmptMgr& cmptMgr, AbstractBlackboard* bb);
		~LayersMgrCmpt();

		virtual void createUIControls(GLUI_Node* parent, ShortcutKeyListener* shortcutLsn);
		virtual void handleUIEvent();

		Layer* getCertainTypeLayer(Type type) const;

		void addLayer(Layer* layer);

		void reloadLayers();

		void pushEvent(Event event);

	private:
		void createUICtrls(bool onlyLayers, size_t editedLayerIndex);

		void addLayer();
		void delLayer();
		void changeLayerLevel(bool isUp);

		int getEditedIndex() const;
		void setLayersDrawAABB();
		void setLayersDrawShape();

	private:
		struct Wrapper
		{
			Layer* layer;
			std::string name;
			int visible;
			bool disable;

			Wrapper();

		}; // Wrapper

		class Content
		{
		public:
			Content(LayersMgr& layersMgr);

			bool addLayer(Layer* layer);
			bool deleteLayer(int index);
			bool changeLayerLevel(int index, bool isUp);

			Layer* getCertainTypeLayer(Type type, int editedIndex) const;

			int getUppermostEditableLayerIndex() const;
			size_t getTotSize() const { return m_wrapper.size(); }

			void setLayersVisible();
			void setlayersEditable(int editedIndex, bool isDrawAABB, bool isDrawShape);

			const std::vector<Wrapper*>& getWrappers() const { return m_wrapper; }

			void reloadLayers();

		private:
			void reloadLayersFromMgr();

			void addLayerToMgr(Layer* layer);
			void addLayerToWrappers(Layer* layer);

		private:
			size_t m_count;

			LayersMgr& m_layersMgr;
			std::vector<Wrapper*> m_wrapper;

		}; // Content

		// todo ...
	public:
		class UICtrls
		{
		public:
			enum
			{
				e_AddLayer,
				e_DelLayer,

				e_SetLayerEditable,
				e_SetLayerVisible,

				e_UpLayer,
				e_DownLayer,

				e_SetDrawAABB,
				e_SetDrawShape
			};

			UICtrls();

			void setParent(GLUI_Node* parent);

			void createUICtrls();
			void createLayersUICtrls();
			void initLayers(const std::vector<Wrapper*>& wrappers);

			int getEditedIndex(size_t totSize) const { 
				return totSize - m_editedIndex - 1; 
			}
			void setEditedIndex(size_t totSize, int index) { 
				m_editedIndex = totSize - index - 1;
			}

			bool isDrawAABB() const { return m_isDrawAABB == 1; }
			bool isDrawShape() const { return m_isDrawShape == 1; }

		private:
			static const size_t BTN_WIDTH = 10;

			static void callback(int id);

		private:
			void initLayersUICtrls();

			void smallLayoutUI();
			void largeLayoutUI();
			void commonLayoutUI(GLUI_Node* parent);

		private:
 			GLUI_Node* m_parent;

			GLUI_Panel* m_layersPanelWrapper;
			GLUI_Panel* m_layersPanel;

			GLUI_Panel* m_nameList;
			GLUI_RadioGroup* m_editableList;
			GLUI_Panel* m_visibleList;

			int m_editedIndex;

			int m_isDrawAABB, m_isDrawShape;

		public:
			static std::queue<Event> m_eventList;

		}; // UICtrls

	private:
		AbstractBlackboard* m_bb;

		Content* m_content;
		UICtrls* m_uiCtrls;

	}; // LayersMgrCmpt
}

#endif // _FEDITOR_LAYERS_MGR_CMPT_H_