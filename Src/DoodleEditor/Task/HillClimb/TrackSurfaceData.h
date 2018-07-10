#ifndef _DEDITOR_HILL_CLIMB_TRACK_SURFACE_DATA_H_
#define _DEDITOR_HILL_CLIMB_TRACK_SURFACE_DATA_H_

#include <wxGUI/wxGUI.h>

namespace deditor
{
	namespace hill_climb
	{
		class TrackSurfaceData
		{
		public:
			wxgui::Image* image;

			std::vector<f2Vec2> vertices;
			std::vector<f2Vec2> texCoords;

		}; // TrackSurfaceData
	}
}

#endif // _DEDITOR_HILL_CLIMB_TRACK_SURFACE_DATA_H_