#ifndef _EASY_BUILDER_DESIGNER_PANEL_H_
#define _EASY_BUILDER_DESIGNER_PANEL_H_

#include <wxGUI/wxGUI.h>

namespace ebuilder
{
	class Scene;
	class SceneItem;

	class DesignerPage : public wxgui::EditPanel, public wxgui::MultiSpritesImpl
	{
	public:
		DesignerPage(wxWindow* parent);

		//
		// wxgui::MultiSpritesImpl interface
		//
		virtual void traverseSprites(IVisitor& visitor, 
			wxgui::TraverseType type = wxgui::e_allExisting, bool order = true) const;
		virtual void removeSprite(wxgui::ISprite* sprite);
		virtual void insertSprite(wxgui::ISprite* sprite);
		virtual void clear();

		void setScene(SceneItem* scene);
		Scene* getScene() const;

		void updateCodePage();

	private:
		class Canvas : public wxgui::SpriteStageCanvas
		{
		public:
			Canvas(DesignerPage* panel);

		protected:
			virtual void onDraw();

		private:
			void drawBackground();
			void drawCenter();

		}; // Canvas

		class DragActorTarget : public wxTextDropTarget
		{
		public:
			DragActorTarget(DesignerPage* editPanel);

			virtual bool OnDropText(wxCoord x, wxCoord y, const wxString& data);

		private:
			DesignerPage* m_editPanel;

		}; // DragActorTarget

		class SelectActorOP : public wxgui::SelectSpritesOP
		{
		public:
			SelectActorOP(wxgui::EditPanel* editPanel, 
				wxgui::MultiSpritesImpl* spritesImpl,
				wxgui::PropertySettingPanel* propertyPanel,
				wxgui::AbstractEditCMPT* callback = NULL,
				const f2Colorf& color = f2Colorf(1, 1, 1));

			virtual bool onMouseLeftUp(int x, int y);

			virtual bool clear();

			virtual wxgui::IPropertySetting* 
				createPropertySetting(wxgui::ISprite* sprite) const;

		private:
			void clearBackstage();

		}; // SelectActorOP

		class ArrangeActorOP : public wxgui::ArrangeSpriteOP<SelectActorOP>
		{
		public:
			ArrangeActorOP(DesignerPage* editPanel,
				wxgui::AbstractEditCMPT* callback);
			
		protected:
			virtual void translateSprite(const f2Vec2& delta);
			virtual void rotateSprite(const f2Vec2& dst);
			virtual void scaleSprite(const f2Vec2& currPos);

		private:
			void refreshThumbnail();

		}; // ArrangeActorOP

	private:
		SceneItem* m_scene;

	}; // DesignerPage
}

#endif // _EASY_BUILDER_DESIGNER_PANEL_H_