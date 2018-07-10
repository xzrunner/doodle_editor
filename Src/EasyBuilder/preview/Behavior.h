#ifndef _EASY_BUILDER_PREVIEW_BEHAVIOR_H_
#define _EASY_BUILDER_PREVIEW_BEHAVIOR_H_

namespace ebuilder
{	
	namespace preview
	{	
		class Behavior
		{
		public:
			virtual ~Behavior() {}

			virtual void trigger() = 0;

		}; // Behavior
	}
}

#endif // _EASY_BUILDER_PREVIEW_BEHAVIOR_H_