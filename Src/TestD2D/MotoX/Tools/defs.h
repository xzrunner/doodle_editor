#ifndef _MOTOX_DEFS_H_
#define _MOTOX_DEFS_H_

#include <string>
#ifdef D2D_WINDOWS
#include <fstream>
#endif

namespace motox
{
#ifdef D2D_WINDOWS
//	static const std::string RESOURCE_ROOT = "D:/MyProject/Editor/Project/TestD2D/Data/MotoX/";
	static const std::string RESOURCE_ROOT = "D:/MyProject/svn 2/FruitsEditor/MotoX/MotoX/pc/";
#endif

	static const std::string TRACK_CHAINS_FILENAME = "track_chains.bin";

	static const std::string GROUND_SURFACE_FILENAME = "ground_surface.bin";
//	static const std::string GROUND_TEXTURE_FILENAME = "ground_surface.jpg";
	static const std::string GROUND_TEXTURE_FILENAME = "ground_surface_2.jpg";

	static const std::string BACKGROUND_FILENAME = "background.jpg";

	static const std::string ACTOR_TEXTURE_FILENAME = "actor.png";
	static const std::string ACTOR_DATA_FILENAME = "actor.bin";

	static const std::string TILES_TEXTURE_FILENAME = "tiles.png";
	static const std::string TILES_TEXTURE_INFO_FILENAME = "tiles.bin";
	static const std::string TILES_DATA_FILENAME = "tiles_data.bin";

	static const std::string OBSTACLE_TEXTURE_FILENAME = "obstacle.png";
	static const std::string OBSTACLE_TEXTURE_INFO_FILENAME = "obstacle.bin";
	static const std::string OBSTACLE_DATA_FILENAME = "obstacle_data.bin";
	static const std::string OBSTACLE_INFO_FILENAME = "obstacle_info.bin";

	enum Operating
	{
		e_left = 0,
		e_right,
		e_up,
		e_down
	};

	static const int g_gravity = /*20*/30;

	static const int g_wheelFriction = 3;
	static const int g_motoDensity = 8; 
	static const int g_speed = 45;
	static const int g_acceleration = 20;
	static const int g_motoTorque = 500;

	static const float g_playerDensity = 0.1f;
	static const int g_playerTorque = 1400;

	static const int g_trackFriction = 2;
}

#endif // _MOTOX_DEFS_H_