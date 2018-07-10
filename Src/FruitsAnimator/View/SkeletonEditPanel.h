#ifndef _FRUITS_ANIMATOR_SKELETON_EDIT_PANEL_H_
#define _FRUITS_ANIMATOR_SKELETON_EDIT_PANEL_H_

#include "Dataset/WholeSkeleton.h"

#include <wxGUI/wxGUI.h>

namespace FRUITS_ANIMATOR
{
	class Sprite;
	class SkeletonSymbolList;

	class SkeletonEditPanel : public wxgui::EditPanel, public wxgui::MultiSpritesImpl
	{
	public:
		static const wxString BONE_SYMBOL_LIST_NAME;

	public:
		SkeletonEditPanel(wxWindow* parent, WholeSkeleton* skeleton, 
			SkeletonSymbolList* symbolList, wxTextCtrl* layerTextCtrl);

		//
		// wxgui::MultiSpritesImpl interface
		//
		virtual void traverseSprites(IVisitor& visitor, 
			wxgui::TraverseType type = wxgui::e_allExisting,
			bool order = true) const;
		virtual void removeSprite(f2Sprite* sprite);
		virtual void insertSprite(f2Sprite* sprite) {}
		virtual void clear() {}

		void insertSprite(int symbolIndex, wxCoord x, wxCoord y);

		void setSelectedBoneLayer(int layer);

	private:
 		class DragSymbolTarget : public wxTextDropTarget
 		{
 		public:
 			DragSymbolTarget(SkeletonEditPanel* panel);
 
 			virtual bool OnDropText(wxCoord x, wxCoord y, const wxString& data);
 
 		private:
 			SkeletonEditPanel* m_panel;
 
 		}; // DragTileTarget

	private:
		WholeSkeleton* m_skeleton;
		SkeletonSymbolList* m_symbolList;

	}; // SkeletonEditPanel
}

#endif // _FRUITS_ANIMATOR_SKELETON_EDIT_PANEL_H_