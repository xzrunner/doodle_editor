#ifndef _WX_GUI_EDIT_POLYLINE_WITH_COPY_NODE_OP_H_
#define _WX_GUI_EDIT_POLYLINE_WITH_COPY_NODE_OP_H_

#include "EditPolylineOP.h"
#include "SelectNodesOP.h"

namespace wxgui
{
	template <typename T>
	class EditPolylineWithCopyNodeOP : public EditPolylineOP<T, SelectNodesOP, DrawPolygonCMPT>
	{
 	public:
 		EditPolylineWithCopyNodeOP(EditPanel* editPanel, MultiShapesImpl* shapesImpl)
 			: EditPolylineOP<T, SelectNodesOP, DrawPolygonCMPT>(editPanel, shapesImpl, NULL)
 		{}
 
 		virtual bool onKeyDown(int keyCode)
 		{
 			if (EditPolylineOP<T, SelectNodesOP, DrawPolygonCMPT>::onKeyDown(keyCode)) 
				return true;
 
 			if (wxGetKeyState(WXK_CONTROL_V))
 				m_selectOP->fetchSelectedNode(m_polyline);
 
 			return false;
 		}

	}; // EditPolylineWithCopyNodeOP
}

#include "EditPolylineWithCopyNodeOP.h"

#endif // _WX_GUI_EDIT_POLYLINE_WITH_COPY_NODE_OP_H_