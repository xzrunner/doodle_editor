#ifndef _DEDITOR_AUTOMATIC_MERGE_BASE_STRATEGY_H_
#define _DEDITOR_AUTOMATIC_MERGE_BASE_STRATEGY_H_

#include <wxGUI/wxGUI.h>

namespace deditor
{
	namespace automatic_merge
	{
		class BaseStrategy
		{
		public:
			virtual ~BaseStrategy() {}

			virtual void arrange(const std::vector<wxgui::ImageSprite*>& sprites, int width, int height) = 0;

		protected:
			void sortByArea(std::vector<wxgui::ImageSprite*>& sprites, bool isDescend = true) const;
			void sortByMaxEdge(std::vector<wxgui::ImageSprite*>& sprites, bool isDescend = true) const;
			void sortByTotEdges(std::vector<wxgui::ImageSprite*>& sprites, bool isDescend = true) const;

		protected:
			enum SortStrategy
			{
				e_area,
				e_maxEdge,
				e_totEdges
			};

			class SpriteCmp
			{
			public:
				SpriteCmp(SortStrategy strategy, bool isDescend);

				bool operator() (const wxgui::ImageSprite* s0, const wxgui::ImageSprite* s1) const;

			private:
				bool isAreaLess(const wxgui::ImageSprite* s0, const wxgui::ImageSprite* s1) const;
				bool isEdgeLess(const wxgui::ImageSprite* s0, const wxgui::ImageSprite* s1) const;
				bool isTotEdgesLess(const wxgui::ImageSprite* s0, const wxgui::ImageSprite* s1) const;

			private:
				SortStrategy m_strategy;
				bool m_isDescend;

			}; // SpriteCmp

		}; // BaseStrategy
	}
}

#endif // _DEDITOR_AUTOMATIC_MERGE_BASE_STRATEGY_H_