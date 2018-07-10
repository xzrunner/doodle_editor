#ifndef _EASY_BUILDER_SETTINGS_H_
#define _EASY_BUILDER_SETTINGS_H_

namespace ebuilder
{
	class Settings
	{
	public:

		enum CodeType
		{
			e_love2d = 0,
			e_libgdx,
			e_cocos2dx,
//			e_unity,
			e_easy2d
		};

		static CodeType code;

	}; // Settings
}

#endif // _EASY_BUILDER_SETTINGS_H_