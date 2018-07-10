#ifndef _EASY_BUILDER_CONTEXT_H_
#define _EASY_BUILDER_CONTEXT_H_

namespace ebuilder
{
	class LibraryPanel;
	class PropertySettingPanel;
	class BackstagePanel;
	class StagePanel;

	class Context
	{
	public:
		LibraryPanel* library;
		PropertySettingPanel* property;
		BackstagePanel* backstage;
		StagePanel* stage;

	public:
		static Context* Instance();

	private:
		Context();

	private:
		static Context* m_instance;

	}; // Context
}

#endif // _EASY_BUILDER_CONTEXT_H_