#ifndef _DEDITOR_TEXTURE_EDIT_MESH_EDIT_OP_H_
#define _DEDITOR_TEXTURE_EDIT_MESH_EDIT_OP_H_

#include <wxGUI/wxGUI.h>

namespace deditor
{
	namespace texture_edit
	{
		class StagePanel;
		class MeshCMPT;

		class MeshEditOP : public wxgui::EditPolylineOP<
			wxgui::DrawPolygonEdgeOP, 
			wxgui::SelectShapesOP, 
			MeshCMPT>
		{
		public:
			MeshEditOP(StagePanel* editPanel, MeshCMPT* cmpt);

			virtual bool onMouseLeftUp(int x, int y);

			virtual bool onDraw() const;
			virtual bool clear();

		private:
			void fetchAllBoundingPos() const;

			void fixedAllChainShapes();

		private:
			static const float BOUNDING_REGION;

		private:
			mutable std::vector<f2Vec2> m_bounding;

		}; // MeshEditOP
	}
}

#endif // _DEDITOR_TEXTURE_EDIT_MESH_EDIT_OP_H_