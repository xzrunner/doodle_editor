#ifndef _DEDITOR_MOTOX_TILE_PACKAGE_CMPT_H_
#define _DEDITOR_MOTOX_TILE_PACKAGE_CMPT_H_

#include "Task/AutomaticMerge/FileAdapter.h"

namespace deditor
{
	namespace motox
	{
		class StagePanel;

		class TilePackageCMPT : public wxgui::AbstractEditCMPT
		{
		public:
			TilePackageCMPT(wxWindow* parent, const wxString& name,
				StagePanel* editPanel);

			static void packageToBin(StagePanel* editPanel, const wxString& src, 
				const wxString& mergeFile, const wxString& dst);

		protected:
			virtual wxSizer* initLayout();

		private:
			void onStoreToBinFile(wxCommandEvent& event);
			void onLoadFromBinFile(wxCommandEvent& event);
			void onLoadMergedFile(wxCommandEvent& event);

		private:
// 			class FetchTilesVisitor : public IVisitor
// 			{
// 			public:
// 				FetchTilesVisitor(std::vector<wxgui::ISprite*>& sprites)
// 					: m_sprites(sprites) {}
// 
// 				virtual void visit(IObject* object, bool& bFetchNext)
// 				{
// 					wxgui::ISprite* sprite = dynamic_cast<wxgui::ISprite*>(object);
// 					if (sprite && sprite->getBody() == NULL)
// 						m_sprites.push_back(sprite);
// 					bFetchNext = true;
// 				}
// 
// 			private:
// 				std::vector<wxgui::ISprite*>& m_sprites;
// 
// 			}; // FetchTilesVisitor

		private:
			StagePanel* m_editPanel;

			automatic_merge::FileAdapter m_merged;

		}; // TilePackageCMPT
	}
}

#endif // _DEDITOR_MOTOX_TILE_PACKAGE_CMPT_H_