#ifndef _DEDITOR_MOTOX_LIBRARY_ACTOR_ITEM_H_
#define _DEDITOR_MOTOX_LIBRARY_ACTOR_ITEM_H_

#include "ActorDefs.h"

#include <wxGUI/wxGUI.h>

namespace deditor
{
	namespace motox
	{
		class LibraryActorItem : public wxgui::ISymbol
		{
		public:
			LibraryActorItem();

			//
			// IObject interface
			//
			virtual LibraryActorItem* clone() { return NULL; }

			//
			// ISerializable interface
			//
			virtual void loadFromTextFile(std::ifstream& fin);
			virtual void storeToTextFile(std::ofstream& fout) const;

			//
			// wxgui::ISymbol interface
			//		
			virtual void reloadTexture() const;
			virtual void draw() const;
			virtual float getWidth() const;
			virtual float getHeight() const;

			void setLocation(const f2Vec2& pos);

		protected:
			virtual void loadResources();

		public:
			struct PartDef
			{
				wxString path;
				f2Vec2 pos;
				float angle;

				wxgui::ISprite* loadBodySprite() const;

			}; // PartDef

			struct JointDef : public wxgui::JointDef
			{
				f2Vec2 anchor;

				JointDef() { anchor.setInvalid(); }

			}; // JointDef

		public:
			PartDef m_parts[PARTS_COUNT];
			JointDef m_joints[JOINTS_TYPE_COUNT];

		}; // LibraryActorItem
	}
}

#endif // _DEDITOR_MOTOX_LIBRARY_ACTOR_ITEM_H_