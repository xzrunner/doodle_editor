#ifndef _EASY_BUILDER_CHANGE_IMAGE_H_
#define _EASY_BUILDER_CHANGE_IMAGE_H_

#include "Behavior.h"

namespace ebuilder
{
	class MediaPage;

	class ChangeImage : public Behavior
	{
	public:
		virtual ~ChangeImage();

		virtual void update(const wxgui::LibraryList& list);

		void registerListener(MediaPage* mediaPage);

	private:
		ChangeImage(Actor* actor, wxgui::LibraryList* mediaList);

	public:
		wxgui::ISymbol* selected;

		MediaPage* m_mediaPage;

		friend class BehaviorFactory;

	}; // ChangeImage
}

#endif // _EASY_BUILDER_CHANGE_IMAGE_H_