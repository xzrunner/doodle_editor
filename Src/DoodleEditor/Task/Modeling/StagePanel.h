#ifndef _DEDITOR_MODELING_STAGE_PANEL_H_
#define _DEDITOR_MODELING_STAGE_PANEL_H_

#include <wxGUI/wxGUI.h>

namespace deditor
{
	namespace modeling
	{
		class BodyData;
		class JointData;

		class StagePanel : public wxgui::EditPanel, public wxgui::SpritesPanelImpl
		{
		public:
			StagePanel(wxWindow* parent, wxgui::PropertySettingPanel* propertyPanel,
				wxgui::LibraryPanel* libraryPanel);
			virtual ~StagePanel();

			virtual void removeSprite(wxgui::ISprite* sprite);
			virtual void insertSprite(wxgui::ISprite* sprite);
			virtual void clear();

			virtual wxgui::ISprite* querySpriteByPos(const f2Vec2& pos) const;
			virtual void querySpritesByAABB(const f2AABB& aabb, std::vector<wxgui::ISprite*>& result) const;		

			JointData* queryJointByPos(const f2Vec2& pos) const;

			void insertJoint(JointData* joint) {
				m_joints.push_back(joint);
			}
			void removeJoint(JointData* joint);

			void traverseBodies(IVisitor& visitor) const;
			void traverseJoints(IVisitor& visitor) const;

		private:
			void loadCircleBody(const wxString& filepath, BodyData& body) const;
			void loadPolygonBody(const wxString& filepath, BodyData& body) const;

		private:
			class PointQueryVisitor : public IVisitor
			{
			public:
				PointQueryVisitor(const f2Vec2& pos, wxgui::ISprite** pResult);
				virtual void visit(IObject* object, bool& bFetchNext);

			private:
				const f2Vec2& m_pos;
				wxgui::ISprite** m_pResult;

			}; // PointQueryVisitor

			class RectQueryVisitor : public IVisitor
			{
			public:
				RectQueryVisitor(const f2AABB& aabb, std::vector<wxgui::ISprite*>& result);
				virtual void visit(IObject* object, bool& bFetchNext);

			private:
				const f2AABB& m_aabb;
				std::vector<wxgui::ISprite*>& m_result;

			}; // RectQueryVisitor

		private:
			std::vector<BodyData*> m_bodies;
			std::vector<JointData*> m_joints;

		}; // StagePanel
	}
}

#endif // _DEDITOR_MODELING_STAGE_PANEL_H_