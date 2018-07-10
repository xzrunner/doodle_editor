#ifndef _DEDITOR_MOTOX_ACTOR_EDIT_PARTS_H_
#define _DEDITOR_MOTOX_ACTOR_EDIT_PARTS_H_

#include "ActorDefs.h"
#include "AEPartsCMPT.h"

#include <Fruits2D/Fruits2D.h>

namespace deditor
{
	namespace motox
	{
		class LibraryActorItem;

		class AEParts
		{
		public:
			AEParts(LibraryActorItem& params);

			void initFromParams();

			void traverse(IVisitor& visitor) const;

			void loadPart(AEPartsCMPT::ID type, 
				wxgui::ISymbol* symbol, const f2Vec2& pos);

			wxgui::ISprite* getPart(int id);

			void clear();

			// part1 is NULL when partID1 = -1
			static void mapCtrlIDToPartIDs(AEPartsCMPT::ID ctrlID, 
				int& partID0, int& partID1);

		private:
			void loadPart(int index, wxgui::ISymbol* symbol, const f2Vec2& pos);

			void setCollisionFilter(size_t part);
			void setCollisionFilter();

 		private:
			static const int TRAVERSE_ORDER[PARTS_COUNT];

 		private:
			LibraryActorItem& m_params;

			wxgui::ISprite* m_parts[PARTS_COUNT];

			friend class AEPartsOP;

		}; // AEParts
	}
}

#endif // _DEDITOR_MOTOX_ACTOR_EDIT_PARTS_H_