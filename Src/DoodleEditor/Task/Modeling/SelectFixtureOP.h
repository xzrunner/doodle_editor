#ifndef _DEDITOR_MODELING_SELECT_FIXTURE_OP_H_
#define _DEDITOR_MODELING_SELECT_FIXTURE_OP_H_

#include <wxGUI/wxGUI.h>

namespace deditor
{
	namespace modeling
	{
		class StagePanel;
		class FixtureData;

		class SelectFixtureOP : public wxgui::DrawRectangleOP
		{
		public:
			SelectFixtureOP(StagePanel* editPanel, wxgui::PropertySettingPanel* propertyPanel);
			virtual ~SelectFixtureOP();

			virtual bool onMouseLeftDown(int x, int y);
			virtual bool onMouseLeftUp(int x, int y);
			virtual bool onMouseMove(int x, int y);

			virtual bool onDraw() const;
			virtual bool clear();

		private:
			StagePanel* m_stagePanel;

			wxgui::PropertySettingPanel* m_propertyPanel;

			f2Vec2 m_firstPos;

			FixtureData* m_selected;
			FixtureData* m_mouseOn;

		}; // SelectFixtureOP
	}
}

#endif // _DEDITOR_MODELING_SELECT_FIXTURE_OP_H_