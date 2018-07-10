#ifndef _MOTOX_SPRITE_GRID_LOADER_H_
#define _MOTOX_SPRITE_GRID_LOADER_H_

#include <Doodle2D/doodle2d.h>

namespace motox
{
	class SpriteGridLoader
	{
	public:
		struct Entry
		{
			int id;
			d2d::Vector pos;
			float angle;
			float scale;
			unsigned int type;
		};

		typedef std::vector<Entry*> Grid;
		typedef std::vector<Grid> Grids;

	public:
		SpriteGridLoader(d2d::Context* pContext, 
			const std::string& filename, int scene, int level);
		~SpriteGridLoader();

		void loadFromFile(bool isSingleLayer);

	private:
		void clear();

		void loadHeader(byte*& ptr);
		void loadData(byte*& ptr, Grids& internal, Grids& intersect);
		void loadData(byte*& ptr, std::vector<Grids>& internals,
			std::vector<Grids>& intersects);
		void loadData(byte*& ptr, Grid& tiles);

	public:
		static const int SPRITE_X_MIRROR = 0x1;
		static const int SPRITE_Y_MIRROR = 0x2;

	public:
		std::string m_filepath;

		float m_leftmost;
		float m_gridWidth;

		Grids m_internal;
		Grids m_intersect;

		std::vector<Grids> m_internals;
		std::vector<Grids> m_intersects;

	private:
#ifdef D2D_ANDROID_NATIVE
		android_app* m_pApplication;
#endif

	}; // SpriteGridLoader
}

#endif // _MOTOX_SPRITE_GRID_LOADER_H_