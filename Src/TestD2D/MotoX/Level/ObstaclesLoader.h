#ifndef _MOTOX_OBSTACLES_LOADER_H_
#define _MOTOX_OBSTACLES_LOADER_H_

#include <Doodle2D/doodle2d.h>

namespace motox
{
	class ObstaclesLoader
	{
	public:
		struct Entry
		{
			int id;	// image + combination + breakable
			d2d::Vector pos;
			float angle;
			float scale;
			unsigned int type;
		};

	public:
		ObstaclesLoader(d2d::Context* pContext, 
			const std::string& filename, int scene, int level);
		~ObstaclesLoader();

	private:
		void clear();

		void loadFromFile(const std::string& filepath);

	public:
		static const int SPRITE_X_MIRROR = 0x1;
		static const int SPRITE_Y_MIRROR = 0x2;

	public:
		std::vector<Entry*> m_sprites;

	private:
#ifdef D2D_ANDROID_NATIVE
		android_app* m_pApplication;
#endif

	}; // ObstaclesLoader
}

#endif // _MOTOX_OBSTACLES_LOADER_H_