#ifndef _WX_GUI_CAMERA_H_
#define _WX_GUI_CAMERA_H_

#include "Interface.h"

#include <Fruits2D/Fruits2D.h>

namespace wxgui
{
	class Camera
	{
	public:
		Camera(float scale = 1.0f);

		const f2Vec2& getCenter() const;
		void setCenter(const f2Vec2& center);

		float getScale() const;
		void setScale(float scale);
		void setScale(float scale, int x, int y, int width, int height);

		f2Vec2 transPosScreenToProject(int x, int y, int width, int height) const;
//		f2Vec2 transPosProjectToScreen(const f2Vec2& proj, int width, int height) const;

		// For reset projection transform (gluOrtho2D)
		void addObserver(ICameraObserver* observer);

	private:
		void notifyObservers();

	private:
		f2Vec2 m_center;
		float m_scale;

		std::vector<ICameraObserver*> m_observers;

	}; // Camera
}

#endif // _WX_GUI_CAMERA_H_